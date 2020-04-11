#include <iostream>
#include <string>

using namespace std;

class Person
{

public:

	Person(const string& firstNameString, const string& middleNameString, const string& lastNameString) {
		firstName = firstNameString;
		lastName = middleNameString;
		middleName = lastNameString;
	}

	void print()
	{
		std::cout << firstName << middleName << lastName << std::endl;
	}

private:
	string firstName;
	string middleName;
	string lastName;

};

int main()
{
	Person* person = new Person("Anna", "Mary", "Smith");

	person->print();
	return 0;
}