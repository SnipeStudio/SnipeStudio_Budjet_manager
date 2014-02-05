#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{

	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.02";

	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";

	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 8;

	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 16;
	#define RC_FILEVERSION 0,0,1,8
	#define RC_FILEVERSION_STRING "0, 0, 1, 8\0"
	static const char FULLVERSION_STRING [] = "0.0.1.8";

	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 0;


}
const char name[35] = "Snipe Studio Budget manager";
const char MajorVersion[4] = "0.0";
const char minorVersion[5] = ".1";
const char platform[8] = "Windows";
const int year = 2014;
const char verTemplate[25] = "%s version %s%s for %s";
const char copyrightTemplate[50] = "%s  Copyright (C) %i  %s";
const char authors[50] = "Snipe Studio";
#endif //VERSION_H
