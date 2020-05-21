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
		return persons == persons.persons;
	}

	bool operator==(const list<Person>& personList) const {
		return persons == personList;
	}



	list<Person> select(const Person& condition) const;

	ostream& printSelected(ostream&, Person& condition);

	void remove(Person& condition);

protected:
	list<Person> persons;
};

