#include "DrawTable.h"

#define BORDER_LINE_WEIGHT 3
#define INNER_LINE_WEIGHT 2

namespace DrawTable
{
    void DrawLine(HDC hDC, POINT point1, POINT point2)
    {
        MoveToEx(hDC, point1.x, point1.y, (LPPOINT)NULL);
        LineTo(hDC, point2.x, point2.y);
    }

    void Draw(HWND hWnd, RECT *rect, std::vector<std::string> values, DWORD countColumns, DWORD countRows)
    {
        HDC hDC = GetDC(hWnd);

        HPEN borderPen = CreatePen(PS_SOLID, BORDER_LINE_WEIGHT, RGB(0, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hDC, borderPen);

        Rectangle(hDC, rect->left, rect->top, rect->right, rect->bottom);
        
        HPEN innerPen = CreatePen(PS_SOLID, INNER_LINE_WEIGHT, RGB(0, 0, 0));
        SelectObject(hDC, innerPen);
        DeleteObject(borderPen);

        DWORD columnWidth = (rect->right - rect->left) / countColumns;

        DWORD rowHeight = (rect->bottom - rect->top) / countRows;

        HBRUSH headerBrush = CreateSolidBrush(RGB(150, 255, 150));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, headerBrush);
        Rectangle(hDC, rect->left, rect->top, rect->right, rect->top + rowHeight);
        SelectObject(hDC, oldBrush);

        for (DWORD i = 1; i < countColumns; i++) {
            DrawLine(hDC, { rect->left + (LONG)(i * columnWidth), rect->top }, { rect->left + (LONG)(i * columnWidth), rect->bottom });
        }

        for (DWORD i = 1; i < countRows; i++) {
            DrawLine(hDC, { rect->left, rect->top + (LONG)(i * rowHeight) }, { rect->right, rect->top + (LONG)(i * rowHeight) });
        }

        int prevBkMode = SetBkMode(hDC, TRANSPARENT);
        RECT cellRect;
        for (DWORD i = 0; i < countRows; i++) {
            for (DWORD j = 0; j < countColumns; j++) {
                cellRect.top = rect->top + i * rowHeight;
                cellRect.bottom = cellRect.top + rowHeight;
                cellRect.left = rect->left + j * columnWidth;
                cellRect.right = cellRect.left + columnWidth;
                DrawText(hDC, values[(i * countColumns + j)].c_str(), -1, &cellRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_CENTER);
            }
        }

        SetBkMode(hDC, prevBkMode);
        SelectObject(hDC, oldPen);
        ReleaseDC(hWnd, hDC);
    }
}

#undef BORDER_LINE_WEIGHT
#undef INNER_LINE_WEIGHT