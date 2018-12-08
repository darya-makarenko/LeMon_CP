#include "SaveSequenceProc.h"

HWND HEdit_sequence;

LRESULT CALLBACK WndSequenceProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string str;
	switch (message)
	{
	case WM_COMMAND:
		switch (wParam)
		{

		case ID_BUTTON_SAVE_FILE:
			//stub for getting edit text
			str = getEditText(HEdit_sequence);
			//getting edit text

			//открытие диалога сохранения последовательности
			str = getFileNameDialog(FALSE);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_SIZE:
		break;

	case WM_DESTROY:
		//чекнуть как закрыть дочернее окно но не закрывать родительское
		//сделать блокировку родительского окна на время работы дочернего
		//PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//Sequence saving elements creation
//vast usage of relational sizes structures
void showSequenceSaveElements(HINSTANCE HInst, HWND HSaveSequence, RECT window_rect, 
	ButtonLocStruct ButtonLocation, LabelLocStruct LabelLocation)
{
	RECT rect{ window_rect.left + LabelLocation.margin,
		LabelLocation.margin,
		window_rect.left + LabelLocation.margin + LabelLocation.width,
		LabelLocation.margin + LabelLocation.height };

	//label for sequence edit
	std::string txtSeqLabel = "Enter the sequence: ";
	LPCSTR lpTxtSeqLabel = txtSeqLabel.c_str();

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(HSaveSequence, &ps);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, lpTxtSeqLabel,
		txtSeqLabel.size(),
		&rect,
		0);

	//sequence edit
	HEdit_sequence = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LOWERCASE,
		rect.right + LabelLocation.margin, rect.top, LabelLocation.width * 2, LabelLocation.height, 
		HSaveSequence, (HMENU)ID_TEXTBOX_SEQUENCE, HInst, 0);

	//save sequence button
	HWND HButtonSaveSequence = makeButton(HInst, HSaveSequence, "remember", rect.right + LabelLocation.margin * 3 + LabelLocation.width,
		rect.bottom + ButtonLocation.margin, ButtonLocation.width / 2, ButtonLocation.height / 2, ID_BUTTON_SAVE_FILE);
}

HWND showCreateSequenceMenu(HINSTANCE hInst, HWND hWnd, LPCTSTR lpzSaveSeq, int width, int height,
	RECT win_rect, ButtonLocStruct btnloc, LabelLocStruct lls)
{
	//bool flag = EnableWindow(hWnd, FALSE);
	HWND HSaveSequence = CreateWindow(lpzSaveSeq, TEXT("SaveSequence"),
		(WS_OVERLAPPEDWINDOW) | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, hWnd, NULL,
		hInst, NULL);

	showSequenceSaveElements(hInst, HSaveSequence, win_rect, btnloc, lls);
	return HSaveSequence;
}