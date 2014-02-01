#include "main.h"
namespace ssbm
{
	category* category::operator=(const category& right)
	{
		//проверка на самоприсваивание
		if (this == &right) {
			return this;
		}
		this->id = right.id;
		this->catCount = right.catCount;
		this->catSum = right.catSum;
		this->cat_type = right.cat_type;
		return this;
	}
	category::category(char* name, bool type)
	{
		this->id = 1;
		this->catCount = 1;
		strcpy(this->categoryName, name);
		this->cat_type = type;
	}
	category::category()
	{
		this->id = 1;
		this->catCount = 1;
		strcpy(this->categoryName, "Def");
		this->cat_type = 0;
	}
	bool category::saveCategories(std::vector<category> cats, unsigned int count)
	{
		std::ofstream categories("categories.dll", std::ios::out);
		for (unsigned int i = 0; i < count; i++)
		{
			categories << cats[i].id << " " << cats[i].categoryName << " " << cats[i].catCount << " " << cats[i].catSum << " " << cats[i].cat_type << std::endl;
		}
		categories.close();
		return 0;
	}
	std::vector<category>* category::loadCategories()
	{
		std::vector<category>* category_vec = new std::vector<category>;
		std::ifstream category_file("categories.dll", std::ios::in);
		if (category_file.is_open()){
			category cat_temp = *new category();
			while (!category_file.eof())
			{
				category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSum >> cat_temp.cat_type;
				category_vec->push_back(cat_temp);
			}
			category_file.close();
			return category_vec;
		}
		else
		{
			std::ofstream category_file_new("categories.dll", std::ios::out);
			category_file_new << "0 Def 0 0 0" << std::feof;
			category_file_new.close();
			exit(3);
		}
	}

	CATID category::selectCategory(std::vector<category>* cat, bool type)
	{
		CATID id = 0;
		category tmp;
		int size = cat->size() - 1;
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

			tmp = cat->at(i);
			if (tmp.cat_type == type)
			{
				pId++;
				arr[pId - 1][0] = pId - 1;
				arr[pId - 1][1] = i;
				std::cout << pId << ") " << tmp.categoryName << std::endl;
			}
		}
		CATID ident;
		std::cin >> ident;
		tmp = cat->at(arr[ident - 1][1]);
		id = tmp.id;
		for (int i = 0; i < size; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
		return id;
	}
	bool category::changeCount(CATID id,double summ, std::vector<category>* cat, bool type)
	{
		category tmp = cat->at(0);
		const int size = cat->size();
		for (int i = 0; i < size;i++)
		{
			tmp = cat->at(i);
			if (tmp.id == id)
			{
				tmp.catCount++;
				tmp.catSum++;
				break;
			}
		}
		return false;
	}
	char* category::getCategoryByID(CATID id, std::vector<category>* cat, bool type)
	{
		char* catName = new char[100];
		category tmp = cat->at(0);
		const int size = cat->size();
		for (int i = 0; i < size; i++)
		{
			tmp = cat->at(i);
			if (tmp.id == id)
			{
				strcpy(catName, tmp.categoryName);
				break;
			}
		}
		return catName;
	}
}