#include <iostream>
#include <fstream>
#include "version.h"
#include <cstdlib>
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
	//Categories 
	CATID addCategory(CATID id,char** cat);
	CATID selectCategory(char** cat);
	char* getCategoryByID(CATID id, char** cat);
	int deleteCategory(CATID id, char** cat);
	//accepting financical changes
	int pay(double summ,CATID id);
	int get(double summ, CATID id);
}