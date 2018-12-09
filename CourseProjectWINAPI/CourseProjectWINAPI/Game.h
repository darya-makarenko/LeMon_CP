#pragma once
#include "GameInput.h"
#include <list>
#include "GameStatistic.h"

class Game
{
public:
    Game(ButtonMapping bm, std::list<GameButton> vGB, long startTime) : buttonMapping(bm), gameButtons(vGB), gameStatistic(startTime) {}
    //Game(ButtonMapping bm, Sequence seq) : buttonMapping(bm), gameSequence(seq) {}
    ~Game() {}
    bool ButtonInput(DeviceButton db, long inputTime);
    bool IsEnd() { return gameButtons.size() == 0; }
    //bool IsEnd() { return gameSequence.IsEnd; }
    GameButton Current() { return IsEnd() ? GameButton_Invalid : gameButtons.front(); }
    //GameButton Current() { return IsEnd() ? GameButton_Invalid : gameSequence.CurrentStep.Direction; }
    GameStatistic getStatistic();

private:
    ButtonMapping buttonMapping;
    std::list<GameButton> gameButtons;
    //Sequence gameSequence;
    GameStatistic gameStatistic;
};



