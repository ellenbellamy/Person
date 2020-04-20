#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"

using namespace std;

int main()
{
	Person person("Anna", "Mary", "Smith");
	cout << person;


	ofstream out;
	out.open("Persons.db", std::ios_base::app);

	out << person;

	out.close();


	return 0;
}