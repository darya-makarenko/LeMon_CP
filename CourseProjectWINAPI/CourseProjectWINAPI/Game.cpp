#include "Game.h"



bool Game::ButtonInput(DeviceButton db, long inputTime)
{
	bool isRight;
	GameButton currGameButton = this->buttonMapping.GetGameButton(db);
	if (!IsEnd() && this->gameSequence.getCurrentStep().getDirection() == currGameButton) {
        this->gameSequence.moveToNextStep();

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
    return this->gameSequence.IsEnd();
}

GameButton Game::Current()
{
    return IsEnd() ? GameButton_Invalid : this->gameSequence.getCurrentStep().getDirection();
}

GameStatistic Game::getStatistic()
{
	return this->gameStatistic;
}
