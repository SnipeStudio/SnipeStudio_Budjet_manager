	#define CATID int
	#pragma once

	namespace ssbm
	{
		class category
		{
		public:
			category();
			virtual ~category();
		private:
			CATID id;
			char categoryName[100];
			unsigned int catCount;
			double catSumm;
			bool catType;
			enum Types{expence,profit};
		public:
			// Operator = copy
			void copy(category* src);
			static bool saveCategories();
			static void loadCategories();
			static CATID addCategory();
			static int deleteCategory();
			static CATID selectCategory( bool type);
			static char* getCategoryNameById(CATID id,bool type);
			static bool changeCount(CATID id,double summ, bool type);
		};
	}
