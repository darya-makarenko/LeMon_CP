#include "Game.h"



bool Game::ButtonInput(DeviceButton db, long inputTime)
{
	bool isRight;
	GameButton currGameButton = this->buttonMapping.GetGameButton(db);
	if (!IsEnd() && this->gameButtons.front() == currGameButton) {
		this->gameButtons.pop_front();
		/*
		if (!IsEnd() && gameSequence.getCurrentStep.Direction == currGameButton) {
		gameSequence.moveToNextStep();
		*/

        if (IsEnd()) {
            this->gameStatistic.stopStatistic();
        }

		isRight = true;
	}
	else {
		currGameButton = GameButton_Invalid;
		isRight = false;
	}

	this->gameStatistic.buttonPush(isRight, currGameButton, inputTime);
	return isRight;
}

bool Game::IsEnd()
{
    return this->gameButtons.size() == 0;
}

GameButton Game::Current()
{
    return IsEnd() ? GameButton_Invalid : this->gameButtons.front();
}

GameStatistic Game::getStatistic()
{
	return this->gameStatistic;
}
