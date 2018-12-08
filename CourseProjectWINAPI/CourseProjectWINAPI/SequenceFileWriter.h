#pragma once

#include <fstream> 
#include "Sequence.h"




class SequenceFileWriter
{
private:
	std::string currentFile;
public:
	SequenceFileWriter(void);
	SequenceFileWriter(std::string);
	~SequenceFileWriter(void);
	void writeStep(std::wstring);
	void writeSequence(Sequence);

};

