#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <math.h>

namespace DrawTable {
    void Draw(HWND hWnd, RECT *rect, std::vector<std::string> values, DWORD countColumns, DWORD countRows);
}

