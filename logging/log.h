#ifndef LOG
#define LOG
#include <ctime>
#endif
#include "../main.h"
namespace ssbm
{
	int openLog();
	int closeLog();
	int writeLog(char* message, unsigned int mode);
}