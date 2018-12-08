#pragma once

#include <fstream>
#include "Sequence.h"


class SequenceFileReader
{
private:
	std::string currentFile;
public:
	SequenceFileReader(void);
	SequenceFileReader(std::string);
	~SequenceFileReader(void);
	Sequence readFromFile(void);
};

