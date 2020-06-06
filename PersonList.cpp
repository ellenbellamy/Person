#include "PersonList.h"
#include <algorithm>
#include <string>
#include <tuple>

PersonList::PersonList() {
}


PersonList::PersonList(const list<Person>& personList) {
	persons= personList;
}

PersonList::PersonList(const initializer_list<Person>& initPersons) {
	persons = initPersons;
}

bool PersonList::isEmpty() const {
	return persons.empty();
}

void PersonList::add(const Person& aPerson) {
	persons.push_back(aPerson);
}

Person PersonList::front() const {
	return persons.front();
}


list<Person>::iterator PersonList::begin() {
	return persons.begin();
}

list<Person>::iterator PersonList::end() {
	return persons.end();
}

void PersonList::sort() {
	persons.sort();
}

size_t PersonList::size() const
{
	return persons.size();
}

bool PersonList::isSorted() const {
	return is_sorted(persons.begin(), persons.end());
}



void PersonList::addAll(PersonList& anotherList)
{
	persons.insert(persons.end(), anotherList.begin(), anotherList.end());
}

void PersonList::addAll(const list<Person>& anotherList)
{
	persons.insert(persons.end(), anotherList.begin(), anotherList.end());
}



void PersonList::merge(PersonList& anotherList)
{
	persons.merge(anotherList.persons);
}

tuple<Person, time_t, int> PersonList::nextCelebrant(tm& timestamp) const
{
	pair<list<Person>::const_iterator, int> nextCelebrant(persons.begin(), persons.begin()->daysUntilBirthday(timestamp));
	for (list<Person>::const_iterator i = persons.begin(); i != persons.end(); i++) {
		int d = i->daysUntilBirthday(timestamp);
		if (d < nextCelebrant.second) {
			nextCelebrant = make_pair(i, d);
		}
	}

	return tuple<Person, time_t, int>(*nextCelebrant.first, nextCelebrant.second, nextCelebrant.first->getBirthday());
}

tuple<Person, time_t, int> PersonList::nextCelebrant() const
{
	tm ttt = convertTime(time(NULL));
	return nextCelebrant(ttt);
}

list<Person> PersonList::select(const Person& condition) const
{
	list<Person> filtered;
	copy_if(persons.begin(), persons.end(), back_inserter(filtered), [condition](Person p) {
		return p.check(condition);
	});
	return filtered;
}
void PersonList::clear()
{
	persons.clear();
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

ostream& PersonList::printSelected(ostream& out, Person& condition)
{
	return out << select(condition);
}

void PersonList::remove(Person& condition)
{
	persons.remove_if([condition](Person p) {
		return p.check(condition);
	});
}

