#include "main.h"
#define Categories 4
namespace ssbm
{

	double balance;
	void getVersion()
	{
		char* logBuff = new char[100];
		sprintf(logBuff, "%s version %s%s for %s", name, MajorVersion, minorVersion, platform);
		ssbm::writeLog(logBuff, 2);
		delete[] logBuff;
	}

	int menu()
	{
		std::ifstream balance_file;
		std::ofstream balance_out;
		unsigned int Changer = 0;
		unsigned int Select = 0;
		char Pos1, Pos2, Pos3, Pos4;
		while (true)
		{
            balance_file.open("balance.db", std::ios::in);
            category::loadCategories();
            if (balance_file.is_open() == 0)
            {
                balance = 0;
            }
            else
            {
                balance_file >> balance;
                balance_file.close();
            }
			system("cls");
			ssbm::getVersion();
			char* logbuff = new char[100];
			sprintf(logbuff, "Your current balance is %.2f RUR", balance);
			writeLog(logbuff, 2);
			delete[] logbuff;
			if (Select == 0)
			{
				Pos1 = '|';
				Pos2 = ' ';
				Pos3 = ' ';
				Pos4 = ' ';
			}
			if (Select == 1)
			{
				Pos1 = ' ';
				Pos2 = '|';
				Pos3 = ' ';
				Pos4 = ' ';
			}
			if (Select == 2)
			{
				Pos1 = ' ';
				Pos2 = ' ';
				Pos3 = '|';
				Pos4 = ' ';
			}
			if (Select == 3)
			{
				Pos1 = ' ';
				Pos2 = ' ';
				Pos3 = ' ';
				Pos4 = '|';
			}
			//	std::cout << name << " " << MajorVersion << minorVersion << " for " << platform << std::endl;
			std::cout<<Pos1<< "1) Expense"             << std::endl;
			std::cout << Pos2 << "2) Income" << std::endl;
			std::cout<<Pos3<< "3) Add new category"    <<std::endl;
			std::cout<<Pos4<< "4) Exit"                << std::endl;

			//std::cin >> Changer;
			Changer = getch();
			double summ;
			CATID category = 0;
			switch (Changer)
			{
			case 230:
				if (Select > 0)
				{
					Select--;
				}
				break;
			case 235:
				if (Select < 4)
				{
					Select++;
				}
				break;
			case 13:
				if (Select == 0)
				{

					std::cout << "What categories of Expence did you specify" << std::endl;
					category = category::selectCategory(0);
					std::cout << "Specify how much money did you spent" << std::endl;
					std::cin >> summ;
					pay(summ, category);
					break;
				}
				if (Select == 1)
				{
					std::cout << "What categories of income did you specify" << std::endl;
					category = category::selectCategory(1);
					std::cout << "Specify how much money did you get" << std::endl;
					std::cin >> summ;
					get(summ, category);
					break;
				}
				if (Select == 2)
				{
					category::addCategory();
					break;
				}
				if (Select == 3)
				{
					balance_out.open("balance.db", std::ios::out);
					balance_out << balance;
					category::saveCategories();
					balance_out.close();
					ssbm::closeLog();
					std::exit(0);
				}
			}
			balance_out.open("balance.db", std::ios::out);
			balance_out << balance;
			category::saveCategories();
			balance_out.close();
		}
		return 0;
	}

	int pay(double summ, CATID id)
	{
		balance -= summ;
		category::changeCount(id, summ, false);
		//addOperation(summ,id,false,category_hold);
		addOperation(summ, id, false);
		return 0;
	}
	int get(double summ, CATID id)
	{
		balance += summ;
		category::changeCount(id, summ, true);
        addOperation(summ,id,true);
		return 0;
	}
	void addOperation(double summ, CATID id, bool type)
	{
		std::ofstream file("operations.ops", std::ios::app);
		time_t t;
		struct tm *t_m;
		t = time(NULL);
		t_m = localtime(&t);
		char side[20];
		if (type == false)
		{
			strcpy(side, "expence");
		}
		else
		{
			strcpy(side, "profit");
		}
		//char catName[100];
		file << t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << " " << summ << " " << side << " " << category::getCategoryNameById(id,type) << std::endl;
		char* debug = new char[255];
		sprintf(debug, "The value was added \n %i:%i:%i %f %s %s", t_m->tm_hour, t_m->tm_min, t_m->tm_sec, summ, side, category::getCategoryNameById(id, type));
		writeLog(debug,1);
		file.close();
	}
}
