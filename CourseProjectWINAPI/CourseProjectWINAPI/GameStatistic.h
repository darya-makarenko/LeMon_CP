#pragma once
#include "Statistic.h"
#include "GameInput.h"
#include <map>
#include <time.h>

struct StatStruct
{
	double average_time;
	long all_time;
	int right_keys_num;
	int all_keys_num;
	int wrong_keys_num;
	char date[11];

	double btn_left_time;
	double btn_right_time;
	double btn_up_time;
	double btn_down_time;
	double btn_upright_time;
	double btn_upleft_time;
	double btn_downright_time;
	double btn_downleft_time;
};


class GameStatistic
{
public:
    GameStatistic();
    GameStatistic(long startTime);
	~GameStatistic() {}
	std::map<GameButton, Statistic> getButtonsStatistic();
	int getCountErrorKeys();
	long getPlayTime();
	double getAverageTime();
	int getCountRightKeys();
	int getCountKeys();
	void buttonPush(bool isRight, GameButton button, long pushTime);
    time_t getEndTime();
    void stopStatistic();

private:
	long lastRightTime;
	long startTime;
	int counErrorKeys;
	int countRightKeys;
    time_t endTime;
	std::map<GameButton, Statistic> statisticMap{
		{ BUTTON_DOWN, Statistic() },
		{ BUTTON_UP, Statistic() },
		{ BUTTON_LEFT, Statistic() },
		{ BUTTON_RIGHT, Statistic() },
		{ BUTTON_UPLEFT, Statistic() },
		{ BUTTON_UPRIGHT, Statistic() },
		{ BUTTON_DOWNLEFT, Statistic() },
		{ BUTTON_DOWNRIGHT, Statistic() }
	};
};

