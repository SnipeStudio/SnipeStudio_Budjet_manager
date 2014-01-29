#include "main.h"

void ssbm::getVersion()
{
	char* logBuff = new char[100];
	sprintf_s(logBuff, 100,"You are using %s version %s%s for %s", name, MajorVersion, minorVersion, platform);
	ssbm::writeLog(logBuff,2);
	delete[] logBuff;
}

int ssbm::menu()
{
	std::cout << name << " " << MajorVersion << minorVersion << " for " << platform << std::endl;
	std::cout << "1) Expense" << std::endl;
	std::cout << "2) Income" << std::endl;
	unsigned int Changer;
	std::cin >> Changer;
	switch (Changer)
	{
	case 1:
		double summ;
		std::cout << "What categories of Expence did you specify" << std::endl;
		CATID category=selectCategory(0);
		std::cout << "Specify how much money did you spent" << std::endl;
		std::cin >> summ;
		pay(summ, category);
		break;
	case 2:
		double summ;
		std::cout << "What categories of income did you specify" << std::endl;
		CATID category = selectCategory(1);
		std::cout << "Specify how much money did you get" << std::endl;
		std::cin >> summ;
		get(summ, category);
		break;
	}
	return 0;
}