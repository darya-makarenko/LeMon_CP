#include "SaveSequenceProc.h"

HWND HEdit_sequence;
HWND hSaveSequence;
HWND hParentWindow;
ButtonLocStruct BtnLoc;
LabelLocStruct LblLoc;
RECT WinRect;

void ShowDefaultFileName();
void ShowHelpPicture();
void ShowTextLabels();

LRESULT CALLBACK WndSequenceProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string sequence_str, filename;
	std::vector<std::string> input_seq;
	Sequence ss, seq;
	SequenceFileWriter fw;
	SequenceFileReader fr;

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &WinRect);
		hSaveSequence = hWnd;
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BUTTON_SAVE_FILE:
			//getting edit text
			sequence_str = getEditText(HEdit_sequence);

			ss = Sequence();
			input_seq = ss.ParseString(sequence_str);
			if (input_seq.size() == 0)
			{
				MessageBox(
					hWnd,
					TEXT("Please, enter valid step sequence!"),
					TEXT("Invalid symbols"),
					MB_ICONERROR
				);
			}
			else
			{
				//открытие диалога сохранения последовательности
				filename = getFileNameDialog(FALSE);

				seq = Sequence(input_seq);
				fw = SequenceFileWriter(filename);
				fw.writeSequence(seq);
				
			}
			break;

		case ID_BUTTON_OPEN_FILE:
			
				//открытие диалога сохранения последовательности
				filename = getFileNameDialog(TRUE);
				fr = SequenceFileReader(filename);
				fr.SetConfigFile(filename);
				ShowDefaultFileName();
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_SIZE:
		ShowTextLabels();
		ShowDefaultFileName();
		ShowHelpPicture();
		break;

	case WM_PAINT:
		ShowTextLabels();
		ShowDefaultFileName();
		ShowHelpPicture();
		break;

	case WM_DESTROY:
		//разблокировка родительского окна при закрытии дочернего окна

		EnableWindow(hParentWindow, TRUE);
		SetActiveWindow(hParentWindow);
		//разблокировка родительского окна при закрытии дочернего окна
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
	BtnLoc = ButtonLocation;
	LblLoc = LabelLocation;
	hSaveSequence = HSaveSequence;

	RECT rect_save{ window_rect.left + LabelLocation.margin,
		LabelLocation.margin,
		window_rect.left + LabelLocation.margin + LabelLocation.width,
		LabelLocation.margin + LabelLocation.height };

	RECT rect_open{ window_rect.left + LabelLocation.margin,
		LabelLocation.margin * 3 + LabelLocation.height * 2,
		window_rect.left + LabelLocation.margin * 4 + LabelLocation.width,
		LabelLocation.margin * 3 + LabelLocation.height * 3 };

	//label for sequence edit
	std::string txtSeqLabel = "Enter the sequence: ";
	LPCSTR lpTxtSeqLabel = txtSeqLabel.c_str();

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(HSaveSequence, &ps);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, lpTxtSeqLabel,
		txtSeqLabel.size(),
		&rect_save,
		0);

	//sequence edit
	HEdit_sequence = CreateWindow("Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LOWERCASE,
		rect_save.right + LabelLocation.margin, rect_save.top, LabelLocation.width * 2, LabelLocation.height, 
		HSaveSequence, (HMENU)ID_TEXTBOX_SEQUENCE, HInst, 0);

	//save sequence button
	HWND HButtonSaveSequence = makeButton(HInst, HSaveSequence, "save", rect_save.right + LabelLocation.margin * 3 + LabelLocation.width,
		rect_save.bottom + ButtonLocation.margin, ButtonLocation.width / 2, ButtonLocation.height / 2, ID_BUTTON_SAVE_FILE);

	//label for sequence edit
	std::string txtOpenSeqLabel = "Choose default sequence file: ";
	LPCSTR lpTxtOpenSeqLabel = txtOpenSeqLabel.c_str();

	DrawText(hdc, lpTxtOpenSeqLabel,
		txtOpenSeqLabel.size(),
		&rect_open,
		0);

	EndPaint(HSaveSequence, &ps);

	//open sequence button
	HWND HButtonOpenSequence = makeButton(HInst, HSaveSequence, "open", rect_save.right + LabelLocation.margin * 3 + LabelLocation.width,
		rect_open.top, ButtonLocation.width / 2, ButtonLocation.height / 2, ID_BUTTON_OPEN_FILE);

}

