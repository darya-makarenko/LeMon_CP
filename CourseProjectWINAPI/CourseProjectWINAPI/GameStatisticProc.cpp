#include "GameStatisticProc.h"

#define DEF_GRAPHIC_PADDING 20;
#define COLUMNS_COUNT 2
#define COUNT_CHARS 20
#define TABLE_MARGIN 20

namespace GameStatisticWindow
{
    GameStatistic *gameStatistic = NULL;

    HWND ShowGameStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, GameStatistic *stat)
    {
        HWND hGameStatWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Game statistic"),
            WS_VISIBLE | WS_BORDER | WS_POPUPWINDOW | WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        DWORD err = GetLastError();

        gameStatistic = stat;

        ShowWindow(hGameStatWnd, SW_MAXIMIZE);
        return hGameStatWnd;
    }

    void DrawValuesGrid(HWND hWnd, GameStatistic *gameStatistic)
    {
        std::map<GameButton, std::string> outputMap{
            { BUTTON_DOWN, "Down" },
            { BUTTON_UP, "Up" },
            { BUTTON_RIGHT, "Right" },
            { BUTTON_LEFT, "Left" },
            { BUTTON_UPRIGHT, "Up-Right" },
            { BUTTON_UPLEFT, "Up-Left" },
            { BUTTON_DOWNRIGHT, "Down-Right" },
            { BUTTON_DOWNLEFT, "Down-Left" },
            { GameButton_Invalid, "The end" }
        };

        RECT clientRect;
        GetClientRect(hWnd, &clientRect);

        int countRows = 0;
        std::vector<std::string> values;
        values.push_back("Game button");
        values.push_back("Avg. push time (ms.)");
        countRows++;
        char valueStr[COUNT_CHARS];
        std::map<GameButton, Statistic> btnStatistics = gameStatistic->getButtonsStatistic();
        for (std::pair<GameButton, Statistic> stat : btnStatistics) {
            values.push_back(outputMap[stat.first]);
            sprintf_s(valueStr, COUNT_CHARS, "%.2lf", stat.second.getAverageTime());
            values.push_back(std::string(valueStr));
            countRows++;
        }

        values.push_back("Avg. push time");
        sprintf_s(valueStr, COUNT_CHARS, "%.2lf", gameStatistic->getAverageTime());
        values.push_back(std::string(valueStr));
        countRows++;
        RECT tableRect = { clientRect.left + TABLE_MARGIN, clientRect.top + TABLE_MARGIN, clientRect.right / 2 - TABLE_MARGIN, clientRect.bottom / 2 - TABLE_MARGIN };
        DrawTable::Draw(hWnd, &tableRect, values, COLUMNS_COUNT, countRows);
    }

    void DrawValuesRose(HWND hWnd, GameStatistic *gameStatistic)
    {
        RECT graphRect;
        GetClientRect(hWnd, &graphRect);
        graphRect.left += (graphRect.right - graphRect.left) / 2 + DEF_GRAPHIC_PADDING;
        graphRect.top += DEF_GRAPHIC_PADDING;
        graphRect.bottom -= DEF_GRAPHIC_PADDING;
        graphRect.right -= DEF_GRAPHIC_PADDING;

        Draw::DrawStatisticRose(hWnd, &graphRect, gameStatistic);
    }

    void DrawCommonInfo(HWND hWnd, GameStatistic *gameStatistic)
    {
        int const TEXT_INTERVAL = 20;
        RECT rect;
        GetClientRect(hWnd, &rect);
        rect.top = (rect.bottom - rect.top) / 2 + TABLE_MARGIN;
        rect.left += TABLE_MARGIN;

        HDC hDC = GetDC(hWnd);
        std::string infoString = "Push keys count: " + std::to_string(gameStatistic->getCountKeys());
        TextOut(hDC, rect.left, rect.top, infoString.c_str(), infoString.size());
        rect.top += TEXT_INTERVAL;
        infoString = "Right keys count: " + std::to_string(gameStatistic->getCountRightKeys());
        COLORREF oldColor = SetTextColor(hDC, RGB(76, 153, 0));
        TextOut(hDC, rect.left, rect.top, infoString.c_str(), infoString.size());
        rect.top += TEXT_INTERVAL;
        infoString = "Wrong keys count: " + std::to_string(gameStatistic->getCountErrorKeys());
        SetTextColor(hDC, RGB(153, 0, 0));
        TextOut(hDC, rect.left, rect.top, infoString.c_str(), infoString.size());
        SetTextColor(hDC, oldColor);

        ReleaseDC(hWnd, hDC);
    }

    LRESULT CALLBACK GameStatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        //case WM_CREATE:
            //return 0;
        case WM_DESTROY: {
            HWND hParentWnd = GetParent(hWnd);
            if (hParentWnd != NULL) {
                PostMessage(hParentWnd, WM_CLOSE, 0, 0);
            }
            //PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
            if (gameStatistic != NULL) {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                DrawValuesGrid(hWnd, gameStatistic);

                DrawCommonInfo(hWnd, gameStatistic);

                DrawValuesRose(hWnd, gameStatistic);
                
                EndPaint(hWnd, &ps);
            }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

#undef DEF_GRAPHIC_PADDING
#undef COLUMNS_COUNT
#undef COUNT_CHARS
#undef TABLE_MARGIN
