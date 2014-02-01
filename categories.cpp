#include "main.h"
namespace ssbm
{

	category::category()
	{
		id = 0;
		catCount = 0;
		catSumm = 0.0;
	}

	// Operator = copy 
	category* category::operator=(const category& right)
	{
		//проверка на самоприсваивание
		if (this == &right) {
			return this;
		}
		this->id = right.id;
		this->catCount = right.catCount;
		this->catSumm = right.catSumm;
		this->catType = right.catType;
		return this;
	}

	category::~category()
	{
	}




	bool category::saveCategories(std::vector<category> categories, unsigned int count)
	{
		std::ofstream categories_file("categories.dll", std::ios::out);
		category cats;
		for (unsigned int i = 0; i < categories.size(); i++)
		{
			cats = categories.at(i);
			categories_file << cats.id << " " << cats.categoryName << " " << cats.catCount << " " << cats.catSumm << " " << cats.catType << std::endl;
		}
		return false;
	}


	std::vector<category>* category::loadCategories()
	{
		std::vector<category>* category_vec = new std::vector<category>;
		std::ifstream category_file("categories.dll", std::ios::in);
		if (category_file.is_open())
		{
			category cat_temp;
			bool eof =!category_file.eof();
			while (category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSumm >> cat_temp.catType)
			{
				//if (category_file.eof()) break;
				//category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSumm >> cat_temp.catType;
				category_vec->push_back(cat_temp);
				eof = !category_file.eof();
			}
			category_file.close();
			return category_vec;
		}
		else
		{
			std::ofstream category_file_new("categories.dll", std::ios::out);
			category_file_new << "0 Default_expence 0 0 0"<<std::endl;
			category_file_new << "0 Default_profit 0 0 1";
			category_file_new.close();
			exit(3);
		}
	}


	CATID category::addCategory(std::vector<category> category_holder, bool type)
	{
		category cat_temp;
		std::cout << "Please enter new category name and it's type (1 for expence, 0 for profit)"<<std::endl;
		cat_temp.id=category_holder.at(category_holder.size() - 1).id+1;
		std::cin >>cat_temp.categoryName>>cat_temp.catType;
		category_holder.push_back(cat_temp);
		return cat_temp.id;
	}


	CATID category::selectCategory(std::vector<category>* category_holder, bool type)
	{
		CATID id = 0;
		category tmp;
		int size = category_holder->size();
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

			tmp = category_holder->at(i);
			strcpy(tmp.categoryName, category_holder->at(i).categoryName);
			if (tmp.catType == type)
			{
				pId++;
				arr[pId - 1][0] = pId - 1;
				arr[pId - 1][1] = i;
				std::cout << pId << ") " << tmp.categoryName << std::endl;
			}
		}
		CATID ident;
		std::cin >> ident;
		tmp = category_holder->at(arr[ident - 1][1]);
		id = tmp.id;
		for (int i = 0; i < size; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
		return id;
	}


	char* category::getCategoryNameById(CATID id, std::vector<category>* category_holder, bool type)
	{
		char* catName = new char[100];
		category tmp = category_holder->at(0);
		const int size = category_holder->size();
		for (int i = 0; i < size; i++)
		{
			tmp = category_holder->at(i);
			if (tmp.id == id)
			{
				strcpy(catName, tmp.categoryName);
				break;
			}
		}
		return catName;
	}




	bool category::changeCount(CATID id, double summ, std::vector<category>* categoryHolder, bool type)
	{
		category tmp = categoryHolder->at(0);
		const int size = categoryHolder->size();
		for (int i = 0; i < size; i++)
		{
			tmp = categoryHolder->at(i);
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