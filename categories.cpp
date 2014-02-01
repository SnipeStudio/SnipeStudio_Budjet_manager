#include "main.h"
namespace ssbm
{
   std::vector<category> category_hold;
	category::category()
	{
		id = 0;
		catCount = 0;
		catSumm = 0.0;
	}

	// Operator = copy
	category category::operator=(const category right)
	{
		category tmp;
		tmp.id = right.id;
		tmp.catCount = right.catCount;
		tmp.catSumm = right.catSumm;
		tmp.catType = right.catType;
		return tmp;
	}

	category::~category()
	{
	}




	bool category::saveCategories()
	{
		std::ofstream categories_file("categories.dll", std::ios::out);
		//ssbm::category cats;
		for (unsigned int i = 0; i < category_hold.size(); i++)
		{
			//cats = category_hold.at(i);
			categories_file << category_hold.at(i).id << " " << category_hold.at(i).categoryName << " " << category_hold.at(i).catCount << " " << category_hold.at(i).catSumm << " " << category_hold.at(i).catType << std::endl;
		}
		category_hold.clear();
		return false;
	}


	void category::loadCategories()
	{
		std::ifstream category_file("categories.dll", std::ios::in);
		if (category_file.is_open())
		{
			category cat_temp;
			bool eof =!category_file.eof();
			while (category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSumm >> cat_temp.catType)
			{
				//if (category_file.eof()) break;
				//category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSumm >> cat_temp.catType;
				category_hold.push_back(cat_temp);
				eof = !category_file.eof();
			}
			category_file.close();
			if (category_hold.size() == 0)
			{
				std::ofstream category_file_new("categories.dll", std::ios::out);
				category_file_new << "0 Default_expence 0 0 0" << std::endl;
				category_file_new << "1 Default_profit 0 0 1";
				category_file_new.close();
				category::loadCategories();
			}
		}
		else
		{
			std::ofstream category_file_new("categories.dll", std::ios::out);
			category_file_new << "0 Default_expence 0 0 0"<<std::endl;
			category_file_new << "1 Default_profit 0 0 1";
			category_file_new.close();
			category::loadCategories();
		}
	}


	CATID category::addCategory()
	{
		category cat_temp;
		std::cout << "Please enter new category name and it's type (0 for expence, 1 for profit)"<<std::endl;
		cat_temp.id=category_hold.at(category_hold.size() - 1).id+1;
		std::cin >>cat_temp.categoryName>>cat_temp.catType;
		category_hold.push_back(cat_temp);
		return cat_temp.id;
	}


	CATID category::selectCategory(bool type)
	{
		CATID id = 0;
		category tmp;
		int size = category_hold.size();
		int pId = 0;
		int** arr = new int*[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = new int[2];
			arr[i][0] = 0;
			arr[i][1] = 0;
		}
		for (int i = 0; i < size; i++)
		{
			if (category_hold.at(i).catType == type)
			{
				pId++;
				arr[pId - 1][0] = pId - 1;
				arr[pId - 1][1] = i;
				std::cout << pId << ") " << category_hold.at(i).categoryName << std::endl;
			}
		}
		CATID ident;
 		ident=49-getch()+1;
		id = category_hold.at(arr[ident - 1][1]).id;
		for (int i = 0; i < size; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
		return id;
	}


	char* category::getCategoryNameById(CATID id, bool type)
	{
		char* catName = new char[100];
		category tmp = category_hold.at(0);
		const int size = category_hold.size();
		for (int i = 0; i < size; i++)
		{
			tmp = category_hold.at(i);
			if (tmp.id == id)
			{
				strcpy(catName, tmp.categoryName);
				break;
			}
		}
		return catName;
	}




	bool category::changeCount(CATID id,double summ,bool type)
	{
		category tmp = category_hold.at(0);
		const int size = category_hold.size();
		for (int i = 0; i < size; i++)
		{
			tmp = category_hold.at(i);
			if (tmp.id == id)
			{
				tmp.catCount++;
				tmp.catSumm++;
				break;
			}
		}
		return false;
	}
}
