#pragma once
#include <string>
#include "GameStatistic.h"
#include <fstream>


class StatisticWriter
{
private:
	std::string currentFile;

public:
	StatisticWriter(void);
	StatisticWriter(std::string);
	~StatisticWriter();
	void writeStat(GameStatistic);
	StatStruct makeSaveStruct(GameStatistic);
    void saveFullStat(std::vector<StatStruct>);
};

