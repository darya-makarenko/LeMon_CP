#pragma once
#include "GameInput.h"
#include <list>
#include "GameStatistic.h"

class Game
{
public:
	Game(ButtonMapping bm, std::list<GameButton> vGB, long startTime) : buttonMapping(bm), gameButtons(vGB), gameStatistic(startTime) {}
	~Game() {}
	bool ButtonInput(DeviceButton db, long inputTime);
	bool IsEnd() { return gameButtons.size() == 0; }
	
	GameButton Current() { return IsEnd() ? GameButton_Invalid : gameButtons.front(); }
	
	GameStatistic getStatistic();

private:
	ButtonMapping buttonMapping;
	std::list<GameButton> gameButtons;
	
	GameStatistic gameStatistic;
};



