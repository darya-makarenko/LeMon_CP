#include "Statistic.h"

double Statistic::getAverageTime()
{
	if (count != 0) {
		return waitTime / (double)count;
	}
	return 0.0;
}

void Statistic::addTime(long waitTime)
{
	count++;
	(*this).waitTime += waitTime;
}
