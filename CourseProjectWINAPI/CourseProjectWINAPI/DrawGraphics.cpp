#include "DrawGraphics.h"

#define SIN 0.70710678118
#define COS 0.70710678118
#define LEFT_COORDINATE(centerPoint, radius) { (int)centerPoint.x - (int)radius, (int)centerPoint.y }
#define RIGHT_COORDINATE(centerPoint, radius) { (int)centerPoint.x + (int)radius, (int)centerPoint.y }
#define DOWN_COORDINATE(centerPoint, radius) { (int)centerPoint.x, (int)centerPoint.y + (int)radius }
#define UP_COORDINATE(centerPoint, radius) { (int)centerPoint.x, (int)centerPoint.y - (int)radius }
#define UPLEFT_COORDINATE(centerPoint, radius) { (int)(centerPoint.x - ((int)radius) * COS), (int)(centerPoint.y - ((int)radius)  * SIN) }
#define DOWNLEFT_COORDINATE(centerPoint, radius) { (int)(centerPoint.x - ((int)radius) * COS), (int)(centerPoint.y + ((int)radius)  * SIN) }
#define UPRIGHT_COORDINATE(centerPoint, radius) { (int)(centerPoint.x + ((int)radius) * COS), (int)(centerPoint.y - ((int)radius)  * SIN) }
#define DOWNRIGHT_COORDINATE(centerPoint, radius) { (int)(centerPoint.x + ((int)radius) * COS), (int)(centerPoint.y + ((int)radius)  * SIN) }
#define GET_STEP(side, max) ((side * 0.9) / (2 * max))
#define X_TEXT_DELTA 10
#define Y_TEXT_DELTA 5
#define STR_BUF_LEN 20

namespace Draw
{
    namespace
    {
        void DrawLine(HDC hDC, POINT point1, POINT point2)
        {
            MoveToEx(hDC, point1.x, point1.y, (LPPOINT)NULL);
            LineTo(hDC, point2.x, point2.y);
        }

