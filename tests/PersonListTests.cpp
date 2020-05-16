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

		Класс L - это связный список объектов класса S.

		Он должен поддерживать :
		- конструктор
		- деструктор
		- operator=
		- operator>> - прочитать список из потока ввода
		- operator<< - вывести список в поток вывода

		+ add - добавить элемент в конец списка
		+ sort - отсортировать

		+ addSort - добавить в отсортированный список с сохранением порядка сортировки
		+ addList - слить вместе 2 списка.

		- write - вывести на экран элементы, удовлетворяющие условиям

		- remove - удалить элементы, удовлетворяющие условиям

		- getBirthday - определяет ближайший день рождения и сколько до него осталось дней





		Определить в функции main интерпретатор командной строки, реализующий команды :
		- help - вывести на экран список команд
		- clear - очистить список
		- load <filename> -добавить список из файла
		- save <filename> -сохранить список в файле
		- add(переходит в режим ввода, начинающийся с ">") - добавить элемент
		- sort - отсортировать
		- find <условия> -вывести на экран элементы, удовлетворяющие условиям
		- delete <условия> -удалить элементы, удовлетворяющие условиям
		- exit - завершить работу и выйти.

		И специальная команда для каждого варианта :
		0 вариант : birthday - вывести на экран людей, у которых ближайший ДР

*/
}