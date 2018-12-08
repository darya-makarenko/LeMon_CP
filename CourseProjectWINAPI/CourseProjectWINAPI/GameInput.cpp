#include "GameInput.h"

GameButton ButtonMapping::GetGameButton(DeviceButton db)
{
	for (ButtonMapEntry mapEntry : vMaps) {
		if (mapEntry.deviceButton == db) {
			return mapEntry.gameButton;
		}
	}
	return GameButton::GameButton_Invalid;
}
