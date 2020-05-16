#include "pch.h"
#include "../PersonList.h"

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

		PersonList anotherPerson;
		anotherPerson.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"));
		anotherPerson.add(Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"));

		persons.merge(anotherPerson);

		EXPECT_EQ(persons.size(), 7);
		EXPECT_TRUE(persons.isSorted());
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