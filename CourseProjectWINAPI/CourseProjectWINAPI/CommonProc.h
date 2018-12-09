#pragma once

#include "Common.h"

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName, WNDPROC Proc);
HWND makeButton(HINSTANCE HInstance, HWND Hwnd, std::string name, int x, int y,
	int width, int height, int id);
std::string getFileNameDialog(BOOL flSaveOpen);
std::string getEditText(HWND hWnd);
