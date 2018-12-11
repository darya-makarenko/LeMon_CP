#include "GameArrow.h"

#define FILL_COEF 0.7

GameArrow::GameArrow()
{
    this->currRect = { 0 };
    this->hMemDC = NULL;
    this->hArrowDC = NULL;
    this->hMemBmp = NULL;
    this->hArrowBmp = NULL;
}


GameArrow::~GameArrow()
{
    if (hArrowBmp != NULL) {
        DeleteObject(this->hArrowBmp);
    }

    if (hMemDC != NULL) {
        DeleteDC(hMemDC);
    }

    if (hArrowDC != NULL) {
        DeleteDC(hArrowDC);
    }

    if (hMemBmp != NULL) {
        DeleteObject(hMemBmp);
    }
}

void GameArrow::Draw(HWND hWnd, GameButton btn, BOOL isNext)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    LONG clientHeight = clientRect.bottom - clientRect.top;
    LONG clientWidth = clientRect.right - clientRect.left;
    HDC hDC = GetDC(hWnd);

    BOOL isResize = (currRect.right - currRect.left != clientWidth) || (currRect.bottom - currRect.top != clientHeight);
    if (isNext || hMemDC == NULL || isResize) {
        if (hMemDC == NULL) {
            hMemDC = CreateCompatibleDC(hDC);
        }

        if (isNext && hArrowDC != NULL) {
            DeleteDC(hArrowDC);
            hArrowDC = NULL;
        }

        if (hArrowDC == NULL) {
            hArrowDC = CreateCompatibleDC(hDC);
        }

        HBITMAP hTempBmp;
        if (btn == BUTTON_DOWN || btn == BUTTON_LEFT || btn == BUTTON_RIGHT || btn == BUTTON_UP || btn == BUTTON_DOWN) {
            hArrowBmp = (HBITMAP)LoadImage(NULL, "../Images/arrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
        }
        else {
            hArrowBmp = (HBITMAP)LoadImage(NULL, "../Images/sideArrow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
        }

        hTempBmp = (HBITMAP)SelectObject(hArrowDC, hArrowBmp);
        if (hTempBmp) {
            DeleteObject(hTempBmp);
        }    

        if (isResize || hMemBmp == NULL) {
            if (hMemBmp != NULL) {
                DeleteObject(hMemBmp);
            }
            hMemBmp = CreateCompatibleBitmap(hDC, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
            HBITMAP hTempBmp = (HBITMAP)SelectObject(hMemDC, hMemBmp);
            if (hTempBmp) {
                DeleteObject(hTempBmp);
            }
        }

        BITMAP bm;
        GetObject(hArrowBmp, sizeof(BITMAP), &bm);
        LONG height = bm.bmHeight;
        LONG width = bm.bmWidth;

        if (clientHeight != 0 && clientWidth != 0) {
            if (((DOUBLE)height / clientHeight) >= FILL_COEF && clientHeight <= clientWidth && width <= clientWidth) {
                height = (LONG)(clientHeight * FILL_COEF);
                width = (LONG)(((double)height / bm.bmHeight) * bm.bmWidth);
            }
            if (clientHeight >= clientWidth || ((DOUBLE)width / clientWidth) >= FILL_COEF) {
                width = (DWORD)(clientWidth * FILL_COEF);
                height = (DWORD)(((double)width / bm.bmWidth) * bm.bmHeight);
            }

            int oldMode = SetStretchBltMode(hArrowDC, COLORONCOLOR);
            BOOL fl = StretchBlt(hArrowDC, 0, 0, width, height, hArrowDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }

        XFORM xForm;
        switch (btn)
        {
        case BUTTON_RIGHT:
        case BUTTON_DOWNRIGHT:
            xForm.eM11 = (FLOAT)0;
            xForm.eM12 = (FLOAT)1;
            xForm.eM21 = (FLOAT)-1;
            xForm.eM22 = (FLOAT)0;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        case BUTTON_LEFT:
        case BUTTON_UPLEFT:
            xForm.eM11 = (FLOAT)0;
            xForm.eM12 = (FLOAT)-1;
            xForm.eM21 = (FLOAT)1;
            xForm.eM22 = (FLOAT)0;
            xForm.eDx = (FLOAT) 0.0;
            xForm.eDy = (FLOAT) 0.0;
            break;
        case BUTTON_UP:
        case BUTTON_UPRIGHT:
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

        FillRect(hMemDC, &clientRect, (HBRUSH)COLOR_APPWORKSPACE);

        SetGraphicsMode(hMemDC, GM_ADVANCED);
        SetWorldTransform(hMemDC, &xForm);
        BOOL fl = DPtoLP(hMemDC, (LPPOINT)&clientRect, 2);
        TransparentBlt(hMemDC, clientRect.right / 2 - width / 2, clientRect.bottom / 2 - height / 2, width, height, hArrowDC, 0, 0, width, height, RGB(255, 255, 255));
        LPtoDP(hMemDC, (LPPOINT)&clientRect, 2);
        ModifyWorldTransform(hMemDC, NULL, MWT_IDENTITY);

        this->currRect = clientRect;
    }

    StretchBlt(hDC, 0, 0, clientWidth, clientHeight, hMemDC, 0, 0, clientWidth, clientHeight, SRCCOPY);
    ReleaseDC(hWnd, hDC);
}