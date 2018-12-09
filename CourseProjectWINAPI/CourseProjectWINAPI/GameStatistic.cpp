#include "GameStatistic.h"

GameStatistic::GameStatistic() : GameStatistic(0) { }

GameStatistic::GameStatistic(long startTime)
{
	lastRightTime = startTime;
	(*this).startTime = startTime;
	counErrorKeys = 0;
	countRightKeys = 0;
}

std::map<GameButton, Statistic> GameStatistic::getButtonsStatistic()
{
	return statisticMap;
}

int GameStatistic::getCountErrorKeys()
{
	return counErrorKeys;
}

long GameStatistic::getPlayTime()
{
	return lastRightTime - startTime;
}

double GameStatistic::getAverageTime()
{
	if (countRightKeys != 0) {
		return getPlayTime() / (double)countRightKeys;
	}
	else {
		return 0.0;
	}
}

int GameStatistic::getCountRightKeys()
{
	return countRightKeys;
}

int GameStatistic::getCountKeys()
{
	return counErrorKeys + countRightKeys;
}

void GameStatistic::buttonPush(bool isRight, GameButton button, long pushTime)
{
	if (isRight) {
		long delta = pushTime - lastRightTime;
		if (delta > 0) {
			lastRightTime = pushTime;
			statisticMap[button].addTime(delta);
			countRightKeys++;
		}
	}
	else {
		counErrorKeys++;
	}
}

time_t GameStatistic::getEndTime()
{
    return this->endTime;
}

void GameStatistic::stopStatistic()
{
    this->endTime = time(0);
}

