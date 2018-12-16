#include "GameProc.h"
#include "GameStatisticProc.h"
#include "CommonProc.h"

#define TIMER_START_COUNT 5
#define TIMER_INTERVAL 1000
#define TIMER_ID 1
#define TIMER_NUMBER_SIZE 0.5
#define FREQUENCY 10
#define ZERO_STATE 0
#define JOYID JOYSTICKID1

namespace GameWindow
{
    Game *game = NULL;
    GameArrow gameArrow;
    LPCTSTR lpGameStatisticClass;
    HINSTANCE _hInstance;
    GameStatistic statistic;
    std::string statisticFile;
    BOOL statisticWasShow = FALSE;
    DWORD secondsBeforeStart = TIMER_START_COUNT;
    int timerID = 0;
    HFONT hFont = NULL;
    Sequence gameSequence;
    BOOL joyAttached = FALSE;
    HWND hParentWnd;
    ButtonMapping btnMapping;

    void DestroyTimer(HWND hWnd)
    {
        if (timerID != 0) {
            KillTimer(hWnd, TIMER_ID);
            secondsBeforeStart = TIMER_START_COUNT;
            timerID = 0;
        }
        if (hFont != NULL) {
            DeleteObject(hFont);
            hFont = NULL;
        }
    }

    void DrawTimerNumber(HWND hWnd)
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        if (hFont == NULL) {
            LONG fontHeight = (LONG)(((rect.bottom - rect.top) * TIMER_NUMBER_SIZE));
            LOGFONT logFont = { 0 };
            logFont.lfHeight = fontHeight;
            logFont.lfWeight = FW_BOLD;
            hFont = CreateFontIndirect(&logFont);
        }
        HDC hDC = GetDC(hWnd);
        HFONT oldFont = (HFONT)SelectObject(hDC, hFont);
        RECT numRect = { 0 };
        std::string timerNumber = std::to_string(secondsBeforeStart);
        DrawText(hDC, timerNumber.c_str(), -1, &numRect, DT_CALCRECT);
        FillRect(hDC, &rect, (HBRUSH)COLOR_APPWORKSPACE);
        int prevBkMode = SetBkMode(hDC, TRANSPARENT);
        TextOut(hDC, (rect.right - rect.left) / 2 - numRect.right / 2, (rect.bottom - rect.top) / 2 - numRect.bottom / 2, timerNumber.c_str(), timerNumber.size());
        SelectObject(hDC, oldFont);
        SetBkMode(hDC, prevBkMode);
        ReleaseDC(hWnd, hDC);
    }

    void ProcessBtnInput(HWND hWnd, UINT btn)
    {
        if (game != NULL) {
            if (!game->IsEnd() && game->ButtonInput(static_cast<DeviceButton>(btn), GetMessageTime())) {
                if (!(game->IsEnd())) {
                    gameArrow.Draw(hWnd, game->Current(), TRUE);
                }
            }

            if (game->IsEnd()) {
                if (!statisticWasShow) {
                    statistic = game->getStatistic();
                    GameStatisticWindow::ShowGameStatisticWindow(_hInstance, hWnd, lpGameStatisticClass, CW_USEDEFAULT, CW_USEDEFAULT, &statistic);
                    StatisticWriter writer(statisticFile);
                    writer.writeStat(statistic);
                    statisticWasShow = TRUE;
                    EnableWindow(hWnd, FALSE);
                }
            }
        }
    }

    bool CheckForJoystick(HWND hWnd)
    {
        JOYINFO joyInfo;
        UINT numDevs;
        BOOL devAttached;
        if ((numDevs = joyGetNumDevs()) == 0) {
            return false;
        }

        devAttached = joyGetPos(JOYID, &joyInfo) == JOYERR_NOERROR;
        if (!devAttached) {
            return false;
        }
        else {
            MMRESULT res = joySetCapture(hWnd, JOYID, FREQUENCY, FALSE);
            if (res == JOYERR_NOERROR) {
                return true;
            }
            else {
                return false;
            }
        }
    }

    ButtonMapping GetGameButtonMapping(HWND hWnd)
    {
        joyAttached = CheckForJoystick(hWnd);
        if (joyAttached) {
            return DeviceInput::sButtonMapping[1];
        }
        else {
            return DeviceInput::sButtonMapping[0];
        }
    }
    
    HWND ShowGameWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statFile, Sequence sequence)
    {
        _hInstance = hInstance;
        HWND hGameWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Game start"),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        hParentWnd = hWnd;
        statisticFile = statFile;
        gameSequence = sequence;

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
        static BOOL isStateChanged = TRUE;

        switch (uMsg)
        {
        case WM_CREATE: {
            btnMapping = GetGameButtonMapping(hWnd);
            return 0;
        }
        case WM_DESTROY: {
            if (joyAttached) {
                joyReleaseCapture(JOYID);
            }

            if (game != NULL) {
                delete game;
                game = NULL;
            }
            else {
                DestroyTimer(hWnd);
            }

            statisticWasShow = FALSE;
            if (hParentWnd != NULL) {
                EnableWindow(hParentWnd, TRUE);
                SetActiveWindow(hParentWnd);
            }

            return 0;
        }
        case WM_SHOWWINDOW: {
            timerID = SetTimer(hWnd, TIMER_ID, TIMER_INTERVAL, NULL);
            if (timerID == 0) {
                secondsBeforeStart = 0;
            }
            else {
                secondsBeforeStart++;
            }

            PostMessage(hWnd, WM_TIMER, 0, 0);
            return 0;
        case WM_TIMER:
            if (--secondsBeforeStart != 0) {
                DrawTimerNumber(hWnd);
            }
            else {
                DestroyTimer(hWnd);
                game = new Game(btnMapping, gameSequence, GetMessageTime());
                gameArrow.Draw(hWnd, game->Current(), TRUE);
            }

            return 0;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            if (timerID != 0 && secondsBeforeStart != 0) {
                DrawTimerNumber(hWnd);
            }
            else if (game != NULL && !game->IsEnd()) {
                gameArrow.Draw(hWnd, game->Current(), FALSE);
            }

            EndPaint(hWnd, &ps);
            return 0;
        }
        case WM_KEYDOWN: {
            if (!joyAttached) {
                ProcessBtnInput(hWnd, wParam);
            }

            return 0;
        }
        case MM_JOY2MOVE:
        case MM_JOY1MOVE: {
            if (joyAttached) {
                JOYINFO joyInfo = { 0 };
                joyGetPos(JOYSTICKID1, &joyInfo);
                UINT joyBtn = joyInfo.wButtons;
                if (joyBtn == ZERO_STATE) {
                    isStateChanged = TRUE;
                }
                else if (isStateChanged) {
                    ProcessBtnInput(hWnd, joyBtn);
                    isStateChanged = FALSE;
                }
            }

            return 0;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

#undef TIMER_START_COUNT
#undef TIMER_INTERVAL
#undef TIMER_ID
#undef TIMER_NUMBER_SIZE
#undef FREQUENCY
#undef ZERO_STATE
#undef JOYID