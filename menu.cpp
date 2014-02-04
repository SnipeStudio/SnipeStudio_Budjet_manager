#include "main.h"
#define Categories 4
namespace ssbm
{

	double balance;

	int menu()
	{
		std::ifstream balance_file;
		std::ofstream balance_out;
		unsigned int Select = 0;
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
			ssbm::getVersion(0);
			char* logbuff = new char[100];
			sprintf(logbuff, "Your current balance is %.2f RUR", balance);
			writeLog(logbuff, 2);
			delete[] logbuff;
			std::cout	<<	"1) Expense"				<< std::endl;
			std::cout	<<	"2) Income"					<< std::endl;
			std::cout	<<	"3) Add new category"		<<std::endl;
			std::cout	<<	"4) Exit"					<< std::endl;
			ssbm::getCopyRight(0);
			char Changer = std::cin.get();
			if(!isdigit(Changer))
			{
				writeLog("Invalid input presented",1);
				continue;
			}
			char summ_ch[20];
			//double summ;
			CATID category = 0;
			
			switch (Changer)
			{
			case '1':
				{
					system("cls");
					ssbm::getVersion(0);
					std::cout<<"Specify what category you select"<<std::endl;
					category=category::selectCategory(false);
					ssbm::getCopyRight(0);
					system("cls");
					ssbm::getVersion(0);
					std::cout<<"Specify how much money you spent on "<<category::getCategoryNameById(category,false)<<std::endl;
					std::cin>>summ_ch;
					std::cout<<summ_ch<<std::endl<<ssbm::checkSumm(summ_ch);

					ssbm::getCopyRight(0);
					break;
				}
			default:
				continue;
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
