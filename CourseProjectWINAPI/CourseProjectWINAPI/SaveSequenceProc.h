#pragma once

#include "Common.h"

LRESULT CALLBACK WndSequenceProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND showCreateSequenceMenu(HINSTANCE hInst, HWND hWnd, LPCTSTR lpzSaveSeq, int width, int height,
	RECT win_rect, ButtonLocStruct btnloc, LabelLocStruct lls);

void showSequenceSaveElements(HINSTANCE HInst, HWND HSaveSequence, RECT window_rect,
	ButtonLocStruct ButtonLocation, LabelLocStruct LabelLocation);
