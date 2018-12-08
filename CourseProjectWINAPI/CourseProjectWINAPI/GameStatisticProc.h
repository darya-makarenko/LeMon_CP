#pragma once

#include <Windows.h>
#include "GameStatistic.h"
#include <map>
#include <string>
#include "DrawGraphics.h"

namespace GameStatisticWindow
{
    HWND ShowGameStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, GameStatistic *stat);
    LRESULT CALLBACK GameStatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

