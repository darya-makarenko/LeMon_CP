#include "Sequence.h"


Sequence::Sequence(Step* startStep)
{
	setStartStep(startStep);
	currentStep = Sequence::startStep;
	lastStep = Sequence::startStep;
	size = 1;
	isEnd = false;
}

Sequence::Sequence(void)
{
	size = 0;
	isEnd = false;
}

Sequence::~Sequence(void)
{
}

void Sequence::setStartStep(Step* startStep)
{
	Sequence::startStep = startStep;
}

Step Sequence::getCurrentStep()
{
	return *Sequence::currentStep;
}

Step Sequence::moveToNextStep()
{
	if ((*currentStep).getNextStep() == NULL)
	{
		isEnd = true;
		resetSequence();
	}
	else
	{
		currentStep = (*currentStep).getNextStep();
		isEnd = false;
	}
	return *currentStep;
}

Step Sequence::resetSequence()
{
	currentStep = startStep;
	return *currentStep;
}

void Sequence::addNewStep(Step* newStep)
{
	if (size == 0)
	{
		setStartStep(newStep);
		currentStep = Sequence::startStep;
	}
	else
	{
		(*lastStep).setNextStep(newStep);
	}
	lastStep = newStep;
	size++;
}

int Sequence::getSize()
{
	return size;
}

