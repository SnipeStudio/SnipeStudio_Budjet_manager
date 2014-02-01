#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstring>
#include <conio.h>

#include "version.h"

#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501
#define _WIN32_IE 0x0600
#ifndef CATEGORIES_INCLUDED
#define SETTINGS_INCLUDED
#include "categories.h"
#endif
#pragma once
#define CATID unsigned int
namespace ssbm{
	int menu();
	void getVersion();
	//logging section
	int openLog();
	int closeLog();
	int writeLog(char* message, unsigned int mode);
	//databasefile handling
	int loadDatabase(char* filename);//Not figured yet
	int updateDatabase(char* filename);//Not figured yet
	int saveDatabase(char* filename);//Not figured yet
	//setting manager
	int loadSettings();//In basic functionality
	//accepting financical changes
	int pay(double summ, CATID id);
	int get(double summ, CATID id);
	void addOperation(double summ, CATID id, bool type);
}
