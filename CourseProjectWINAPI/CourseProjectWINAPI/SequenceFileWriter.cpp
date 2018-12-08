#include "SequenceFileWriter.h"


SequenceFileWriter::SequenceFileWriter(void)
{
}

SequenceFileWriter::SequenceFileWriter(std::string filename)
{
	SequenceFileWriter::currentFile = filename;
}

SequenceFileWriter::~SequenceFileWriter(void)
{
}

void SequenceFileWriter::writeStep(std::wstring dir)
{
	std::wofstream fout(SequenceFileWriter::currentFile, std::ios::app);
	//const char* direction = dir.c_str();
	fout << dir << std::endl;
	fout.close();
}


void SequenceFileWriter::writeSequence(Sequence sequence)
{
	std::wofstream fout(SequenceFileWriter::currentFile);
	for (int i = 0; i < sequence.getSize(); i++)
	{
		fout << sequence.getCurrentStep().getDirectionStr() << std::endl;
		sequence.moveToNextStep();
	}
	fout.close();
}
