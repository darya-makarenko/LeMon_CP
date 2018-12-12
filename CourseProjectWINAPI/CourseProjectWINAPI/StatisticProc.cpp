#include "StatisticProc.h"

#define STR_BUF_LEN 20
#define EPSILON 0,0000000001
#define GRAPHIC_MARGIN 20
#define COUNT_ROWS 10
#define COUNT_COLUMNS 3
#define COUNT_CHARS 30
#define BTN_HEIGHT 20

#define ID_BUTTON_SAVE 3010
#define ID_BUTTON_LOAD 3011
#define ID_BUTTON_PREV 3012
#define ID_BUTTON_NEXT 3013

typedef struct _btnAvg
{
    DWORD count;
    double allAvgTime;
} BtnAvg;

namespace StatisticWindow
{
    namespace
    {
        std::vector<StatStruct> fullStatistic;
        DWORD currIndex;
        HWND hButtonLoad;
        HWND hButtonSave;
        HWND hButtonPrev;
        HWND hButtonNext;
        HWND hParentWnd;

        StatStruct CountAvgStatistic(std::vector<StatStruct> *pFullStat)
        {
            int const BTN_COUNT = 8;
            StatStruct avgStat = { 0 };
            size_t statCount = pFullStat->size();
            BtnAvg avgArray[BTN_COUNT] = { 0 };
            for (size_t i = 0; i < statCount; i++) {
                double avgTime[BTN_COUNT] = { (*pFullStat)[i].btn_upleft_time, 
                    (*pFullStat)[i].btn_up_time, 
                    (*pFullStat)[i].btn_upright_time,
                    (*pFullStat)[i].btn_right_time,
                    (*pFullStat)[i].btn_downright_time, 
                    (*pFullStat)[i].btn_down_time, 
                    (*pFullStat)[i].btn_downleft_time, 
                    (*pFullStat)[i].btn_left_time };
                for (int i = 0; i < BTN_COUNT; i++) {
                    if (avgTime[i] > EPSILON) {
                        avgArray[i].allAvgTime += avgTime[i];
                        avgArray[i].count++;
                    }
                }
            }

            avgStat.btn_upleft_time = avgArray[0].count != 0 ? (avgArray[0].allAvgTime / avgArray[0].count) : 0.0;
            avgStat.btn_up_time = avgArray[1].count != 0 ? (avgArray[1].allAvgTime / avgArray[1].count) : 0.0;
            avgStat.btn_upright_time = avgArray[2].count != 0 ? (avgArray[2].allAvgTime / avgArray[2].count) : 0.0;
            avgStat.btn_right_time = avgArray[3].count != 0 ? (avgArray[3].allAvgTime / avgArray[3].count) : 0.0;
            avgStat.btn_downright_time = avgArray[4].count != 0 ? (avgArray[4].allAvgTime / avgArray[4].count) : 0.0;
            avgStat.btn_down_time = avgArray[5].count != 0 ? (avgArray[5].allAvgTime / avgArray[5].count) : 0.0;
            avgStat.btn_downleft_time = avgArray[6].count != 0 ? (avgArray[6].allAvgTime / avgArray[6].count) : 0.0;
            avgStat.btn_left_time = avgArray[7].count != 0 ? (avgArray[7].allAvgTime / avgArray[7].count) : 0.0;
            return avgStat;
        }

        void DrawAverageStatisticRose(HWND hWnd, std::vector<StatStruct> *pFullStat)
        {
            StatStruct avgStat = CountAvgStatistic(pFullStat);
            RECT rect;
            GetClientRect(hWnd, &rect);
            rect.left = rect.left + (rect.right - rect.left) / 2 + GRAPHIC_MARGIN;
            rect.bottom = rect.top + (rect.bottom - rect.top) / 2 - GRAPHIC_MARGIN;
            rect.top += GRAPHIC_MARGIN;
            rect.right -= GRAPHIC_MARGIN;
            Draw::DrawStatisticRose(hWnd, &rect, &avgStat);
        }

        void DrawStatisticGraphic(HWND hWnd, std::vector<StatStruct> *pFullStat)
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            rect.top = (rect.bottom - rect.top) / 2 + GRAPHIC_MARGIN;
            rect.bottom -= GRAPHIC_MARGIN;
            rect.left += GRAPHIC_MARGIN;
            rect.right -= GRAPHIC_MARGIN;
            Draw::DrawTimeProgressGraphic(hWnd, &rect, &fullStatistic);
        }

        void ShowTable(HWND hWnd)
        {
            if (fullStatistic.size() > currIndex && currIndex >= 0) {
                std::vector<std::string> values;
                values.push_back("No.");
                values.push_back("Game date");
                values.push_back("Avg. push time (ms.)");
                char valueStr[COUNT_CHARS];
                DWORD startInd = currIndex + COUNT_ROWS > fullStatistic.size() ? fullStatistic.size() : currIndex + COUNT_ROWS;
                for (int i = startInd - 1; i >= (int)currIndex && i >= 0 ; i--) {
                    values.push_back(std::to_string(i + 1) + ".");
                    ctime_s(valueStr, sizeof(valueStr), &(fullStatistic[i].date));
                    values.push_back(std::string(valueStr));
                    sprintf_s(valueStr, COUNT_CHARS, "%.2lf", fullStatistic[i].average_time);
                    values.push_back(std::string(valueStr));
                }
                
                RECT clientRect;
                GetClientRect(hWnd, &clientRect);
                RECT tableRect = { clientRect.left + GRAPHIC_MARGIN, clientRect.top + GRAPHIC_MARGIN, clientRect.right / 2 - GRAPHIC_MARGIN - BTN_HEIGHT, clientRect.bottom / 2 - GRAPHIC_MARGIN - BTN_HEIGHT};
                DrawTable::Draw(hWnd, &tableRect, values, COUNT_COLUMNS, COUNT_ROWS + 1);
            }
        }

