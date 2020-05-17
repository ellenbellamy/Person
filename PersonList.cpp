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

Person PersonList::nextCelebrant(tm& timestamp) const
{
	pair<std::list<Person>::const_iterator, int> nextCelebrant(list.begin(), list.begin()->daysUntilBirthday(timestamp));
	for (std::list<Person>::const_iterator i = list.begin(); i != list.end(); i++) {
		int d = i->daysUntilBirthday(timestamp);
		if (d < nextCelebrant.second) {
			nextCelebrant = make_pair(i, d);
		}
	}
	return *nextCelebrant.first;
}

void PersonList::clear()
{
	list.clear();
}
