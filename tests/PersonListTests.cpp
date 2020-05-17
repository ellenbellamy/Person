#include "pch.h"
#include "../PersonList.h"
#include <algorithm>
#include <random>

namespace PersonListTesting {

	class PersonListTests : public ::testing::Test
	{
	protected:
		PersonList persons;

		void TearDown() {
			persons.clear();
		}
	};

	TEST_F(PersonListTests, IsEmptyOnCreation) {
		EXPECT_TRUE(PersonList().isEmpty());
	}

	TEST_F(PersonListTests, AddingElement) {
		persons.add(Person());

		EXPECT_FALSE(persons.isEmpty());
	}

	TEST_F(PersonListTests, Sorting) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));


		persons.sort();

		list<Person>::iterator current = persons.begin();

		EXPECT_TRUE(persons.isSorted());
	}

	TEST_F(PersonListTests, AddingList) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));

		PersonList anotherPerson;
		anotherPerson.add(Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("888", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"));

		persons.addAll(anotherPerson);

		EXPECT_EQ(persons.size(), 7);
	}

	TEST_F(PersonListTests, AddingSortedList) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("888", "Mary", "Smith", "2001-01-01", "+98765432100"));

		PersonList otherPersons;
		otherPersons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		otherPersons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		otherPersons.add(Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"));
		otherPersons.add(Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"));

		persons.merge(otherPersons);

		EXPECT_EQ(persons.size(), 7);
		EXPECT_TRUE(persons.isSorted());
	}

	TEST_F(PersonListTests, NextCelebrant) {

		vector<Person> indexedPersons = {
				Person("111", "Mary", "Smith", "2001-08-08", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-08-11", "+98765432100"),
				Person("333", "Mary", "Smith", "2001-09-09", "+98765432100"),
				Person("444", "Mary", "Smith", "2001-09-13", "+98765432100"),
				Person("555", "Mary", "Smith", "2001-09-19", "+98765432100"),
				Person("777", "Mary", "Smith", "2001-09-27", "+98765432100") 
		};

		vector<Person> shuffledPersons(indexedPersons.size());
		copy(indexedPersons.begin(), indexedPersons.end(), shuffledPersons.begin());
		shuffle(shuffledPersons.begin(), shuffledPersons.end(), default_random_engine());

		for (const Person& person : shuffledPersons) {
			persons.add(person);
		}

		EXPECT_EQ(persons.nextCelebrant(readDateTm("2001-01-01")), indexedPersons[0]);
		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-01-01")), indexedPersons[0]);

		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-08-09")), indexedPersons[1]);
		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-08-11")), indexedPersons[1]);

		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-08-12")), indexedPersons[2]);
		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-09-12")), indexedPersons[3]);
		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-09-20")), indexedPersons[5]);
		EXPECT_EQ(persons.nextCelebrant(readDateTm("2020-09-28")), indexedPersons[0]);

	}


	/*

		����� L - ��� ������� ������ �������� ������ S.

		�� ������ ������������ :
		- �����������
		- ����������

		- operator=

		- operator>> - ��������� ������ �� ������ �����
		- operator<< - ������� ������ � ����� ������

		+ add - �������� ������� � ����� ������
		+ sort - �������������

		+ addSort - �������� � ��������������� ������ � ����������� ������� ����������
		+ addList - ����� ������ 2 ������.

		- write - ������� �� ����� ��������, ��������������� ��������

		- remove - ������� ��������, ��������������� ��������

		- getBirthday - ���������� ��������� ���� �������� � ������� �� ���� �������� ����





		���������� � ������� main ������������� ��������� ������, ����������� ������� :
		- help - ������� �� ����� ������ ������
		- clear - �������� ������
		- load <filename> -�������� ������ �� �����
		- save <filename> -��������� ������ � �����
		- add(��������� � ����� �����, ������������ � ">") - �������� �������
		- sort - �������������
		- find <�������> -������� �� ����� ��������, ��������������� ��������
		- delete <�������> -������� ��������, ��������������� ��������
		- exit - ��������� ������ � �����.

		� ����������� ������� ��� ������� �������� :
		0 ������� : birthday - ������� �� ����� �����, � ������� ��������� ��

*/
}