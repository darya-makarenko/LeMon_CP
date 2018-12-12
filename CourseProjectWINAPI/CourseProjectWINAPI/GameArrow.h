#pragma once

#include <Windows.h>
#include "GameInput.h"
#include <math.h>

class GameArrow
{
private:
    RECT currRect;
    HDC hMemDC,
        hArrowDC;
    HBITMAP hArrowBmp,
        hMemBmp;
public:
    GameArrow();
    void Draw(HWND hWnd, GameButton btn, BOOL isNext);
    ~GameArrow();
};

