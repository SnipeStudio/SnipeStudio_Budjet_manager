#include "../main.h"
#define Categories 4
#define _CRT_SECURE_NO_WARNINGS
namespace ssbm
{

	double balance;

	int menu()
	{
		std::ifstream balance_file;
		std::ofstream balance_out;
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
		while (true)
		{
			system("cls");
			ssbm::getVersion(0);
			char* logbuff = new char[100];
			sprintf(logbuff, "Your current balance is %.2f RUR", balance);
			writeLog(logbuff, 2);
			delete[] logbuff;
			std::cout << "1) Expense" << std::endl;
			std::cout << "2) Income" << std::endl;
			std::cout << "3) Add new category" << std::endl;
			std::cout << "4) Delete category" << std::endl;
			std::cout << "5) Save"<< std::endl;
			std::cout << "6) Reload Data" << std::endl;
			std::cout << "7) Exit" << std::endl;
			ssbm::getCopyRight(0);
			char Changer = std::cin.get();
			if (!isdigit(Changer))
			{
				writeLog((char*)"Invalid input presented", 1);
				continue;
			}
			CATID category = 0;
			double summ=0;
			char* summ_ch = new char[20],*error;
			switch (Changer)
			{
			case '1':
				{
					system("cls");
					ssbm::getVersion(0);
					std::cout<<"Specify what category you select"<<std::endl;
					category=category::selectCategory(false);
					if (category < 0)
					{
						break;
					}
					ssbm::getCopyRight(0);
					system("cls");
					ssbm::getVersion(0);
					std::cout<<"Specify how much money you spent on "<<category::getCategoryNameById(category,false)<<std::endl;
					std::cin>>summ_ch;
					std::cout<<summ_ch<<std::endl<<ssbm::checkSumm(summ_ch);
					if (ssbm::checkSumm(summ_ch))
						summ = strtod(summ_ch, &error);
					delete[] summ_ch;
					pay(summ, category);
					ssbm::getCopyRight(0);
					break;
				}
			case '2':
			{
						system("cls");
						ssbm::getVersion(0);
						std::cout << "Specify what category you select" << std::endl;
						category = category::selectCategory(true);
						if (category < 0)
						{
							break;
						}
						ssbm::getCopyRight(0);
						system("cls");
						ssbm::getVersion(0);
						std::cout << "Specify how much money you spent on " << category::getCategoryNameById(category, false) << std::endl;
						std::cin >> summ_ch;
						std::cout << summ_ch << std::endl << ssbm::checkSumm(summ_ch);
						if (ssbm::checkSumm(summ_ch))
							summ = strtod(summ_ch, &error);
						delete[] summ_ch;
						get(summ, category);
						ssbm::getCopyRight(0);
						break;
			}
			case '3':
			{
						category::addCategory();
						break;
			}
			case '4':
				category::deleteCategory();
				break;
			case '5':
			{
						balance_out.open("balance.db", std::ios::out);
						balance_out << balance;
						category::saveCategories();
						balance_out.close();
						break;
			}
			case '6':
			{
						category::loadCategories();
						balance_file.open("balance.db", std::ios::in);
						if (balance_file.is_open() == 0)
						{
							balance = 0;
						}
						else
						{
							balance_file >> balance;
							balance_file.close();
						}
						break;
			}
			case '7':
			{
						balance_out.open("balance.db", std::ios::out);
						balance_out << balance;
						category::saveCategories();
						balance_out.close();
						exit(0);
			}
			default:
				continue;
			}
		}
		return 0;
	}

	int pay(double summ, CATID id)
	{
		balance -= summ;
		category::changeCount(id, summ, false);
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
		file <<t_m->tm_year << "\\" << t_m->tm_mon << "\\" << t_m->tm_mday<<" "<< t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << " | " << summ << " " << side << " " << category::getCategoryNameById(id, type) << std::endl;
		char* debug = new char[255];
		sprintf(debug, "The value was added \n %i:%i:%i %f %s %s", t_m->tm_hour, t_m->tm_min, t_m->tm_sec, summ, side, category::getCategoryNameById(id, type));
		writeLog(debug,1);
		file.close();
	}
}
