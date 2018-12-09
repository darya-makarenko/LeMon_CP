#pragma once

#include <Windows.h>
#include "GameStatistic.h"
#include <stdio.h>

namespace Draw
{
    void DrawStatisticRose(HWND hWnd, RECT *lpRect, GameStatistic *stat);
    void DrawStatisticRose(HWND hWnd, RECT *lpRect, StatStruct *stat);
}