void ShowTextLabels()
{
	RECT rect_save{ WinRect.left + LblLoc.margin,
		LblLoc.margin,
		WinRect.left + LblLoc.margin + LblLoc.width,
		LblLoc.margin + LblLoc.height };

	RECT rect_open{ WinRect.left + LblLoc.margin,
		LblLoc.margin * 3 + LblLoc.height * 2,
		WinRect.left + LblLoc.margin * 4 + LblLoc.width,
		LblLoc.margin * 3 + LblLoc.height * 3 };

	//label for sequence edit
	std::string txtSeqLabel = "Enter the sequence: ";
	LPCSTR lpTxtSeqLabel = txtSeqLabel.c_str();

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hSaveSequence, &ps);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, lpTxtSeqLabel,
		txtSeqLabel.size(),
		&rect_save,
		0);

	//label for sequence edit
	std::string txtOpenSeqLabel = "Choose default sequence file: ";
	LPCSTR lpTxtOpenSeqLabel = txtOpenSeqLabel.c_str();

	DrawText(hdc, lpTxtOpenSeqLabel,
		txtOpenSeqLabel.size(),
		&rect_open,
		0);

	EndPaint(hSaveSequence, &ps);
}

void ShowDefaultFileName()
{
	RECT rect{ WinRect.left + LblLoc.margin * 5 + LblLoc.width,
		LblLoc.margin * 3 + LblLoc.height * 2,
		WinRect.left + LblLoc.margin * 5 + LblLoc.width * 2,
		LblLoc.margin * 3 + LblLoc.height * 3 };

	SequenceFileReader sr = SequenceFileReader();

	//label for sequence edit
	std::string txtSeqLabel = sr.GetSaveSequenceFilename();
	std::size_t filename_pos = txtSeqLabel.find_last_of("/\\");
	txtSeqLabel = txtSeqLabel.substr(filename_pos + 1);
	LPCSTR lpTxtSeqLabel = txtSeqLabel.c_str();

	InvalidateRect(hSaveSequence, &rect, TRUE);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hSaveSequence, &ps);
	
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, lpTxtSeqLabel,
		txtSeqLabel.size(),
		&rect,
		0);

	EndPaint(hSaveSequence, &ps);
}

void ShowHelpPicture()
{
	HDC hDC;
	RECT rect{ WinRect.left + LblLoc.width + LblLoc.margin * 2,
		(WinRect.bottom - WinRect.top) / 2 - LblLoc.margin * 2,
		WinRect.right - LblLoc.width,
		WinRect.bottom - LblLoc.margin
	};

	hDC = GetDC(hSaveSequence);

	HDC hMemDC;
	hMemDC = CreateCompatibleDC(hDC);

	SetGraphicsMode(hDC, GM_ADVANCED);
	
	BITMAP bm;
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, "../Images/help_arrows.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (hBitmap != NULL) {
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		SelectObject(hMemDC, hBitmap);

		BOOL fl = TransparentBlt(hDC, rect.left, rect.top, bm.bmWidth / 6, bm.bmHeight / 6, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));
	}

	DeleteDC(hMemDC);
	ReleaseDC(hSaveSequence, hDC);
}

HWND showCreateSequenceMenu(HINSTANCE hInst, HWND hWnd, LPCTSTR lpzSaveSeq, int width, int height,
	ButtonLocStruct btnloc, LabelLocStruct lls)
{
	hParentWindow = hWnd;
	//bool flag = EnableWindow(hWnd, FALSE);
	HWND HSaveSequence = CreateWindow(lpzSaveSeq, TEXT("SaveSequence"),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX) | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, hWnd, NULL,
		hInst, NULL);

	showSequenceSaveElements(hInst, HSaveSequence, WinRect, btnloc, lls);
	ShowHelpPicture();
	return HSaveSequence;
}