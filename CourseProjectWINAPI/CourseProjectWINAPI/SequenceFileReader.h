#pragma once

#include <fstream>
#include "Sequence.h"
#include "Common.h"


class SequenceFileReader
{
private:
	std::string currentFile;
public:
	SequenceFileReader(void);
	SequenceFileReader(std::string);
	~SequenceFileReader(void);
	Sequence readFromFile(void);
	bool SetConfigFile(std::string);
	std::string GetSaveSequenceFilename(void);
};

