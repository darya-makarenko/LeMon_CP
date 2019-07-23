#pragma once


class Statistic
{
public:
	Statistic() : waitTime(0), count(0) {};
	double getAverageTime();
	void addTime(long waitTime);

private:
	long waitTime;
	int count;
};

