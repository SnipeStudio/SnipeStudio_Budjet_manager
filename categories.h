#define CATID unsigned int
#pragma once

namespace ssbm
{

	class category
	{
	public:
		category();
		virtual ~category();
	private:
		unsigned int id;
		char categoryName[100];
		unsigned int catCount;
		double catSumm;
		bool catType;
	public:
		// Operator = copy 
		category* operator=(const category& right);
		static bool saveCategories(std::vector<category> categories, unsigned int count);
		static std::vector<category>* loadCategories();
		static CATID addCategory(std::vector<category> category_holder, bool type);
		static CATID selectCategory(std::vector<category>* category_holder, bool type);
		static char* getCategoryNameById(CATID id, std::vector<category>* category_holder, bool type);
		static bool changeCount(CATID id, double summ, std::vector<category>* categoryHolder, bool type);
	};
}