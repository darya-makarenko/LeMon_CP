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

std::vector<StatStruct> StatisticReader::findStatisticByDate(std::string date)
{
	std::ifstream in(currentFile.c_str(), std::ifstream::in | std::ifstream::binary);
	std::vector<StatStruct> stat_vec;
	StatStruct temp;

	while (in.read((char*)&temp, sizeof(StatStruct))) {
		if (std::strncmp(temp.date, date.c_str(), 11) == 0)
		{
			stat_vec.push_back(temp);
		}
	};
	in.close();
	return stat_vec;
}


