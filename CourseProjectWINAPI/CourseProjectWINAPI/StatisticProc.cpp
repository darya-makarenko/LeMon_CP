#include "StatisticProc.h"

#define STR_BUF_LEN 20

namespace StatisticWindow
{
    namespace
    {
        std::vector<StatStruct> fullStatistic;
        HWND hWndList;

        void CreateColumns(HWND hListWnd)
        {
            LV_COLUMN lvc = { 0 };
            RECT rect;

            GetClientRect(hListWnd, &rect);

            lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt = LVCFMT_LEFT;
            lvc.cx = (rect.right - rect.left) / 2;

            lvc.iSubItem = 0;
            char dateColumnName[] = "Date";
            lvc.pszText = dateColumnName;
            ListView_InsertColumn(hListWnd, 0, &lvc);

            lvc.iSubItem = 1;
            char speedColumnName[] = "Avg. Speed";
            lvc.pszText = speedColumnName;
            ListView_InsertColumn(hListWnd, 1, &lvc);
        }

        void FillListView(HWND hListWnd, std::vector<StatStruct> *pFullStat)
        {
            LV_ITEM lvi = { 0 };
            lvi.mask = LVIF_TEXT | LVIF_COLUMNS;
            for (size_t i = 0; i < pFullStat->size(); i++) {
                lvi.iItem = i;
                lvi.iSubItem = 0;
                lvi.pszText = (*pFullStat)[i].date;
                lvi.cColumns = 2;
                ListView_InsertItem(hListWnd, &lvi);

                lvi.iItem = i;
                lvi.iSubItem = 1;
                char valueStr[STR_BUF_LEN];
                int strLen = sprintf_s(valueStr, STR_BUF_LEN, "%.2lf", (*pFullStat)[i].average_time);
                lvi.pszText = valueStr;
                //lvi.cchTextMax = strLen;
                ListView_InsertItem(hListWnd, &lvi);
            }
        }

        void DrawAverageStatisticRose(HWND hWnd, std::vector<StatStruct> *pFullStat)
        {
            StatStruct avgStat = { 0 };
            size_t statCount = pFullStat->size();
            for (size_t i = 0; i < statCount; i++) {
                avgStat.btn_downleft_time += (*pFullStat)[i].btn_downleft_time / statCount;
                avgStat.btn_left_time += (*pFullStat)[i].btn_left_time / statCount;
                avgStat.btn_down_time += (*pFullStat)[i].btn_down_time / statCount;
                avgStat.btn_up_time += (*pFullStat)[i].btn_up_time / statCount;
                avgStat.btn_right_time += (*pFullStat)[i].btn_right_time / statCount;
                avgStat.btn_upleft_time += (*pFullStat)[i].btn_upleft_time / statCount;
                avgStat.btn_downright_time += (*pFullStat)[i].btn_downright_time / statCount;
                avgStat.btn_upright_time += (*pFullStat)[i].btn_upright_time / statCount;
                avgStat.average_time += (*pFullStat)[i].average_time / statCount;
            }

            RECT rect;
            GetClientRect(hWnd, &rect);
            rect.left = rect.left + (rect.right - rect.left) / 2;
            rect.bottom = rect.top + (rect.bottom - rect.top) / 2;
            Draw::DrawStatisticRose(hWnd, &rect, &avgStat);
        }
    }

    HWND ShowStatisticWindow(HINSTANCE hInstance, HWND hWnd, LPCTSTR lpClassName, int width, int height, std::string statisticFile)
    {
        HWND hStatWnd = CreateWindowEx(
            0,
            lpClassName,
            TEXT("Full statistic"),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_BORDER,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            hWnd,
            NULL,
            hInstance,
            NULL
        );

        RECT rect;
        GetClientRect(hStatWnd, &rect);
        INITCOMMONCONTROLSEX icce = { 0 };
        icce.dwICC = ICC_LISTVIEW_CLASSES;
        icce.dwSize = sizeof(icce);
        InitCommonControlsEx(&icce);
        hWndList = CreateWindowEx(
            0L,
            WC_LISTVIEW,
            "",
            WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | WS_BORDER | LVS_SINGLESEL,
            0, 0, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2,
            hStatWnd,
            NULL,
            hInstance,
            NULL
        );
        
        CreateColumns(hWndList);

        StatisticReader reader(statisticFile);
        fullStatistic = reader.readStatVector();

        FillListView(hWndList, &fullStatistic);

        return hStatWnd;
    }

    LRESULT CALLBACK StatisticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
            DrawAverageStatisticRose(hWnd, &fullStatistic);
            EndPaint(hWnd, &ps);
            return 0;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

#undef STR_BUF_LEN
