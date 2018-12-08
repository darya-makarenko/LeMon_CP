#include "DeviceInput.h"



const ButtonMapping DeviceInput::sButtonMapping[] =
{
	//Numpad game device
	ButtonMapping(
		ButtonMapEntry(NUMPAD1, BUTTON_DOWNLEFT),
		ButtonMapEntry(NUMPAD2, BUTTON_DOWN),
		ButtonMapEntry(NUMPAD3, BUTTON_DOWNRIGHT),
		ButtonMapEntry(NUMPAD4, BUTTON_LEFT),
		ButtonMapEntry(NUMPAD6, BUTTON_RIGHT),
		ButtonMapEntry(NUMPAD7, BUTTON_UPLEFT),
		ButtonMapEntry(NUMPAD8, BUTTON_UP),
		ButtonMapEntry(NUMPAD9, BUTTON_UPRIGHT))
};