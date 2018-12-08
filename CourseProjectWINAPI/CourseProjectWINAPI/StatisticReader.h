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
	std::vector<StatStruct> findStatisticByDate(std::string date);
};

