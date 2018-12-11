#pragma once
#include <Windows.h>
#include <vector>

enum GameButton {
	BUTTON_LEFT = 4,
	BUTTON_RIGHT = 5,
	BUTTON_UP = 2,
	BUTTON_DOWN = 7,
	BUTTON_UPRIGHT = 3,
	BUTTON_UPLEFT = 1,
	BUTTON_DOWNRIGHT = 8,
	BUTTON_DOWNLEFT = 6,
	GameButton_Invalid = 0
};

enum DeviceButton {
	NUMPAD1 = VK_NUMPAD1,
	NUMPAD2 = VK_NUMPAD2,
	NUMPAD3 = VK_NUMPAD3,
	NUMPAD4 = VK_NUMPAD4,
	//NUMPAD5 = VK_NUMPAD5,
	NUMPAD6 = VK_NUMPAD6,
	NUMPAD7 = VK_NUMPAD7,
	NUMPAD8 = VK_NUMPAD8,
	NUMPAD9 = VK_NUMPAD9,
    MAT_CROSS = 64,
    MAT_UP = 4,
    MAT_CIRCLE = 128,
    MAT_RIGHT = 8,
    MAT_SQUARE = 32,
    MAT_DOWN = 2,
    MAT_TRIANGLE = 16,
    MAT_LEFT = 1,
	DeviceButton_Invalid
};

struct ButtonMapEntry
{
	ButtonMapEntry() : deviceButton(DeviceButton_Invalid), gameButton(GameButton_Invalid) {}
	ButtonMapEntry(DeviceButton d, GameButton g) : deviceButton(d), gameButton(g) {}
	bool IsEmpty() const { return deviceButton == DeviceButton_Invalid && gameButton == GameButton_Invalid; }

	DeviceButton deviceButton;
	GameButton gameButton;
};

struct ButtonMapping
{
	ButtonMapping(
		ButtonMapEntry bm1 = ButtonMapEntry(),
		ButtonMapEntry bm2 = ButtonMapEntry(),
		ButtonMapEntry bm3 = ButtonMapEntry(),
		ButtonMapEntry bm4 = ButtonMapEntry(),
		ButtonMapEntry bm5 = ButtonMapEntry(),
		ButtonMapEntry bm6 = ButtonMapEntry(),
		ButtonMapEntry bm7 = ButtonMapEntry(),
		ButtonMapEntry bm8 = ButtonMapEntry()
	) {
#define PUSH(bm) { if (!bm.IsEmpty()) vMaps.push_back(bm); }
		PUSH(bm1); PUSH(bm2); PUSH(bm3); PUSH(bm4); PUSH(bm5); PUSH(bm6); PUSH(bm7); PUSH(bm8);
#undef PUSH
	}
	GameButton GetGameButton(DeviceButton db);

	std::vector<ButtonMapEntry> vMaps;
};