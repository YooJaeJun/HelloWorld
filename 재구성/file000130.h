#include "LinkedList.h"

template<typename T>
LinkedList<T>::LinkedList<T>(int val) : val_(val) {}

LinkedList<T>::LinkedList(int val, LinkedList* next) : val_(val), next_(next) {}

LinkedList::~LinkedList()
{
	while (false == isEmpty())
	{

	}
}

void LinkedList::insert(LinkedList* newList)
{

}

void LinkedList::clear()
{
}

bool LinkedList::isEmpty() const
{
	return nullptr == this;
}

int LinkedList::val() const
{
	return val_;
}

LinkedList* LinkedList::next() const
{
	return next_;
}

void LinkedList::setVal(const int val)
{
	val_ = val;
}

void LinkedList::setNext(LinkedList* next)
{
	next_ = next;
}