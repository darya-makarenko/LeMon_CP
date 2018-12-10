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

bool SequenceFileReader::SetConfigFile(std::string filename)
{
	if (filename == "")
	{
		return false;
	}

	std::ofstream fout(CONFIG_FILENAME, std::ios::trunc);
	fout << filename << std::endl;
	fout.close();

	return true;
}

std::string SequenceFileReader::GetSaveSequenceFilename()
{
	std::ifstream fin(CONFIG_FILENAME);
	std::string filename;
	if (fin.is_open())
	{
		getline(fin, filename);
	}
	fin.close();
	return filename;
}
