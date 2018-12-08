#pragma once

#include "Step.h"

class Sequence
{
private:
	Step * startStep;
	Step* currentStep;
	Step* lastStep;
	int size;
	bool isEnd;

public:
	Sequence(Step*);
	Sequence(void);
	~Sequence(void);

	int getSize();
	void setStartStep(Step*);
	Step getCurrentStep();
	Step moveToNextStep(void);
	Step resetSequence(void);
	void addNewStep(Step*);
};

