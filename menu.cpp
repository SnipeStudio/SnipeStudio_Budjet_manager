#include "main.h"
double balance;
void ssbm::getVersion()
{
	char* logBuff = new char[100];
	sprintf_s(logBuff, 100,"%s version %s%s for %s", name, MajorVersion, minorVersion, platform);
	ssbm::writeLog(logBuff,2);
	delete[] logBuff;
}

int ssbm::menu()
{
	std::ifstream balance_file;
		balance_file.open("balance.db",std::ios::in);
	if(balance_file.is_open()==0)
	{
		balance=0;
	}
	else
	{
		balance_file>>balance;
		balance_file.close();
	}
	unsigned int Changer=0;
	while(Changer!=3)
	{
		system("cls");
			ssbm::getVersion();
		char* logbuff=new char[100];
		sprintf(logbuff,"Your current balance is %.2f RUR",balance);
		writeLog(logbuff,2);
		delete[] logbuff;
//	std::cout << name << " " << MajorVersion << minorVersion << " for " << platform << std::endl;
		std::cout << "1) Expense" << std::endl;
		std::cout << "2) Income" << std::endl;
		std::cout << "3) Exit" <<std::endl;

	std::cin >> Changer;
	double summ;
	CATID category=0;
	switch (Changer)
	{
	case 1:
		std::cout << "What categories of Expence did you specify" << std::endl;
		std::cout << "Specify how much money did you spent" << std::endl;
		std::cin >> summ;
		pay(summ, category);
		break;
	case 2:
		std::cout << "What categories of income did you specify" << std::endl;
		std::cout << "Specify how much money did you get" << std::endl;
		std::cin >> summ;
		get(summ, category);
		break;
	case 3:
		break;
	}

	std::ofstream balance_out;
	balance_out.open("balance.db",std::ios::out);
	balance_out<<balance;
	balance_out.close();
}
	return 0;
}


int ssbm::get(double summ,CATID category)
{
	balance+=summ;
	return 0;
}
int ssbm::pay(double summ,CATID category)
{
	balance-=summ;
	return 0;
}