#include "main.h"
namespace ssbm
{
	void getVersion(unsigned int type)
	{
		unsigned int mode=type;
		if(mode!=1||mode!=2||mode!=0)
		{
			mode=2;
		}
		char* logBuff = new char[100];
		sprintf(logBuff, verTemplate, name, MajorVersion, minorVersion, platform);
		ssbm::writeLog(logBuff, mode);
		delete[] logBuff;
	}

	void getCopyRight(unsigned int type)
	{
		unsigned int mode=type;
		if(mode!=1||mode!=2||mode!=0)
		{
			mode=2;
		}
		char* logBuff = new char[100];
		sprintf(logBuff, copyrightTemplate, name, year, authors);//{project}  Copyright (C) {year}  {fullname}
		ssbm::writeLog(logBuff, mode);
		delete[] logBuff;
	}
}