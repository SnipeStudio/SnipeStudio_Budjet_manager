#include "../log.h"

namespace ssbm{ std::ofstream logFile; }
//Write log
//modes:
//1 - log only
//2 - both console and log
//0 - console only
int ssbm::writeLog(char* message,unsigned int mode){
	time_t t;
	struct tm *t_m;
	t = time(NULL);
	t_m = localtime(&t);
	if (mode == 1 || mode == 2)
		ssbm::logFile << t_m->tm_year << "\\" << t_m->tm_mon << "\\" << t_m->tm_mday << " " << t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << " | " << message << std::endl;
	if (mode == 0 || mode == 2)
	std::cout << message << std::endl;
	return 0;
}

int ssbm::openLog()
{
	
	ssbm::logFile.open("ssbm.log", std::ios::app);
	if (!ssbm::logFile.is_open())
	{
		writeLog((char *)"Could not open log file... exiting", 0);
		return 1;
	}
	return 0;
}

int ssbm::closeLog()
{
	ssbm::logFile.close();
	return 0;
}
