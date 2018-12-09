#include "GameArrow.h"



GameArrow::GameArrow()
{
    this->arrowBmp = (HBITMAP)LoadImage(NULL, "../Images/arrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    this->angleArrowBmp = (HBITMAP)LoadImage(NULL, "../Images/sideArrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
}


GameArrow::~GameArrow()
{
    DeleteObject(arrowBmp);
    DeleteObject(angleArrowBmp);
}

void GameArrow::Draw(HWND hWnd, GameButton btn)
{
    HDC hDC;
    XFORM xForm;
    RECT rect;

    hDC = GetDC(hWnd);

    HDC hMemDC;
    hMemDC = CreateCompatibleDC(hDC);

    SetGraphicsMode(hDC, GM_ADVANCED);
    SetMapMode(hDC, MM_LOENGLISH);

    HBITMAP hBitmap;
    BITMAP bm;
    if (btn == BUTTON_DOWN || btn == BUTTON_LEFT || btn == BUTTON_RIGHT || btn == BUTTON_UP || btn == BUTTON_DOWN) {
        hBitmap = this->arrowBmp;
    }
    else if (btn == GameButton_Invalid) {
        hBitmap = NULL;
    }
    else {
        hBitmap = this->angleArrowBmp;
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
    GetClientRect(hWnd, (LPRECT)&rect);
    DPtoLP(hDC, (LPPOINT)&rect, 2);

    if (hBitmap != NULL) {
        GetObject(hBitmap, sizeof(BITMAP), &bm);

        SelectObject(hMemDC, hBitmap);

        BOOL fl = TransparentBlt(hDC, rect.right / 2 - bm.bmWidth / 2, rect.bottom / 2 - bm.bmHeight / 2, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));
    }

    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
}