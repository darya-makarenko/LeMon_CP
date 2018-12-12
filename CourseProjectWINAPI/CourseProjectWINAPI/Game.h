#pragma once
#include "GameInput.h"
#include <list>
#include "GameStatistic.h"
#include "Sequence.h"

class Game
{
public:
    Game(ButtonMapping bm, Sequence seq, long startTime) : buttonMapping(bm), gameSequence(seq), gameStatistic(startTime) {}
    ~Game() {}
    bool ButtonInput(DeviceButton db, long inputTime);
    bool IsEnd(); 
    GameButton Current(); 
    GameStatistic getStatistic();

private:
    ButtonMapping buttonMapping;
    Sequence gameSequence;
    GameStatistic gameStatistic;
};



