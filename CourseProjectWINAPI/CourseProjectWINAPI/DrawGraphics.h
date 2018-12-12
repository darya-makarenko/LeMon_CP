#pragma once

#include <Windows.h>
#include "GameStatistic.h"
#include <stdio.h>
#include <math.h>
#include <string>

namespace Draw
{
    void DrawStatisticRose(HWND hWnd, RECT *lpRect, GameStatistic *stat);
    void DrawStatisticRose(HWND hWnd, RECT *lpRect, StatStruct *stat);
    void DrawTimeProgressGraphic(HWND hWnd, RECT *lpRect, std::vector<StatStruct> *fullStat);
}