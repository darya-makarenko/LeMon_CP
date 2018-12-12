#pragma once

#include "Step.h"
#include <sstream>

class Sequence
{
private:
	Step * startStep;
	Step* currentStep;
	Step* lastStep;
	int size;
	bool isEnd;
	int IsValidToken(std::string token);

public:
	Sequence(Step*);
	Sequence(void);
	Sequence(std::vector<std::string> str_vector);
	~Sequence(void);

	int getSize();
	void setStartStep(Step*);
	Step getCurrentStep();
	Step moveToNextStep(void);
	Step resetSequence(void);
	void addNewStep(Step*);
	std::vector<std::string> ParseString(std::string);
    bool IsEnd();
};

