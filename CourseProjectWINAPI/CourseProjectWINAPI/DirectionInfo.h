#pragma once

#include <Windows.h>
#include <vector>
#include <unordered_map>
#include "DeviceInput.h"

class DirectionInfo
{
private:
	std::unordered_map<GameButton, std::wstring> outputMap;
	std::unordered_map<std::wstring, GameButton> inputMap;
public:
	DirectionInfo(void);
	~DirectionInfo();
	std::wstring GetDirectionText(GameButton dir);
	GameButton DirectionFromString(std::wstring dir);
};



