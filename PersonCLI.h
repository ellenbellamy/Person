#pragma once
#include "PersonList.h"
#include <string>

using namespace std;

class PersonCLI
{
public:
	string process(const string&);

	void start(istream&, ostream&);

	PersonList& getPersons();
	void setPersons(const PersonList& p);


private:
	PersonList persons;
};