        DOUBLE GetStep(DWORD side, std::map<GameButton, double> *keyAvgTime)
        {
            double max = (*keyAvgTime)[BUTTON_DOWN];
            double temp;

            if ((temp = (*keyAvgTime)[BUTTON_UP]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_LEFT]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_RIGHT]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_DOWNRIGHT]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_DOWNLEFT]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_UPRIGHT]) > max) {
                max = temp;
            }

            if ((temp = (*keyAvgTime)[BUTTON_UPLEFT]) > max) {
                max = temp;
            }

            return GET_STEP(side, max);
        }

        void DrawAxis(HDC hDC, POINT centerPoint, DWORD radius)
        {
            HPEN boldPen, oldPen;
            boldPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
            oldPen = (HPEN)SelectObject(hDC, boldPen);

            //Draw horizontal line
            POINT point1 = LEFT_COORDINATE(centerPoint, radius);
            POINT point2 = RIGHT_COORDINATE(centerPoint, radius);
            DrawLine(hDC, point1, point2);

            //Draw vertical line
            point1 = UP_COORDINATE(centerPoint, radius);
            point2 = DOWN_COORDINATE(centerPoint, radius);
            DrawLine(hDC, point1, point2);

            //Draw secondary diagonal line
            point1 = DOWNLEFT_COORDINATE(centerPoint, radius);
            point2 = UPRIGHT_COORDINATE(centerPoint, radius);
            DrawLine(hDC, point1, point2);

            //Draw main diagonal line
            point1 = UPLEFT_COORDINATE(centerPoint, radius);
            point2 = DOWNRIGHT_COORDINATE(centerPoint, radius);
            DrawLine(hDC, point1, point2);

            SelectObject(hDC, oldPen);
        }

        void DrawRose(HDC hDC, POINT centerPoint, double step, std::map<GameButton, double> *keyAvgTime)
        {
            HPEN statPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
            HPEN oldPen = (HPEN)SelectObject(hDC, statPen);
            int prevBkMode = SetBkMode(hDC, TRANSPARENT);
            char valueStr[STR_BUF_LEN];
            int strLen;

            POINT leftPoint = LEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_LEFT]));
            POINT rightPoint = RIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_RIGHT]));
            POINT upPoint = UP_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UP]));
            POINT downPoint = DOWN_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWN]));
            POINT upleftPoint = UPLEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UPLEFT]));
            POINT uprightPoint = UPRIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UPRIGHT]));
            POINT downleftPoint = DOWNLEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWNLEFT]));
            POINT downrightPoint = DOWNRIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWNRIGHT]));

            DrawLine(hDC, rightPoint, uprightPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_RIGHT]);
            TextOut(hDC, rightPoint.x + X_TEXT_DELTA, rightPoint.y + Y_TEXT_DELTA, valueStr, strLen);

            DrawLine(hDC, uprightPoint, upPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UPRIGHT]);
            TextOut(hDC, uprightPoint.x + X_TEXT_DELTA, uprightPoint.y, valueStr, strLen);

            DrawLine(hDC, upPoint, upleftPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UP]);
            TextOut(hDC, upPoint.x + X_TEXT_DELTA, upPoint.y, valueStr, strLen);

            DrawLine(hDC, upleftPoint, leftPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UPLEFT]);
            TextOut(hDC, upleftPoint.x + X_TEXT_DELTA, upleftPoint.y - Y_TEXT_DELTA, valueStr, strLen);

            DrawLine(hDC, leftPoint, downleftPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_LEFT]);
            TextOut(hDC, leftPoint.x + X_TEXT_DELTA, leftPoint.y + Y_TEXT_DELTA, valueStr, strLen);

            DrawLine(hDC, downleftPoint, downPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWNLEFT]);
            TextOut(hDC, downleftPoint.x + X_TEXT_DELTA, downleftPoint.y, valueStr, strLen);

            DrawLine(hDC, downPoint, downrightPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWN]);
            TextOut(hDC, downPoint.x + X_TEXT_DELTA, downPoint.y, valueStr, strLen);

            DrawLine(hDC, downrightPoint, rightPoint);
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWNRIGHT]);
            TextOut(hDC, downrightPoint.x + X_TEXT_DELTA, downrightPoint.y - Y_TEXT_DELTA, valueStr, strLen);

            SetBkMode(hDC, prevBkMode);
            SelectObject(hDC, oldPen);
        }

        void DrawStatisticRose(HWND hWnd, RECT *lpRect, std::map<GameButton, double> *keyAvgTime)
        {
            HDC hDC = GetDC(hWnd);
            RECT rect;
            if (lpRect == NULL) {
                if (!GetClientRect(hWnd, &rect)) {
                    return;
                }
            }
            else {
                rect = *lpRect;
            }

            DWORD width = rect.right - rect.left;
            DWORD height = rect.bottom - rect.top;
            POINT centerPoint;
            centerPoint.x = rect.left + width / 2;
            centerPoint.y = rect.top + height / 2;
            DWORD side;
            if (width < height) {
                side = width;
            }
            else {
                side = height;
            }

            DPtoLP(hDC, (LPPOINT)&rect, 2);
            DrawAxis(hDC, centerPoint, side / 2);

            DOUBLE step = GetStep(side, keyAvgTime);
            DrawRose(hDC, centerPoint, step, keyAvgTime);

            ReleaseDC(hWnd, hDC);
        }
    }

    void DrawStatisticRose(HWND hWnd, RECT *lpRect, GameStatistic *stat)
    {
        std::map<GameButton, Statistic> keysStat = stat->getButtonsStatistic();
        std::map<GameButton, double> keyAvgTime{
            { BUTTON_DOWN, keysStat[BUTTON_DOWN].getAverageTime() },
            { BUTTON_UP, keysStat[BUTTON_UP].getAverageTime() },
            { BUTTON_RIGHT, keysStat[BUTTON_RIGHT].getAverageTime() },
            { BUTTON_LEFT, keysStat[BUTTON_LEFT].getAverageTime() },
            { BUTTON_UPRIGHT, keysStat[BUTTON_UPRIGHT].getAverageTime() },
            { BUTTON_UPLEFT, keysStat[BUTTON_UPLEFT].getAverageTime() },
            { BUTTON_DOWNRIGHT, keysStat[BUTTON_DOWNRIGHT].getAverageTime() },
            { BUTTON_DOWNLEFT, keysStat[BUTTON_DOWNLEFT].getAverageTime() }
        };
        DrawStatisticRose(hWnd, lpRect, &keyAvgTime);
    }

    void DrawStatisticRose(HWND hWnd, RECT *lpRect, StatStruct *stat)
    {
        std::map<GameButton, double> keyAvgTime{
            { BUTTON_DOWN, stat->btn_down_time },
            { BUTTON_UP, stat->btn_up_time },
            { BUTTON_RIGHT, stat->btn_right_time },
            { BUTTON_LEFT, stat->btn_left_time },
            { BUTTON_UPRIGHT, stat->btn_upright_time },
            { BUTTON_UPLEFT, stat->btn_upleft_time },
            { BUTTON_DOWNRIGHT, stat->btn_downright_time },
            { BUTTON_DOWNLEFT, stat->btn_downleft_time }
        };
        DrawStatisticRose(hWnd, lpRect, &keyAvgTime);
    }
}

#undef LEFT_COORDINATE
#undef RIGHT_COORDINATE
#undef UP_COORDINATE
#undef DOWN_COORDINATE
#undef UPRIGHT_COORDINATE
#undef UPLEFT_COORDINATE
#undef DOWNRIGHT_COORDINATE
#undef DOWNLEFT_COORDINATE
#undef COS
#undef SIN
#undef GET_STEP
