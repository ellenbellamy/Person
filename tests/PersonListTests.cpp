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
		persons.addAll({
				Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100")
			});

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

		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2001-01-01"))) == (tuple<Person, time_t, int>(indexedPersons[0], 219, indexedPersons[0].getBirthday())));
		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-08-09"))) == (tuple<Person, time_t, int>(indexedPersons[1], 2, indexedPersons[1].getBirthday())));
		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-08-11"))) == (tuple<Person, time_t, int>(indexedPersons[1], 0, indexedPersons[1].getBirthday())));

		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-08-12"))) == (tuple<Person, time_t, int>(indexedPersons[2], 28, indexedPersons[2].getBirthday())));
		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-09-12"))) == (tuple<Person, time_t, int>(indexedPersons[3], 1, indexedPersons[3].getBirthday())));
		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-09-20"))) == (tuple<Person, time_t, int>(indexedPersons[5], 7, indexedPersons[5].getBirthday())));
		EXPECT_TRUE((persons.nextCelebrant(readDateTm("2020-09-28"))) == (tuple<Person, time_t, int>(indexedPersons[0], 314, indexedPersons[0].getBirthday())));
	}


	TEST_F(PersonListTests, Assigning) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));

		PersonList p;
		p = persons;

		EXPECT_EQ(p, persons);
	}

	TEST_F(PersonListTests, Writing) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));


		stringstream ss;

		ss << persons;

		EXPECT_EQ(
			"111 Mary Smith 978296400 +98765432100\n"
			"222 Mary Smith 978296400 +98765432100\n"
			"333 Mary Smith 978296400 +98765432100\n",
			ss.str());
	}

	TEST_F(PersonListTests, Reading) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));

		stringstream ss;
		ss << persons;


		PersonList p;
		ss >> p;


		EXPECT_EQ(persons, p);

	}

	TEST_F(PersonListTests, Selecting) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("444", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));

		EXPECT_EQ(
			persons.select(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100")),
			list<Person>({
				Person("111", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));

		EXPECT_EQ(
			persons.select(Person({}, "Mary", {}, {}, {})),
			list<Person>({
				Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("555", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));
	}

	TEST_F(PersonListTests, PrintingSelected) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("444", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"));

		stringstream ss;

		persons.printSelected(ss, Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(
			ss.str(),
			"111 Mary Smith 978296400 +98765432100\n");

		persons.printSelected(ss, Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));


		ss.str(string());
		persons.printSelected(ss, Person({}, "Mary", {}, {}, {}));
		EXPECT_EQ(
			ss.str(),
			"111 Mary Smith 978296400 +98765432100\n"
			"333 Mary Smith 978296400 +98765432100\n"
			"555 Mary Smith 978296400 +98765432100\n"
		);
	}

	TEST_F(PersonListTests, Removing) {
		persons.add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("222", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("444", "Phil", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("555", "John", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("777", "Jack", "Smith", "2001-01-01", "+98765432100"));
		persons.add(Person("888", "Mary", "Smith", "2001-01-01", "+98765432100"));

		persons.remove(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(
			persons,
			list<Person>({
					Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
					Person("222", "John", "Smith", "2001-01-01", "+98765432100"),
					Person("444", "Phil", "Smith", "2001-01-01", "+98765432100"),
					Person("555", "John", "Smith", "2001-01-01", "+98765432100"),
					Person("777", "Jack", "Smith", "2001-01-01", "+98765432100"),
					Person("888", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));

		persons.remove(Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(
			persons,
			list<Person>({
					Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
					Person("222", "John", "Smith", "2001-01-01", "+98765432100"),
					Person("444", "Phil", "Smith", "2001-01-01", "+98765432100"),
					Person("555", "John", "Smith", "2001-01-01", "+98765432100"),
					Person("777", "Jack", "Smith", "2001-01-01", "+98765432100"),
					Person("888", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));

		persons.remove(Person({}, "John", "Smith", {}, {}));
		EXPECT_EQ(
			persons,
			list<Person>({
					Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
					Person("444", "Phil", "Smith", "2001-01-01", "+98765432100"),
					Person("777", "Jack", "Smith", "2001-01-01", "+98765432100"),
					Person("888", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));

		persons.remove(Person({}, "Phil", "Smith", {}, {}));
		EXPECT_EQ(
			persons,
			list<Person>({
					Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
					Person("777", "Jack", "Smith", "2001-01-01", "+98765432100"),
					Person("888", "Mary", "Smith", "2001-01-01", "+98765432100")
				}));

		persons.remove(Person({}, {}, {}, {}, {}));
		EXPECT_TRUE(persons.isEmpty());
	}

}



/*
	 ласс L - это св€зный список объектов класса S.

	ќн должен поддерживать :
	? конструктор
	? деструктор

	? operator=

	+ operator>> - прочитать список из потока ввода
	+ operator<< - вывести список в поток вывода

	+ add - добавить элемент в конец списка
	+ sort - отсортировать

	+ addSort - добавить в отсортированный список с сохранением пор€дка сортировки
	+ addList - слить вместе 2 списка.

	+ write - вывести на экран элементы, удовлетвор€ющие услови€м

	+ remove - удалить элементы, удовлетвор€ющие услови€м

	+ getBirthday - определ€ет ближайший день рождени€ и сколько до него осталось дней

*/
