#define CATID unsigned int
namespace ssbm
{

	class category
	{
	public:
		category(char* name, bool type);
		category();
		category* operator=(const category& right);
		static bool saveCategories(std::vector<category> cats, unsigned int count);
		static std::vector<category>* loadCategories();
		static int deleteElement(CATID id, std::vector<category>* cat, bool type);
		static CATID addCategory(CATID id, std::vector<category>* cat, bool type);
		static CATID selectCategory(std::vector<category>* cat, bool type);
		static char* getCategoryByID(CATID id, std::vector<category>* cat, bool type);
		static int deleteCategory(CATID id,std::vector<category>* cat, bool type);
		static bool changeCount(CATID id, double summ, std::vector<category>* cat, bool type);
	private:
		CATID id;
		char categoryName[50];
		unsigned int catCount;
		double catSum;
		// 1 is expense
		// 0 is profit
		bool cat_type;

	};

}