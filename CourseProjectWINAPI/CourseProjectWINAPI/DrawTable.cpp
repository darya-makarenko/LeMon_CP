#include "DrawTable.h"

#define BORDER_LINE_WEIGHT 3
#define INNER_LINE_WEIGHT 1
#define HEADER_COLOR RGB(205, 255, 229)

namespace DrawTable
{
    void DrawLine(HDC hDC, POINT point1, POINT point2)
    {
        MoveToEx(hDC, point1.x, point1.y, (LPPOINT)NULL);
        LineTo(hDC, point2.x, point2.y);
    }

    std::vector<DWORD> CountColumnsWidth(HDC hDC, RECT *rect, DWORD columnCount, std::vector<std::string> *values)
    {
        RECT cellRect = { 0 };
        std::vector<DWORD> columnsWidth(columnCount);
        LONG fullWidth = 0;

        for (size_t i = 0; i < values->size(); i += columnCount) {
            for (DWORD j = 0; j < columnCount; j++) {
                if (i + j < values->size()) {
                    DrawText(hDC, (*values)[i + j].c_str(), -1, &cellRect, DT_CALCRECT);
                    if (columnsWidth[j] < cellRect.right) {
                        columnsWidth[j] = cellRect.right;
                    }
                }
            }
        }

        for (DWORD i = 0; i < columnCount; i++) {
            fullWidth += columnsWidth[i];
        }

        LONG delta = rect->right - rect->left - fullWidth;
        if (delta != 0) {
            if (delta > 0) {
                delta = (LONG)(delta / columnCount);
                for (DWORD i = 0; i < columnCount; i++) {
                    columnsWidth[i] += delta;
                }
            }
            else {
                LONG width = (rect->right - rect->left) / columnCount;
                for (DWORD i = 0; i < columnCount; i++) {
                    columnsWidth[i] = width;
                }
            }
        }

        return columnsWidth;
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

        std::vector<DWORD> columnsWidth = CountColumnsWidth(hDC, rect, countColumns, &values);
    
        DWORD rowHeight = (rect->bottom - rect->top) / countRows;

        HBRUSH headerBrush = CreateSolidBrush(HEADER_COLOR);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, headerBrush);
        Rectangle(hDC, rect->left, rect->top, rect->right, rect->top + rowHeight);
        SelectObject(hDC, oldBrush);

        LONG width = 0;
        for (DWORD i = 0; i < countColumns - 1; i++) {
            width += (LONG)columnsWidth[i];
            DrawLine(hDC, { rect->left + (LONG)(width), rect->top }, { rect->left + (LONG)(width), rect->bottom });
        }

        for (DWORD i = 1; i < countRows; i++) {
            DrawLine(hDC, { rect->left, rect->top + (LONG)(i * rowHeight) }, { rect->right, rect->top + (LONG)(i * rowHeight) });
        }

        int prevBkMode = SetBkMode(hDC, TRANSPARENT);
        RECT cellRect;
        for (DWORD i = 0; i < countRows; i++) {
            DWORD width = 0;
            for (DWORD j = 0; j < countColumns; j++) {
                cellRect.top = rect->top + i * rowHeight;
                cellRect.bottom = cellRect.top + rowHeight;
                cellRect.left = rect->left + width;
                cellRect.right = cellRect.left + columnsWidth[j];
                width += columnsWidth[j];
                if (i * countColumns + j < values.size()) {
                    DrawText(hDC, values[(i * countColumns + j)].c_str(), -1, &cellRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_CENTER);
                }
            }
        }

        SetBkMode(hDC, prevBkMode);
        SelectObject(hDC, oldPen);
        ReleaseDC(hWnd, hDC);
    }
}

#undef BORDER_LINE_WEIGHT
#undef INNER_LINE_WEIGHT
#undef HEADER_COLOR