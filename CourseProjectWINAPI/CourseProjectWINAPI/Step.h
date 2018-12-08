#pragma once

#include "DirectionInfo.h"
#include <string>

class Step
{
private:
	GameButton direction;
	Step* nextStep;

public:
	Step(void);
	Step(GameButton, Step* = NULL);
	Step(std::wstring, Step* = NULL);
	~Step(void);
	void setDirection(GameButton);
	void setDirection(std::wstring);
	GameButton getDirection(void);
	std::wstring getDirectionStr(void);
	void setNextStep(Step*);
	Step* getNextStep(void);
};

