#include "main.h"
namespace ssbm
{
	std::vector<category> category_hold;
	bool checkSumm(char* summ_ch)
	{
		int i = 0;
		bool valid = false;
		while (summ_ch[i] != '\0')
		{
			if (isdigit(summ_ch[i]) || summ_ch[i] != '.' || summ_ch[i] != ',')
			{
				if ((summ_ch[i] == '.' || summ_ch[i] == ',')&&i == 0)
				{
					valid = false;
				}
				else
				{
					valid = true;
				}
				if (summ_ch[i] == ',')
				{
					summ_ch[i] = '.';
				}


			}
			else
			{
				valid = false;
			}
			i++;
		}
		return valid;
	}
	category::category()
	{
		id = 0;
		catCount = 0;
		catSumm = 0.0;
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
			while (category_file >> cat_temp.id >> cat_temp.categoryName >> cat_temp.catCount >> cat_temp.catSumm >> cat_temp.catType)
			{
				category_hold.push_back(cat_temp);
			}
			category_file.close();
			if (category_hold.size() == 0)
			{
				std::ofstream category_file_new("categories.dll", std::ios::out);
				category_file_new << "0 Default_expence 0 0 0" << std::endl;
				category_file_new << "1 Default_profit 0 0 1";
				category_file_new.close();
			}
		}
		else
		{
			std::ofstream category_file_new("categories.dll", std::ios::out);
			category_file_new << "0 Default_expence 0 0 0" << std::endl;
			category_file_new << "1 Default_profit 0 0 1";
			category_file_new.close();
		}
	}


	CATID category::addCategory()
	{
		category cat_template;
		std::cout << "Please enter new category name" << std::endl;
		if (category_hold.size() != 0)
			cat_template.id = category_hold.at(category_hold.size() - 1).id + 1;
		else
			cat_template.id = 0;
		char* catName=new char[100];
		std::cin >> catName;
		strcpy(cat_template.categoryName, catName);
		std::cout << "Please enter new category type (0 for expence, 1 for profit)" << std::endl;
		char* type = new char[2];
		std::cin >> type;
		if (*type != '0' && *type != '1')
		{
			writeLog((char*)"Invalid data presented", 2);
			return 0;
		}
		else
		{
			if (*type == '0')
			{
				cat_template.catType = cat_template.expence;
			}
			else
			{
				cat_template.catType = cat_template.profit;
			}
			category_hold.push_back(cat_template);
			int id = cat_template.id;
			return id;
		}

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
		if (pId == 0)
		{
			writeLog((char*)"There are no categories yet, but you can add your own", 2);
			addCategory();
			return -1;
		}
		char ident_c;
		std::cin >> ident_c;
		if (isdigit(ident_c))
		{
			CATID ident = ident_c;
			ident -= 49;
			if (ident >= 0)
			{
				id = category_hold.at(arr[ident][1]).id;
				for (int i = 0; i < size; i++)
				{
					delete[] arr[i];
				}
				delete[] arr;
				return id;
			}
			else
				return 0;
		}
		return -1;
	}


	char* category::getCategoryNameById(CATID id, bool type)
	{
		char* catName = new char[100];
		const int size = category_hold.size();
		for (int i = 0; i < size; i++)
		{
			if (category_hold.at(i).id == id)
			{
				strcpy(catName, category_hold.at(i).categoryName);
				break;
			}
		}
		return catName;
	}




	bool category::changeCount(CATID id, double summ, bool type)
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
		return 0;
	}
	int category::deleteCategory()
	{
		category tmp;
		int size = category_hold.size();
		if (size == 0)
		{
			writeLog((char*)"Trying to delete empty category folder", 2);
			return 2;
		}
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

			pId++;
			arr[pId - 1][0] = pId - 1;
			arr[pId - 1][1] = i;
			std::cout << pId << ") " << category_hold.at(i).categoryName << std::endl;
		}
		char* ident_c = new char[20];
		std::cin >> ident_c;
		if (isdigit(*ident_c))
		{
			CATID ident = atoi(ident_c)-1;
			if (ident >= 0)
			{

				tmp.copy(&category_hold.at(size - 1));
				category_hold.at(arr[ident][1]).copy(&tmp);
				tmp.copy(&category_hold.at(size - 1));
				category_hold.pop_back();
				for (int i = 0; i < size; i++)
				{
					delete[] arr[i];
				}
				delete[] arr;
			}
			else
				return 0;
		}
		return 1;
	}

	void category::copy(category* src)
	{
		this->id = src->id;
		strcpy(this->categoryName, src->categoryName);
		this->catCount = src->catCount;
		this->catSumm = src->catSumm;
		this->catType = src->catType;
	}
}
