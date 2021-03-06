#include "DeviceInput.h"

// Mapping of device buttons and buttons in game
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
		ButtonMapEntry(NUMPAD9, BUTTON_UPRIGHT)),
    //Dance game mat device
    ButtonMapping(
        ButtonMapEntry(MAT_UP, BUTTON_UP),
        ButtonMapEntry(MAT_DOWN, BUTTON_DOWN),
        ButtonMapEntry(MAT_RIGHT, BUTTON_RIGHT),
        ButtonMapEntry(MAT_LEFT, BUTTON_LEFT),
        ButtonMapEntry(MAT_CROSS, BUTTON_UPLEFT),
        ButtonMapEntry(MAT_CIRCLE, BUTTON_UPRIGHT),
        ButtonMapEntry(MAT_SQUARE, BUTTON_DOWNRIGHT),
        ButtonMapEntry(MAT_TRIANGLE, BUTTON_DOWNLEFT))
};