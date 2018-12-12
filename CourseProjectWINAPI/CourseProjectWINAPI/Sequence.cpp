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

int Sequence::IsValidToken(std::string token)
{
	if ((atoi(token.c_str()) <= 8) && (atoi(token.c_str()) > 0))
	{
		return atoi(token.c_str());
	}

	return -1;
}


std::vector<std::string> Sequence::ParseString(std::string str)
{
	std::string buf;
	std::stringstream ss(str);

	std::vector<std::string> tokens;

	int res;
	while (ss >> buf)
	{
		if ((res = IsValidToken(buf)) != -1)
		{
			DirectionInfo di = DirectionInfo();
			std::wstring dir = di.GetDirectionText(GameButton(res));
			std::string token_str(dir.begin(), dir.end());
			tokens.push_back(token_str);
		}
	}
	return tokens;
}

Sequence::Sequence(std::vector<std::string> str_vector)
{
	size = 0;
	isEnd = false;
	if (str_vector.size() != 0)
	{
		for (std::vector<std::string>::iterator it = str_vector.begin(); it < str_vector.end(); ++it)
		{
			std::wstring step_str((*it).begin(), (*it).end());
			Sequence::addNewStep(new Step(step_str));
		}
	}
}

bool Sequence::IsEnd()
{
    return isEnd;
}
