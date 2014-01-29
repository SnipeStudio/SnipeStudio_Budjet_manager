#include "main.h"
namespace ssbm
{

	class category
	{
	public:
		category();
		~category();
		void killList();
		category* operator=(const category& right);
		CATID addElement();
		int deleteElement(CATID id);


	private:
		CATID id;
		char categoryName[50];
		unsigned int catCount;
		category* first;
		category* last;
		category* next;
		category* previous;

	};
	category* category::operator=(const category& right)
	{
		//проверка на самоприсваивание
		if (this == &right) {
			return this;
		}
		this->id = right.id;
		this->catCount = right.catCount;
		this->first = right.first;
		this->last = right.last;
		this->next = right.next;
		this->previous = right.previous;
		return this;
	}
	category::category()
	{
		this->id = 1;
		this->catCount = 1;
		this->first = this;
		this->last = this;
		this->next = nullptr;
		this->previous = nullptr;
	}
	category::~category()
	{
	}
	void category::killList()
	{
		category* buff1,*buff2;
		buff1 = this;
		buff1->first;
		while (buff1->next != nullptr)
		{
			buff2 = buff1;
			buff1 = buff1->next;
			buff1->previous = nullptr;
			buff1->first = buff1;
			delete buff2;
		}
	}
}