#include "PersonList.h"
#include <algorithm>
#include <string>

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

tuple<Person, time_t, int> PersonList::nextCelebrant(tm& timestamp) const
{
	pair<std::list<Person>::const_iterator, int> nextCelebrant(list.begin(), list.begin()->daysUntilBirthday(timestamp));
	for (std::list<Person>::const_iterator i = list.begin(); i != list.end(); i++) {
		int d = i->daysUntilBirthday(timestamp);
		if (d < nextCelebrant.second) {
			nextCelebrant = make_pair(i, d);
		}
	}

	return tuple<Person, time_t, int>(*nextCelebrant.first, nextCelebrant.second, nextCelebrant.first->getBirthday());
}

list<Person> PersonList::filter(const Person& filter) const
{
	 std::list<Person> filtered;
	 copy_if(list.begin(), list.end(), back_inserter(filtered), [filter](Person p) {
		 return p.check(filter); 
	 });
	 return filtered;
}
void PersonList::clear()
{
	list.clear();
}

ostream& operator<<(ostream& out, list<Person> persons)
{
	for (list<Person>::iterator i = persons.begin(); i != persons.end(); i++)
	{
		out << (*i) << endl;
	}

	return out;
}

ostream& operator<<(ostream& out, PersonList& persons)
{
	for (list<Person>::iterator i = persons.begin(); i != persons.end(); i++) 
	{
		out << (*i) << endl;
	}

	return out;
}


istream& operator>>(istream& in, PersonList& persons)
{
	Person person;
	while (!in.eof()) 
	{
		in >> person;
		if (in.fail()) 
		{
			break;
		}
		persons.add(person);
	}

	return in;
}

ostream& PersonList::printFiltered(ostream& out, Person& filterPerson)
{
	return out << filter(filterPerson);
}

