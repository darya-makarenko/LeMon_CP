#include "Game.h"



bool Game::ButtonInput(DeviceButton db, long inputTime)
{
	bool isRight;
	GameButton currGameButton = buttonMapping.GetGameButton(db);
	if (!IsEnd() && gameButtons.front() == currGameButton) {
		gameButtons.pop_front();
		/*
		if (!IsEnd() && gameSequence.getCurrentStep.Direction == currGameButton) {
		gameSequence.moveToNextStep();
		*/

        if (IsEnd()) {
            gameStatistic.stopStatistic();
        }

		isRight = true;
	}
	else {
		currGameButton = GameButton_Invalid;
		isRight = false;
	}

	gameStatistic.buttonPush(isRight, currGameButton, inputTime);
	return isRight;
}

GameStatistic Game::getStatistic()
{
	return gameStatistic;
}
