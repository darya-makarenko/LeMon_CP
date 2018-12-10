#pragma once

#include <Windows.h>
#include "GameInput.h"
#include <math.h>

class GameArrow
{
public:
    GameArrow();
    void Draw(HWND hWnd, GameButton btn);
    ~GameArrow();
};

