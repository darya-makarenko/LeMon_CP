#include "StatisticReader.h"



StatisticReader::StatisticReader()
{
}

StatisticReader::StatisticReader(std::string fileName)
{
	currentFile = fileName;
}


StatisticReader::~StatisticReader()
{
}

std::vector<StatStruct> StatisticReader::readStatVector()
{
	std::ifstream in(currentFile.c_str(), std::ifstream::in | std::ifstream::binary);
	std::vector<StatStruct> stat_vec;
	StatStruct temp;

	while (in.read((char*)&temp, sizeof(StatStruct))) {
		stat_vec.push_back(temp);
	};
	in.close();
	return stat_vec;
}

std::vector<StatStruct> StatisticReader::findStatisticByDate(time_t date1, time_t date2)
{
	std::ifstream in(currentFile.c_str(), std::ifstream::in | std::ifstream::binary);
	std::vector<StatStruct> stat_vec;
	StatStruct temp;

	while (in.read((char*)&temp, sizeof(StatStruct))) {
		if (temp.date >= date1 && temp.date <= date2)
		{
			stat_vec.push_back(temp);
		}
	};
	in.close();
	return stat_vec;
}

