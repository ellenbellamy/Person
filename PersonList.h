#pragma once
#include <list>
#include "Person.h"
#include <string>
#include <iostream>

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

	tuple<Person, time_t, int> nextCelebrant(tm&) const;

	//PersonList& operator=(const PersonList& another);

	friend ostream& operator<<(ostream&, PersonList&);
	friend istream& operator>>(istream&, PersonList&);

	bool operator==(const PersonList& persons) const {
		return list == persons.list;
	}

	list<Person> filter(const Person&) const;

	ostream& printFiltered(ostream&, Person& filter);


protected:
	list<Person> list;
};

