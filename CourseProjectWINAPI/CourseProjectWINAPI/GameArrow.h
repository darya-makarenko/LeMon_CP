#pragma once

#include <Windows.h>
#include "GameInput.h"

class GameArrow
{
private:
    HBITMAP arrowBmp;
    HBITMAP angleArrowBmp;

public:
    GameArrow();
    void Draw(HWND hWnd, GameButton btn);
    ~GameArrow();
};

