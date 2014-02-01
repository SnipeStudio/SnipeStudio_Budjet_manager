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
			category operator=(const category right);
			static bool saveCategories();
			static void loadCategories();
			static CATID addCategory();
			static CATID selectCategory( bool type);
			static char* getCategoryNameById(CATID id,bool type);
			static bool changeCount(CATID id,double summ, bool type);
		};
	}
