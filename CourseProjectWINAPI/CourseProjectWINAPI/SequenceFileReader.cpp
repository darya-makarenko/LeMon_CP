#include "SequenceFileReader.h"


SequenceFileReader::SequenceFileReader(void)
{
}

SequenceFileReader::SequenceFileReader(std::string filename)
{
	currentFile = filename;
}

SequenceFileReader::~SequenceFileReader(void)
{
}

Sequence SequenceFileReader::readFromFile()
{
	std::wifstream fin(SequenceFileReader::currentFile);
	Sequence sequence = Sequence();
	std::wstring line;
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			Step* newStep = new Step(line);
			sequence.addNewStep(newStep);
		}
	}
	fin.close();
	return sequence;
}
