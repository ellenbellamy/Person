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

	//typedef tuple<Person, time_t, int> NextCelebrant;
	//NextCelebrant nextCelebrant(tm&) const;
	tuple<Person, time_t, int> nextCelebrant(tm&) const;

	//PersonList& operator=(const PersonList& another);

	friend ostream& operator<<(ostream& out, PersonList& person);
	friend istream& operator>>(istream& out, PersonList& person);


protected:
	list<Person> list;
};

