#pragma once
#include <list>
#include "Person.h"

class PersonList
{
public:
	bool isEmpty() const;

	void add(const Person&);

	Person front() const;

	list<Person>::iterator begin();
	list<Person>::iterator end();

	size_t size() const;


	void clear();


	void sort();

	bool isSorted() const;


	void addAll(PersonList&);
	void merge(PersonList&);

	//typedef tuple<Person, time_t, int> NextCelebrant;
	//NextCelebrant nextCelebrant(tm&) const;
	tuple<Person, time_t, int> nextCelebrant(tm&) const;

protected:
	list<Person> list;
};

