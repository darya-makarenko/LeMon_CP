#pragma once

#include <Windows.h>
#include <string>
#include "CommonProc.h"
#include "SequenceFileReader.h"
#include "SequenceFileWriter.h"
#include "StatisticWriter.h"
#include "StatisticReader.h"

// buttons id
#define ID_BUTTON_START 3001
#define ID_BUTTON_CREATE_SEQUENCE 3002
#define ID_BUTTON_SHOW_STATISTICS 3003
#define ID_BUTTON_EXIT 3004
#define ID_BUTTON_SAVE_FILE 3005
#define ID_BUTTON_OPEN_FILE 3008
//edit box id
#define ID_TEXTBOX_SEQUENCE 3006
#define ID_TEXTBOX_FILE_NAME 3007

#define CONFIG_FILENAME "../Data/SEQUENCE_PATH.txt"


struct ButtonLocStruct
{
	int height = 60;
	int width = 150;
	int margin = 30;
};

struct LabelLocStruct
{
	int height = 30;
	int width = 150;
	int margin = 30;
};

