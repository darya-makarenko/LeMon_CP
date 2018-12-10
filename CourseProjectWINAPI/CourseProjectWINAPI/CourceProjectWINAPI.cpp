#include "SequenceFileReader.h"
#include "SequenceFileWriter.h"
#include "StatisticWriter.h"
#include "StatisticReader.h"
#include "Common.h"
#include "SaveSequenceProc.h"
#include "GameProc.h"
#include "StatisticProc.h"

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void showMenu();
std::string getEditText(HWND hWnd);

//global variables

RECT window_rect;
int width = 700, height = 600;
int window_width, window_height;
HDC hdc;
ButtonLocStruct ButtonLocation; //the relational sizes of button elements
LabelLocStruct LabelLocation; //relational sizes of label elements
std::string statisticFile = "../Data/gameStatistic.dat";


//main windows handles
HWND hWnd;
HWND HSaveSequence;
HINSTANCE HInstance;
LPCTSTR lpzSaveSeq;
LPCTSTR lpGameClass;
LPCTSTR lpStatClass;

//gdi elements
HWND HButton_start;
HWND HButton_create_sequence;
HWND HButton_show_statistics;
HWND HButton_exit;


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE         hPrevInstance,
	LPSTR             lpCmdLine,
	int               nCmdShow)
{
	HInstance = hInstance;
	LPCTSTR lpzClass = TEXT("LeMon");
	if (!RegMyWindowClass(hInstance, lpzClass, (WNDPROC)WndProc))
		return 1;

	lpzSaveSeq = TEXT("SaveSequence");
	if (!RegMyWindowClass(HInstance, lpzSaveSeq, (WNDPROC)WndSequenceProc))
		return 1;

    lpGameClass = TEXT("Game");
    if (!RegMyWindowClass(HInstance, lpGameClass, (WNDPROC)GameWindow::GameWindowProc))
        return 1;

    lpStatClass = TEXT("Statistic");
    if (!RegMyWindowClass(HInstance, lpStatClass, (WNDPROC)StatisticWindow::StatisticWindowProc))
        return 1;

	hWnd = CreateWindow(lpzClass, TEXT("LeMon"),
		(WS_OVERLAPPEDWINDOW) | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
		hInstance, NULL);
	MSG msg = { 0 };
	int iGetOk = 0;

	GetClientRect(hWnd, &window_rect);
	window_width = window_rect.right - window_rect.left;
	window_height = window_rect.bottom - window_rect.top;


	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);
	SetBkMode(hdc, TRANSPARENT);
	showMenu();
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (iGetOk == -1) return 3;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string str;

    switch (message)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BUTTON_START:
            GameWindow::ShowGameWindow(HInstance, hWnd, lpGameClass, width, height, statisticFile);
			break;
		case ID_BUTTON_CREATE_SEQUENCE:
			showCreateSequenceMenu(HInstance, hWnd, lpzSaveSeq, width, height, window_rect, 
				ButtonLocation, LabelLocation);
			break;
		case ID_BUTTON_SHOW_STATISTICS:
            StatisticWindow::ShowStatisticWindow(HInstance, hWnd, lpStatClass, width, height, statisticFile);
			break;
		case ID_BUTTON_EXIT:
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_SIZE:
		break;

	case WM_DESTROY:
		//чекнуть как закрыть дочернее окно но не закрывать родительское
		//сделать блокировку родительского окна на время работы дочернего
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//start menu buttons creation and setting their coordinates
void showMenu()
{
	int X_menu = (window_width - ButtonLocation.width) / 2;
	int Y_menu = (window_height - 4 * ButtonLocation.height -
		3 * ButtonLocation.margin) / 2;
	HButton_start = makeButton(HInstance, hWnd, "start", X_menu, Y_menu, ButtonLocation.width, ButtonLocation.height,
		ID_BUTTON_START);
	HButton_create_sequence = makeButton(HInstance, hWnd, "save", X_menu,
		Y_menu + ButtonLocation.height + ButtonLocation.margin,
		ButtonLocation.width, ButtonLocation.height,
		ID_BUTTON_CREATE_SEQUENCE);
	HButton_show_statistics = makeButton(HInstance, hWnd, "statistics", X_menu,
		Y_menu + 2 * ButtonLocation.height + 2 * ButtonLocation.margin,
		ButtonLocation.width, ButtonLocation.height,
		ID_BUTTON_SHOW_STATISTICS);
	HButton_exit = makeButton(HInstance, hWnd, "exit", X_menu,
		Y_menu + 3 * ButtonLocation.height + 3 * ButtonLocation.margin,
		ButtonLocation.width, ButtonLocation.height,
		ID_BUTTON_EXIT);
}


