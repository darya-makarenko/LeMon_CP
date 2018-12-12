#include "StatisticWriter.h"


StatisticWriter::StatisticWriter(void)
{
}

StatisticWriter::StatisticWriter(std::string filename)
{
	StatisticWriter::currentFile = filename;
}

StatisticWriter::~StatisticWriter()
{
}

void StatisticWriter::writeStat(GameStatistic stat)
{
	StatStruct save_struct = makeSaveStruct(stat);
	std::ofstream out(currentFile.c_str(), std::ofstream::out | std::ofstream::app | std::ofstream::binary);
	out.write(reinterpret_cast<char*>(&save_struct), sizeof(save_struct));
	out.close();
}

StatStruct StatisticWriter::makeSaveStruct(GameStatistic stat)
{
	time_t dt = time(NULL);

	StatStruct save_struct;

	
	save_struct.average_time = stat.getAverageTime();
	save_struct.all_time = stat.getPlayTime();
	save_struct.right_keys_num = stat.getCountRightKeys();
	save_struct.all_keys_num =  stat.getCountKeys();
	save_struct.wrong_keys_num = stat.getCountErrorKeys();
	
	save_struct.date = dt;

	save_struct.btn_left_time = stat.getButtonsStatistic()[BUTTON_LEFT].getAverageTime();
	save_struct.btn_right_time = stat.getButtonsStatistic()[BUTTON_RIGHT].getAverageTime();
	save_struct.btn_up_time = stat.getButtonsStatistic()[BUTTON_UP].getAverageTime();
	save_struct.btn_down_time = stat.getButtonsStatistic()[BUTTON_DOWN].getAverageTime();
	save_struct.btn_upright_time = stat.getButtonsStatistic()[BUTTON_UPRIGHT].getAverageTime();
	save_struct.btn_upleft_time = stat.getButtonsStatistic()[BUTTON_UPLEFT].getAverageTime();
	save_struct.btn_downright_time = stat.getButtonsStatistic()[BUTTON_DOWNRIGHT].getAverageTime();
	save_struct.btn_downleft_time = stat.getButtonsStatistic()[BUTTON_DOWNLEFT].getAverageTime();

	
	return save_struct;
}

void StatisticWriter::saveFullStat(std::vector<StatStruct> fullStat)
{
    std::ofstream out(currentFile.c_str(), std::ofstream::out | std::ofstream::app | std::ofstream::binary);
    for (size_t i = 0; i < fullStat.size(); i++) {
        StatStruct save_struct = fullStat[i];
        out.write(reinterpret_cast<char*>(&save_struct), sizeof(save_struct));
    }
    out.close();
}