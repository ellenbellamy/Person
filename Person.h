#pragma once

#include <string>
#include <compare>
#include <ctime>

using namespace std;

class Person
{
public:

	Person();

	Person(
		const string& firstNameString,
		const string& middleNameString,
		const string& lastNameString,
		const string& birthdayString,
		const string& phoneString);

	Person(const Person&);

	string getFirstName() const;

	string getLastName() const;

	string getMiddleName() const;

	time_t getBirthday() const;
	tm getBirthdayTm() const;


	bool operator==(const Person&) const;
	friend bool operator<(const Person&, const Person&);

	friend ostream& operator<<(ostream& out, const Person& person);
	friend istream& operator>>(istream& out, Person& person);

	Person& operator=(const Person& another);

	int daysUntilBirthday(tm&) const;

	//int daysUntilBirthday() {
	//	return this->daysUntilBirthday(time(NULL));
	//};

private:
	string lastName;
	string firstName;
	string middleName;

	time_t birthday;
	tm birthdayTm;

	string phone;
};

struct WrongDateFormat : public exception {
	//const char* what() const throw () {
	//	return "C++ Exception";
	//}
};

tm readDateTm(const string&);
time_t readDate(const string&);

tm convertTime(time_t);
