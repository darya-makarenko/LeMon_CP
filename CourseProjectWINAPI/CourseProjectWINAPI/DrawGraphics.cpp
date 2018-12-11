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
#define AXIS_LINE_WIDTH 3
#define ROSE_LINE_WIDTH 3
#define KEY_DEF_STEP 1
#define MAX_X_ELEMENTS_COUNT 5
#define ERR_COLOR RGB(153, 0, 0)
#define TIME_COLOR RGB(76, 153, 0)
#define SHORT_LINE_LENGTH 10
#define TEXT_MARGIN 5

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

        void DrawRoseAxis(HDC hDC, POINT centerPoint, DWORD radius)
        {
            HPEN boldPen, oldPen;
            boldPen = CreatePen(PS_SOLID, AXIS_LINE_WIDTH, RGB(0, 0, 0));
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

        void DrawValue(HDC hDC, RECT *rect, POINT rightUpPoint, char *str)
        {
            RECT textRect = { 0 };
            DrawText(hDC, str, -1, &textRect, DT_CALCRECT);
            if (rightUpPoint.x + textRect.right > rect->right) {
                rightUpPoint.x = rect->right - textRect.right;
            }

            if (rightUpPoint.y + textRect.bottom > rect->bottom) {
                rightUpPoint.y = rect->bottom - textRect.bottom;
            }

            TextOut(hDC, rightUpPoint.x, rightUpPoint.y, str, strlen(str)); 
        }

        void DrawValues(HDC hDC, POINT centerPoint, DWORD radius, std::map<GameButton, double> *keyAvgTime)
        {
            char valueStr[STR_BUF_LEN];
            int strLen;

            RECT roseRect = { centerPoint.x - (LONG)radius, centerPoint.y - (LONG)radius, centerPoint.x + (LONG)radius, centerPoint.y + (LONG)radius };
            int prevBkMode = SetBkMode(hDC, TRANSPARENT);

            //Output text under axis
            centerPoint.y += Y_TEXT_DELTA;
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_RIGHT]);
            DrawValue(hDC, &roseRect, RIGHT_COORDINATE(centerPoint, radius), valueStr);

            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_LEFT]);
            DrawValue(hDC, &roseRect, LEFT_COORDINATE(centerPoint, radius), valueStr);

            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWNLEFT]);
            DrawValue(hDC, &roseRect, DOWNLEFT_COORDINATE(centerPoint, radius), valueStr);

            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWNRIGHT]);
            DrawValue(hDC, &roseRect, DOWNRIGHT_COORDINATE(centerPoint, radius), valueStr);
            centerPoint.y -= Y_TEXT_DELTA;

            //Output text at right side of axis
            centerPoint.x += X_TEXT_DELTA;
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UP]);
            DrawValue(hDC, &roseRect, UP_COORDINATE(centerPoint, radius), valueStr);

            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_DOWN]);
            DrawValue(hDC, &roseRect, DOWN_COORDINATE(centerPoint, radius), valueStr);
            centerPoint.x -= X_TEXT_DELTA;

            //Output text at right side above axis
            centerPoint.y -= Y_TEXT_DELTA;
            centerPoint.x += X_TEXT_DELTA;
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UPRIGHT]);
            DrawValue(hDC, &roseRect, UPRIGHT_COORDINATE(centerPoint, radius), valueStr);

            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*keyAvgTime)[BUTTON_UPLEFT]);
            DrawValue(hDC, &roseRect, UPLEFT_COORDINATE(centerPoint, radius), valueStr);
            centerPoint.y += Y_TEXT_DELTA;
            centerPoint.x -= X_TEXT_DELTA;
            SetBkMode(hDC, prevBkMode);
        }

        void DrawRose(HDC hDC, POINT centerPoint, DWORD side, std::map<GameButton, double> *keyAvgTime)
        {
            DOUBLE step = GetStep(side, keyAvgTime);
            HPEN statPen = CreatePen(PS_SOLID, ROSE_LINE_WIDTH, RGB(0, 255, 0));
            HPEN oldPen = (HPEN)SelectObject(hDC, statPen);

            POINT leftPoint = LEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_LEFT]));
            POINT rightPoint = RIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_RIGHT]));
            POINT upPoint = UP_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UP]));
            POINT downPoint = DOWN_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWN]));
            POINT upleftPoint = UPLEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UPLEFT]));
            POINT uprightPoint = UPRIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_UPRIGHT]));
            POINT downleftPoint = DOWNLEFT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWNLEFT]));
            POINT downrightPoint = DOWNRIGHT_COORDINATE(centerPoint, (int)(step * (*keyAvgTime)[BUTTON_DOWNRIGHT]));

            DrawLine(hDC, rightPoint, uprightPoint);
            DrawLine(hDC, leftPoint, downleftPoint);
            DrawLine(hDC, downleftPoint, downPoint);
            DrawLine(hDC, downrightPoint, rightPoint);
            DrawLine(hDC, downPoint, downrightPoint);
            DrawLine(hDC, uprightPoint, upPoint);
            DrawLine(hDC, upPoint, upleftPoint);
            DrawLine(hDC, upleftPoint, leftPoint);

            DrawValues(hDC, centerPoint, side / 2, keyAvgTime);

            SelectObject(hDC, oldPen);
            DeleteObject(statPen);
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

            DrawRoseAxis(hDC, centerPoint, side / 2);

            DrawRose(hDC, centerPoint, side, keyAvgTime);

            ReleaseDC(hWnd, hDC);
        }

        DWORD GetMaxErrorKeyCount(std::vector<StatStruct> *fullStat)
        {
            DWORD max = 0;
            for (size_t  i = 0; i < fullStat->size(); i++)
            {
                if ((DWORD)((*fullStat)[i].wrong_keys_num) > max) {
                    max = (DWORD)((*fullStat)[i].wrong_keys_num);
                }
            }

            return max;
        }

        DOUBLE GetMaxAvgTime(std::vector<StatStruct> *fullStat)
        {
            DOUBLE max = 0;
            for (size_t i = 0; i < fullStat->size(); i++)
            {
                if ((*fullStat)[i].average_time > max) {
                    max = (*fullStat)[i].average_time;
                }
            }

            return max;
        }

        void DrawShortLine(HDC hDC, POINT point)
        {
            DrawLine(hDC, { point.x - (LONG)(SHORT_LINE_LENGTH / 2), point.y }, {point.x + (LONG)(SHORT_LINE_LENGTH / 2), point.y});
        }

        RECT GetMaxTextRect(HDC hDC, std::string str)
        {
            RECT rect = { 0 };
            DrawText(hDC, str.c_str(), -1, &rect, DT_CALCRECT);
            return rect;
        }

        void DrawCenterText(HDC hDC, POINT point, DWORD textHight, std::string str)
        {
            TextOut(hDC, point.x + TEXT_MARGIN, point.y - textHight, str.c_str(), str.size());
        }

        POINT DrawErrKeysAxis(HDC hDC, RECT rect, DWORD maxCount, DWORD *countIntervals)
        {
            DWORD countStep = 1;
            if (maxCount < *countIntervals) {
                *countIntervals = maxCount;
            }
            else {
                countStep = (DWORD)floor(maxCount / *countIntervals);
            }

            RECT textRect = GetMaxTextRect(hDC, std::to_string(maxCount));
            textRect.right -= TEXT_MARGIN;
            LONG x = rect.right - textRect.right;
            DrawLine(hDC, { x, rect.bottom }, { x, rect.top });

            DOUBLE step = GET_STEP((rect.bottom - rect.top) * 2, *countIntervals);
            for (DWORD i = 0; i <= *countIntervals; i++) {
                POINT point = { x, (LONG)(rect.bottom - i * step) };
                DrawShortLine(hDC, point);
                DrawCenterText(hDC, point, textRect.bottom, std::to_string(i * countStep));
            }

            return { x, rect.bottom };
        }

        POINT DrawTimeAxis(HDC hDC, RECT rect, DOUBLE maxTime, DWORD *countIntervals)
        {
            char valueStr[STR_BUF_LEN];
            int strLen;
            strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", maxTime);
            RECT textRect = GetMaxTextRect(hDC, std::string(valueStr));
            textRect.right += TEXT_MARGIN;
            LONG x = rect.left + textRect.right;
            DrawLine(hDC, { x, rect.bottom }, { x, rect.top });

            DOUBLE step = GET_STEP((rect.bottom - rect.top) * 2, *countIntervals);
            DOUBLE timeStep = maxTime / *countIntervals;
            for (DWORD i = 0; i <= *countIntervals; i++) {
                POINT point = { x, (LONG)(rect.bottom - i * step) };
                DrawShortLine(hDC, point);
                strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", i * timeStep);
                DrawCenterText(hDC, {point.x - textRect.right, point.y }, textRect.bottom, std::string(valueStr));
            }

            return { x, rect.bottom };
        }

        POINT DrawFullStatisticAxis(HDC hDC, RECT rect, std::vector<StatStruct> *fullStat)
        {
            int prevBkMode = SetBkMode(hDC, TRANSPARENT);
            HPEN avgTimePen = CreatePen(PS_SOLID, AXIS_LINE_WIDTH, TIME_COLOR);
            HPEN errCountPen = CreatePen(PS_SOLID, AXIS_LINE_WIDTH, ERR_COLOR);
            DWORD timeIntervalCount = MAX_X_ELEMENTS_COUNT,
                keyIntervalCount = MAX_X_ELEMENTS_COUNT;

            DOUBLE maxAvgTime = GetMaxAvgTime(fullStat);
            DWORD maxErrKeyCount = GetMaxErrorKeyCount(fullStat);
           
            //Count under line text height 

            HPEN oldPen = (HPEN)SelectObject(hDC, avgTimePen);
            POINT timeStartPoint = DrawTimeAxis(hDC, rect, maxAvgTime, &timeIntervalCount);
            SelectObject(hDC, errCountPen);
            POINT keyStartPoint = DrawErrKeysAxis(hDC, rect, maxErrKeyCount, &keyIntervalCount);
            SelectObject(hDC, oldPen);

            DrawLine(hDC, timeStartPoint, keyStartPoint);

            DeleteObject(avgTimePen);
            DeleteObject(errCountPen);
            SetBkMode(hDC, prevBkMode);
            return POINT();
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

    void DrawTimeProgressGraphic(HWND hWnd, RECT *lpRect, std::vector<StatStruct> *fullStat)
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

        POINT zeroPoint = DrawFullStatisticAxis(hDC, rect, fullStat);
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
#undef AXIS_LINE_WIDTH
#undef ROSE_LINE_WIDTH
#undef MAX_X_ELEMENTS_COUNT
#undef ERR_COLOR
#undef TIME_COLOR
