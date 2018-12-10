#include "GameArrow.h"

#define FILL_COEF 0.7

GameArrow::GameArrow()
{
}


GameArrow::~GameArrow()
{
}

void GameArrow::Draw(HWND hWnd, GameButton btn)
{
    HBITMAP hBitmap;
    
    if (btn == BUTTON_DOWN || btn == BUTTON_LEFT || btn == BUTTON_RIGHT || btn == BUTTON_UP || btn == BUTTON_DOWN) {
        hBitmap = (HBITMAP)LoadImage(NULL, "../Images/arrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    }
    else if (btn == GameButton_Invalid) {
        hBitmap = NULL;
    }
    else {
        hBitmap = (HBITMAP)LoadImage(NULL, "../Images/sideArrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    }

    if (hBitmap != NULL)
    {
        HDC hDC;
        XFORM xForm;
        RECT rect;

        hDC = GetDC(hWnd);
        SetGraphicsMode(hDC, GM_ADVANCED);
        SetMapMode(hDC, MM_LOENGLISH);
        int some = FillRect(hDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        GetClientRect(hWnd, (LPRECT)&rect);
        LONG clientHeight = abs(rect.bottom - rect.top);
        LONG clientWidth = abs(rect.right - rect.left);

        /*HRGN hRegion = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRgn(hDC, hRegion, hBrush);*/

        HDC hMemDC;
        hMemDC = CreateCompatibleDC(hDC);    

        BITMAP bm;
        GetObject(hBitmap, sizeof(BITMAP), &bm);
        SelectObject(hMemDC, hBitmap);
        LONG height = bm.bmHeight;
        LONG width = bm.bmWidth;

        if (hBitmap != NULL && clientHeight != 0 && clientWidth != 0) {

            if (((DOUBLE)height / clientHeight) >= FILL_COEF && clientHeight <= clientWidth && width <= clientWidth) {
                height = (LONG)(clientHeight * FILL_COEF);
                width = (LONG)(((double)height / bm.bmHeight) * bm.bmWidth);
            }
            if (clientHeight >= clientWidth || ((DOUBLE)width / clientWidth) >= FILL_COEF) {
                width = (DWORD)(clientWidth * FILL_COEF);
                height = (DWORD)(((double)width / bm.bmWidth) * bm.bmHeight);
            }

            SetStretchBltMode(hMemDC, COLORONCOLOR);
            BOOL fl = StretchBlt(hMemDC, 0, 0, width, height, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }

        switch (btn)
        {
        case BUTTON_RIGHT:
        case BUTTON_UPRIGHT:
            xForm.eM11 = (FLOAT)0;
            xForm.eM12 = (FLOAT)1;
            xForm.eM21 = (FLOAT)-1;
            xForm.eM22 = (FLOAT)0;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        case BUTTON_LEFT:
        case BUTTON_DOWNLEFT:
            xForm.eM11 = (FLOAT)0;
            xForm.eM12 = (FLOAT)-1;
            xForm.eM21 = (FLOAT)1;
            xForm.eM22 = (FLOAT)0;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        case BUTTON_DOWN:
        case BUTTON_DOWNRIGHT:
            xForm.eM11 = (FLOAT)1;
            xForm.eM12 = (FLOAT)0;
            xForm.eM21 = (FLOAT)0;
            xForm.eM22 = (FLOAT)1;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        default:
            xForm.eM11 = (FLOAT)-1;
            xForm.eM12 = (FLOAT)0;
            xForm.eM21 = (FLOAT)0;
            xForm.eM22 = (FLOAT)-1;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        }

        SetWorldTransform(hDC, &xForm);
        DPtoLP(hDC, (LPPOINT)&rect, 2);

        if (hBitmap != NULL) {
            BOOL fl = TransparentBlt(hDC, rect.right / 2 - width / 2, rect.bottom / 2 - height / 2, width, height, hMemDC, 0, 0, width, height, RGB(255, 255, 255));
        }

        DeleteObject(hBitmap);
        DeleteDC(hMemDC);
        ReleaseDC(hWnd, hDC);
    }
}