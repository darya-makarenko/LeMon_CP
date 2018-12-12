#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include "GameStatistic.h"
#include "StatisticReader.h"
#include <commctrl.h>
#include "DrawGraphics.h"
#include "DrawTable.h"
#include "CommonProc.h"
#include "StatisticWriter.h"

namespace StatisticWindow
{
    HWND ShowStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statisticFile);
    LRESULT CALLBACK StatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

