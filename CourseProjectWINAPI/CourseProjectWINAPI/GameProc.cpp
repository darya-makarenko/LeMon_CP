#include "GameProc.h"
#include "GameStatisticProc.h"
#include "CommonProc.h"

namespace GameWindow
{
    namespace
    {
        Game *game = NULL;
        GameArrow gameArrow;
        LPCTSTR lpGameStatisticClass;
        HINSTANCE _hInstance;
        GameStatistic statistic;
        //HWND hStatisticWnd = NULL;
        std::string statisticFile;
        BOOL statisticWasShow = FALSE;
    }

    HWND ShowGameWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statFile)
    {
        _hInstance = hInstance;
        HWND hGameWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Game start"),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,// | WS_MAXIMIZE,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        statisticFile = statFile;

        lpGameStatisticClass = TEXT("GameStatistic");
        if (!RegMyWindowClass(hInstance, lpGameStatisticClass, (WNDPROC)GameStatisticWindow::GameStatisticWindowProc)) {
            if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
                lpGameStatisticClass = NULL;
            }
        }

        return hGameWnd;
    }

    LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        static std::list<GameButton> lGameButtons{
            BUTTON_DOWN,
            BUTTON_UP,
            BUTTON_DOWN,
            BUTTON_DOWNRIGHT,
            BUTTON_DOWNLEFT,
            BUTTON_UP,
            BUTTON_LEFT,
            BUTTON_UPLEFT,
            BUTTON_DOWN,
            BUTTON_UPRIGHT,
            BUTTON_DOWN,
            BUTTON_UP,
            BUTTON_RIGHT,
            BUTTON_UP,
            BUTTON_DOWN
        };

        switch (uMsg)
        {
        case WM_CREATE:
            return 0;
        case WM_DESTROY:
            if (game != NULL) {
                delete game;
                game = NULL;
            }
            //DestroyWindow(hStatisticWnd);
            //hStatisticWnd = NULL;
            //PostQuitMessage(0);
            statisticWasShow = FALSE;
            return 0;
        case WM_PAINT:
            if (game != NULL && !game->IsEnd()) {
                gameArrow.Draw(hWnd, game->Current());
            }
            return 0;
        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_RETURN:
                if (game == NULL) {
                    game = new Game(DeviceInput::sButtonMapping[0], lGameButtons, GetMessageTime());
                    gameArrow.Draw(hWnd, game->Current());
                }
                return 0;
            default:
                if (!game->IsEnd() && game->ButtonInput(static_cast<DeviceButton>(wParam), GetMessageTime())) {
                    gameArrow.Draw(hWnd, game->Current());
                }
                if (game->IsEnd()) {
                    if (!statisticWasShow) {
                        statistic = game->getStatistic();
                        GameStatisticWindow::ShowGameStatisticWindow(_hInstance, hWnd, lpGameStatisticClass, CW_USEDEFAULT, CW_USEDEFAULT, &statistic);
                        StatisticWriter writer(statisticFile);
                        writer.writeStat(statistic);
                        statisticWasShow = TRUE;
                    }
                }
                break;
            };
            return 0;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}