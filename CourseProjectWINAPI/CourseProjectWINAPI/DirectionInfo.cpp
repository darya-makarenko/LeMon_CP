#include "DirectionInfo.h"



DirectionInfo::DirectionInfo()
{
	DirectionInfo::outputMap[GameButton::BUTTON_DOWN] = L"Down";
	DirectionInfo::outputMap[GameButton::BUTTON_DOWNLEFT] = L"DownLeft";
	DirectionInfo::outputMap[GameButton::BUTTON_DOWNRIGHT] = L"DownRight";
	DirectionInfo::outputMap[GameButton::BUTTON_LEFT] = L"Left";
	DirectionInfo::outputMap[GameButton::BUTTON_RIGHT] = L"Right";
	DirectionInfo::outputMap[GameButton::BUTTON_UP] = L"Up";
	DirectionInfo::outputMap[GameButton::BUTTON_UPLEFT] = L"UpLeft";
	DirectionInfo::outputMap[GameButton::BUTTON_UPRIGHT] = L"UpRight";
	DirectionInfo::outputMap[GameButton::GameButton_Invalid] = L"Invalid";

	DirectionInfo::inputMap[L"Down"] = GameButton::BUTTON_DOWN;
	DirectionInfo::inputMap[L"DownLeft"] = GameButton::BUTTON_DOWNLEFT;
	DirectionInfo::inputMap[L"DownRight"] = GameButton::BUTTON_DOWNRIGHT;
	DirectionInfo::inputMap[L"Left"] = GameButton::BUTTON_LEFT;
	DirectionInfo::inputMap[L"Right"] = GameButton::BUTTON_RIGHT;
	DirectionInfo::inputMap[L"Up"] = GameButton::BUTTON_UP;
	DirectionInfo::inputMap[L"UpLeft"] = GameButton::BUTTON_UPLEFT;
	DirectionInfo::inputMap[L"UpRight"] = GameButton::BUTTON_UPRIGHT;
	DirectionInfo::inputMap[L"Invalid"] = GameButton::GameButton_Invalid;
}


DirectionInfo::~DirectionInfo()
{
}

std::wstring DirectionInfo::GetDirectionText(GameButton dir)
{
	return outputMap[dir];
}

GameButton DirectionInfo::DirectionFromString(std::wstring dir)
{
	return inputMap[dir];
}