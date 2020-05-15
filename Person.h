#pragma once

#include <string>
#include <compare>
#include <ctime>
#include <optional>

using namespace std;

class Person
{
public:

	Person();

	Person(
		const optional<string>& firstNameStringOrNull,
		const optional<string>& middleNameStringOrNull,
		const optional<string>& lastNameStringOrNull,
		const optional<string>& birthdayStringOrNull,
		const optional<string>& phoneStringOrNull);

	Person(const Person&);

	string getFirstName() const;

	string getLastName() const;

	string getMiddleName() const;

	time_t getBirthday() const;
	tm getBirthdayTm() const;

	string getPhone() const;

	bool operator==(const Person&) const;
	friend bool operator<(const Person&, const Person&);

	friend ostream& operator<<(ostream& out, const Person& person);
	friend istream& operator>>(istream& out, Person& person);

	Person& operator=(const Person& another);

	int daysUntilBirthday(tm&) const;

	//int daysUntilBirthday() {
	//	return this->daysUntilBirthday(time(NULL));
	//};

	bool check(const Person&) const;

private:
	optional<string> lastName;
	optional<string> firstName;
	optional<string> middleName;

	optional<time_t> birthday;
	optional<tm> birthdayTm;

	optional<string> phone;
};

struct WrongDateFormat : public exception {
	//const char* what() const throw () {
	//	return "C++ Exception";
	//}
};

tm readDateTm(const string&);
time_t readDate(const string&);

tm convertTime(time_t);
