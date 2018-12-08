#include "Step.h"


Step::Step(GameButton direction, Step* nextStep)
{
	setDirection(direction);
	setNextStep(nextStep);
}

Step::Step(std::wstring direction, Step* nextStep)
{
	setDirection(direction);
	setNextStep(nextStep);
}

Step::Step(void)
{
}

Step::~Step(void)
{
}

void Step::setDirection(GameButton newDirection)
{
	Step::direction = newDirection;
}

void Step::setDirection(std::wstring newDirection)
{
	/*if (newDirection == "Down")
	{
	setDirection(GameButton::Down);
	}
	if (newDirection == "Up")
	{
	setDirection(GameButton::Up);
	}
	if (newDirection == "Left")
	{
	setDirection(GameButton::Left);
	}
	if (newDirection == "Right")
	{
	setDirection(GameButton::Right);
	}*/
	DirectionInfo di = DirectionInfo();
	setDirection(di.DirectionFromString(newDirection));
}

void Step::setNextStep(Step* stepPtr)
{
	Step::nextStep = stepPtr;
}

GameButton Step::getDirection()
{
	return Step::direction;
}

std::wstring Step::getDirectionStr()
{
	/*switch (Step::direction)
	{
	case GameButton::Down:
	return "Down";
	case GameButton::Up:
	return "Up";
	case GameButton::Left:
	return "Left";
	case GameButton::Right:
	return "Right";
	}*/
	DirectionInfo di = DirectionInfo();
	return di.GetDirectionText(Step::direction);
}

Step* Step::getNextStep()
{
	return Step::nextStep;
}