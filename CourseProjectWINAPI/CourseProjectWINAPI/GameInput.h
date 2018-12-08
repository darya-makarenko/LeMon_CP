#pragma once
#include <Windows.h>
#include <vector>

enum GameButton {
	BUTTON_LEFT = 0,
	BUTTON_RIGHT = 1,
	BUTTON_UP = 2,
	BUTTON_DOWN = 3,
	BUTTON_UPRIGHT = 4,
	BUTTON_UPLEFT = 5,
	BUTTON_DOWNRIGHT = 6,
	BUTTON_DOWNLEFT = 7,
	GameButton_Invalid = 8
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