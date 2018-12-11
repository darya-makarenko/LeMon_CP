#include "StatisticProc.h"

#define STR_BUF_LEN 20
#define EPSILON 0,0000000001
#define GRAPHIC_MARGIN 20

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
        HWND hWndList;

        void CreateColumns(HWND hListWnd)
        {
            LV_COLUMN lvc = { 0 };
            RECT rect;

            GetClientRect(hListWnd, &rect);

            lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt = LVCFMT_LEFT;
            lvc.cx = (rect.right - rect.left) / 2;

            lvc.iSubItem = 0;
            char dateColumnName[] = "Date";
            lvc.pszText = dateColumnName;
            ListView_InsertColumn(hListWnd, 0, &lvc);

            lvc.iSubItem = 1;
            char speedColumnName[] = "Avg. Speed";
            lvc.pszText = speedColumnName;
            ListView_InsertColumn(hListWnd, 1, &lvc);
        }

        typedef struct _statInfo
        {
            char *time;
            char *value;
        } STATINFO;

        void FillListView(HWND hListWnd, std::vector<StatStruct> *pFullStat)
        {
            LV_ITEM lvi = { 0 };
            lvi.mask = LVIF_TEXT | LVIF_PARAM;
            STATINFO statInfo = { 0 };
            for (size_t i = 0; i < pFullStat->size(); i++) {
                lvi.iItem = i;
                lvi.iSubItem = 0;
                lvi.cchTextMax = 40;
                time_t date = (*pFullStat)[i].date;
                char timeBuf[26];
                ctime_s(timeBuf, sizeof(timeBuf), &date);
                statInfo.time = timeBuf;

                char valueStr[STR_BUF_LEN];
                int strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*pFullStat)[i].average_time);
                statInfo.value = valueStr;
                //statInfo = { timeBuf, valueStr };

                //lvi.pszText = timeBuf;
                lvi.lParam = (LPARAM)&statInfo;
                //lvi.cColumns = 2;
                ListView_InsertItem(hListWnd, &lvi);

                lvi.iItem = i;
                lvi.iSubItem = 1;
                
                //lvi.pszText = valueStr;
                //lvi.cchTextMax = strLen;
                ListView_InsertItem(hListWnd, &lvi);
            }
        }

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

            avgStat.btn_upleft_time = avgArray[0].allAvgTime / (double)avgArray[0].count;
            avgStat.btn_up_time = avgArray[1].allAvgTime / (double)avgArray[1].count;
            avgStat.btn_upright_time = avgArray[2].allAvgTime / (double)avgArray[2].count;
            avgStat.btn_right_time = avgArray[3].allAvgTime / (double)avgArray[3].count;
            avgStat.btn_downright_time = avgArray[4].allAvgTime / (double)avgArray[4].count;
            avgStat.btn_down_time = avgArray[5].allAvgTime / (double)avgArray[5].count;
            avgStat.btn_downleft_time = avgArray[6].allAvgTime / (double)avgArray[6].count;
            avgStat.btn_left_time = avgArray[7].allAvgTime / (double)avgArray[7].count;
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

        RECT rect;
        GetClientRect(hStatWnd, &rect);
        INITCOMMONCONTROLSEX icce = { 0 };
        icce.dwICC = ICC_LISTVIEW_CLASSES;
        icce.dwSize = sizeof(icce);
        InitCommonControlsEx(&icce);
        hWndList = CreateWindowEx(
            0L,
            WC_LISTVIEW,
            "",
            WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | WS_BORDER | LVS_SINGLESEL,
            0, 0, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2,
            hStatWnd,
            NULL,
            hInstance,
            NULL
        );
        
        CreateColumns(hWndList);

        StatisticReader reader(statisticFile);
        fullStatistic = reader.readStatVector();

        FillListView(hWndList, &fullStatistic);

        return hStatWnd;
    }

    LRESULT CALLBACK StatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            DrawAverageStatisticRose(hWnd, &fullStatistic);
            DrawStatisticGraphic(hWnd, &fullStatistic);
            EndPaint(hWnd, &ps);
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
