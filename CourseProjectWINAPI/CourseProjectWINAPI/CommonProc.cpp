#include "Common.h"


HWND makeButton(HINSTANCE HInstance, HWND HWnd, std::string name, int x, int y,
	int width, int height, int id)
{
	LPCSTR caption = name.c_str();
	return CreateWindow("BUTTON",
		caption,
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_OVERLAPPED,
		x, y, width, height, HWnd,
		(HMENU)id, HInstance, NULL);
}

//open-save file dialog
std::string getFileNameDialog(BOOL flSaveOpen)
{
	OPENFILENAME ofn = { 0 };
	char szDirect[260];
	char szFileName[260];
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szDirect;
	*(ofn.lpstrFile) = 0;
	ofn.nMaxFile = sizeof(szDirect);
	//ofn.lpstrFilter = NULL;
	ofn.lpstrFilter = TEXT("Format: SQ\0*.sq\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szFileName;
	*(ofn.lpstrFileTitle) = 0;
	ofn.nMaxFileTitle = sizeof(szFileName);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER;
	if (flSaveOpen)
		GetOpenFileName(&ofn);
	else
		GetSaveFileName(&ofn);
	return szDirect;
}

std::string getEditText(HWND hWnd)
{
	int txtLength = GetWindowTextLength(hWnd);
	LPSTR txtSequence = new CHAR[txtLength + 1];
	GetWindowText(hWnd, txtSequence, txtLength);
	std::string txtResult = txtSequence;
	return txtResult;
}