        void MoveNextTablePage(HWND hWnd)
        {
            if (fullStatistic.size() >= currIndex) {
                currIndex += COUNT_ROWS;
                if (currIndex > fullStatistic.size()) {
                    currIndex = fullStatistic.size();
                    EnableWindow(hButtonNext, FALSE);
                }
                else {
                    EnableWindow(hButtonNext, TRUE);
                }
                ShowTable(hWnd);
            }
        }

        void MovePrevTablePage(HWND hWnd)
        {
            if (currIndex >= 0) {
                if ((int)(currIndex) - COUNT_ROWS <= 0) {
                    currIndex = 0;
                    EnableWindow(hButtonPrev, FALSE);
                }
                else {
                    currIndex -= COUNT_ROWS;
                    EnableWindow(hButtonPrev, TRUE);
                }
                ShowTable(hWnd);
            }
        }

        void CreateButtons(HINSTANCE hInstance, HWND hWnd)
        {
            RECT rect = { 0 };
            GetClientRect(hWnd, &rect);
            rect.left += GRAPHIC_MARGIN;
            rect.right = (rect.right / 2) - GRAPHIC_MARGIN;
            rect.bottom = rect.bottom / 2;
            rect.top = rect.bottom - BTN_HEIGHT;
            LONG btnWidth = (rect.right - rect.left - 3 * GRAPHIC_MARGIN) / 4;
            if (btnWidth < 0 ) {
                btnWidth = 0;
            }

            hButtonLoad = makeButton(hInstance, hWnd, "Load", rect.left, rect.top, btnWidth, BTN_HEIGHT,
                ID_BUTTON_LOAD);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            hButtonSave = makeButton(hInstance, hWnd, "Save all", rect.left, rect.top, btnWidth, BTN_HEIGHT,
                ID_BUTTON_SAVE);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            hButtonPrev = makeButton(hInstance, hWnd, "<-Prev", rect.left, rect.top, btnWidth, BTN_HEIGHT,
                ID_BUTTON_PREV);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            hButtonNext = makeButton(hInstance, hWnd, "Next->", rect.left, rect.top, btnWidth, BTN_HEIGHT,
                ID_BUTTON_NEXT);

            EnableWindow(hButtonPrev, FALSE);
            if (fullStatistic.size() < COUNT_ROWS) {
                EnableWindow(hButtonNext, FALSE);
            }
        }

        void MoveButtons(HWND hWnd)
        {
            RECT rect = { 0 };
            GetClientRect(hWnd, &rect);
            rect.left += GRAPHIC_MARGIN;
            rect.right = (rect.right / 2) - GRAPHIC_MARGIN;
            rect.bottom = rect.bottom / 2;
            rect.top = rect.bottom - BTN_HEIGHT;
            LONG btnWidth = (rect.right - rect.left - 3 * GRAPHIC_MARGIN) / 4;
            if (btnWidth < 0) {
                btnWidth = 0;
            }

            MoveWindow(hButtonLoad, rect.left, rect.top, btnWidth, BTN_HEIGHT, FALSE);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            MoveWindow(hButtonSave, rect.left, rect.top, btnWidth, BTN_HEIGHT, FALSE);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            MoveWindow(hButtonPrev, rect.left, rect.top, btnWidth, BTN_HEIGHT, FALSE);
            rect.left += btnWidth + GRAPHIC_MARGIN;
            MoveWindow(hButtonNext, rect.left, rect.top, btnWidth, BTN_HEIGHT, FALSE);
        }
    }

    HWND ShowStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statisticFile)
    {
        HWND hStatWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Full statistic"),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_BORDER,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        hParentWnd = hWnd;
        currIndex = 0;

        StatisticReader reader(statisticFile);
        fullStatistic = reader.readStatVector();
        ShowTable(hStatWnd);

        CreateButtons(hInstance, hStatWnd);

        return hStatWnd;
    }

    LRESULT CALLBACK StatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            if (hParentWnd != NULL) {
                EnableWindow(hParentWnd, TRUE);
                SetActiveWindow(hParentWnd);
            }
            return 0;
        case WM_COMMAND:
            switch (wParam)
            {
            case ID_BUTTON_SAVE: {
                std::string filename = getStatFileNameDialog(FALSE);
                if (filename != "") {
                    StatisticWriter writer(filename);
                    writer.saveFullStat(fullStatistic);
                }
            }
                break;
            case ID_BUTTON_LOAD: {
                std::string filename = getStatFileNameDialog(TRUE);
                if (filename != "") {
                    StatisticReader reader(filename);
                    fullStatistic = reader.readStatVector();
                    currIndex = 0;
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
                break;
            case ID_BUTTON_PREV:
                MovePrevTablePage(hWnd);
                break;
            case ID_BUTTON_NEXT:
                MoveNextTablePage(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            DrawAverageStatisticRose(hWnd, &fullStatistic);
            DrawStatisticGraphic(hWnd, &fullStatistic);
            ShowTable(hWnd);
            MoveButtons(hWnd);
            EndPaint(hWnd, &ps);
            
            if (currIndex == 0) {
                EnableWindow(hButtonPrev, FALSE);
            }
            
            if (currIndex + COUNT_ROWS >= fullStatistic.size()) {
                EnableWindow(hButtonNext, FALSE);
            }
            return 0;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

#undef STR_BUF_LEN
#undef EPSILON
#undef GRAPHIC_MARGIN
#undef COUNT_ROWS
#undef COUNT_COLUMNS
#undef COUNT_CHARS