#pragma once

#include <string>
#include <compare>
#include <ctime>

using namespace std;

class Person
{
public:

	Person(
		const string& firstNameString, 
		const string& middleNameString, 
		const string& lastNameString,
		const string& birthdayString,
		const string& phoneString);

	string getFirstName() const;

	string getLastName() const;

	string getMiddleName() const;

	time_t getBirthday() const;

	bool operator==(const Person&) const;
	friend bool operator<(const Person&, const Person&);

	//std::strong_ordering operator<=>(const Person&) const;

	friend ostream& operator<<(ostream& out, const Person& person);

private:
	string lastName;
	string firstName;
	string middleName;
	std::time_t birthday;
	string phone;
};

struct WrongDateFormat : public exception {
	//const char* what() const throw () {
	//	return "C++ Exception";
	//}
};

