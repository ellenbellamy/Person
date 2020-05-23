#pragma once
#include <string>

using namespace std;

class PersonCLI
{
public:
	string process(const string&);

	void start(istream&, ostream&);
};