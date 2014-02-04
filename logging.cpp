#include "main.h"

namespace ssbm{ std::ofstream logFile; }
//Write log
//modes:
//1 - log only
//2 - both console and log
//0 - console only
int ssbm::writeLog(char* message,unsigned int mode){
	if (mode == 1 || mode == 2)
		ssbm::logFile << message << std::endl;
	if (mode == 0 || mode == 2)
	std::cout << message << std::endl;
	return 0;
}

int ssbm::openLog()
{
	ssbm::logFile.open("ssbm.log", std::ios::app);
	if (ssbm::logFile.is_open())
	{
		//writeLog("Logfile sucsesfully opened", 1);
	}
	else
	{
		writeLog("Could not open log file... exiting", 0);
		return 1;
	}
	return 0;
}

int ssbm::closeLog()
{
	ssbm::writeLog("Log file is closing",1);
	ssbm::writeLog("Bye", 2);
	ssbm::logFile.close();
	return 0;
}