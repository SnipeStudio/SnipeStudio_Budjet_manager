#ifndef MAIN
#define MAIN
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <cstdlib>
#include <string>

#include "service/version.h"

#ifndef CATEGORIES_INCLUDED
#define SETTINGS_INCLUDED
#include "categories.h"
#endif
#pragma once
#define CATID int
namespace ssbm{
	int menu();
	void getVersion(unsigned int type);
	void getCopyRight(unsigned int type);
	bool checkSumm(char* summ_ch);
	//logging section
	int openLog();
	int closeLog();
	int writeLog(char* message, unsigned int mode);
	//database file handling
	int loadDatabase(char* filename);//Not figured yet
	int updateDatabase(char* filename);//Not figured yet
	int saveDatabase(char* filename);//Not figured yet
	//setting manager
	int loadSettings();//In basic functionality
	//accepting financial changes
	int pay(double summ, CATID id);
	int get(double summ, CATID id);
	void addOperation(double summ, CATID id, bool type);
}
#endif // MAIN
