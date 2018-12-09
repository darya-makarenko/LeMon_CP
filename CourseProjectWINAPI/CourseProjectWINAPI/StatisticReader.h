#pragma once
#include <string>
#include "StatisticWriter.h"
#include <vector>
#include "GameStatistic.h"




class StatisticReader
{
private:
	std::string currentFile;
public:
	StatisticReader();
	StatisticReader(std::string);
	~StatisticReader();
	std::vector<StatStruct> readStatVector();
	std::vector<StatStruct> findStatisticByDate(time_t date1, time_t date2);
};

