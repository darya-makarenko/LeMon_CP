#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include "Game.h"
#include "DeviceInput.h"
#include <Wingdi.h>
#include <algorithm>
#include "DrawGraphics.h"
#include "GameArrow.h"
#include "StatisticWriter.h"

namespace GameWindow
{
    HWND ShowGameWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statFile);
    LRESULT CALLBACK GameWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}