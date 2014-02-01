#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "version.h"
#include "categories.h"
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
	int pay(double summ, CATID id, std::vector<category>* category_hold);
	int get(double summ, CATID id, std::vector<category>* category_hold);
	void addOperation(double summ, CATID id, bool type, std::vector<category>* cat);
}