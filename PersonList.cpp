#include "PersonList.h"
#include <algorithm>

bool PersonList::isEmpty() const {
	return list.empty();
}

void PersonList::add(const Person& aPerson) {
	list.push_back(aPerson);
}

Person PersonList::front() const {
	return list.front();
}


list<Person>::iterator PersonList::begin() {
	return list.begin();
}

list<Person>::iterator PersonList::end() {
	return list.end();
}

void PersonList::sort() {
	list.sort();
}

size_t PersonList::size() const
{
	return list.size();
}

bool PersonList::isSorted() const {
	return is_sorted(list.begin(), list.end());
}

void PersonList::addAll(PersonList& anotherList)
{
	list.insert(list.end(), anotherList.begin(), anotherList.end());
}

void PersonList::merge(PersonList& anotherList)
{
	list.merge(anotherList.list);
}

void PersonList::clear()
{
	list.clear();
}
