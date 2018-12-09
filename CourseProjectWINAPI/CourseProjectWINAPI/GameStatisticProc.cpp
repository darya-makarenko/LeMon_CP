#include "GameStatisticProc.h"

#define DEF_GRAPHIC_PADDING 20;

namespace GameStatisticWindow
{
    GameStatistic *gameStatistic = NULL;

    HWND ShowGameStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, GameStatistic *stat)
    {
        HWND hGameWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Game statistic"),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_BORDER,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        gameStatistic = stat;

        return hGameWnd;
    }

    LRESULT CALLBACK GameStatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        static std::map<GameButton, std::string> outputMap{
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

        switch (uMsg)
        {
        case WM_CREATE:
            return 0;
        case WM_DESTROY:
            //PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            if (gameStatistic != NULL) {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                int y = 20, delta = 20;
                std::string statisticString = "Statistic:";
                TextOut(hdc, 20, y, statisticString.c_str(), statisticString.length());
                for (std::pair<GameButton, Statistic> stat : gameStatistic->getButtonsStatistic()) {
                    y += delta;
                    statisticString = outputMap[stat.first] + ": " + std::to_string(stat.second.getAverageTime());
                    TextOut(hdc, 20, y, statisticString.c_str(), statisticString.length());
                }

                statisticString = "Play time: " + std::to_string(gameStatistic->getPlayTime()) + ", " +
                    "Average right press time: " + std::to_string(gameStatistic->getAverageTime()) + ", " +
                    "Count all keys: " + std::to_string(gameStatistic->getCountKeys()) + ", " +
                    "Count wrong keys: " + std::to_string(gameStatistic->getCountErrorKeys()) + ", " +
                    "Count right keys: " + std::to_string(gameStatistic->getCountRightKeys());
                TextOut(hdc, 20, y + delta, statisticString.c_str(), statisticString.length());

                time_t endTime = gameStatistic->getEndTime();
                char timeBuf[26];
                ctime_s(timeBuf, sizeof(timeBuf), &endTime);
                statisticString = "Game: " + std::string(timeBuf);
                TextOut(hdc, 20, y + 2 * delta, statisticString.c_str(), statisticString.length());

                RECT graphRect;
                GetClientRect(hWnd, &graphRect);
                graphRect.left += (graphRect.right - graphRect.left) / 2 + DEF_GRAPHIC_PADDING;
                graphRect.top += DEF_GRAPHIC_PADDING;
                graphRect.bottom -= DEF_GRAPHIC_PADDING;
                graphRect.right -= DEF_GRAPHIC_PADDING;

                Draw::DrawStatisticRose(hWnd, &graphRect, gameStatistic);

                EndPaint(hWnd, &ps);
            }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

#undef DEF_GRAPHIC_PADDING
