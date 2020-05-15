#include "pch.h"
#include "../Person.h"
#include <ctime>

namespace PersonTesting {
	Person person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100");

	TEST(Person, HasFirstName) {
		EXPECT_EQ(person.getFirstName(), "Anna");
	}

	TEST(Person, HasLastName) {
		EXPECT_EQ(person.getLastName(), "Smith");
	}

	TEST(Person, HasMiddleName) {
		EXPECT_EQ(person.getMiddleName(), "Mary");
	}

	TEST(Person, WritesItself) {
		std::stringstream ss;

		ss << person;

		EXPECT_EQ("Anna Mary Smith 978296400 +98765432100", ss.str());
	}

	TEST(Person, Equality) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST(Person, EqualityIgnoresPhone) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 01"));
	}

	TEST(Person, Inequality) {
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith_", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary_", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna_", "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100"));
	}

	TEST(Person, LessByBirthday) {
		EXPECT_LT(
			Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST(Person, LessIgnoresPhone) {
		EXPECT_FALSE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")
			<
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101"));
	}


	//TEST(Person, ThrowsExceptionOnWrongBirthdayFormat) {
	//	Person p = Person("Anna", "Mary", "Smith", "2001-02-31", "+98765432100");
	//	EXPECT_THROW( p /*= Person("Anna", "Mary", "Smith", "2001-02-29", "+98765432100")*/, WrongDateFormat);
	//}

	TEST(Person, ReadsItself) {

		std::stringstream ss;

		ss << person;

		Person p;
		ss >> p;

		EXPECT_EQ(person, p);
	}

	TEST(Person, Assignment) {
		Person p;
		p = person;
		EXPECT_EQ(person, p);
	}

	TEST(Person, Copy) {
		Person p(person);
		EXPECT_EQ(person, p);
	}

	TEST(Person, DaysUntilBirthday) {
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2001-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-12-31")), 1);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-12-30")), 2);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-01-02")), 365);

		EXPECT_EQ(person.daysUntilBirthday(convertTime(readDate("2000-12-31") + 1)), 1);
		EXPECT_EQ(person.daysUntilBirthday(convertTime(readDate("2000-12-31") + 24 * 60 * 60)), 0);

		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2002-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2001-12-31")), 1);

		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-12-31")), 1);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-12-30")), 2);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-01-02")), 365);
	}

	TEST(Person, Check) {
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));

		//EXPECT_FALSE(person.check(Person("Anna_", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_FALSE(person.check(Person("Anna", "Mary_", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith_", "2001-01-01", "+98765432100")));
		//EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100")));
		//EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101")));

		EXPECT_TRUE(person.check(Person({}, "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		//EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
	}

/*

		Класс L - это связный список объектов класса S.

		Он должен поддерживать :
		-конструктор
		- деструктор
		- operator=
		- operator>> - прочитать список из потока ввода
		- operator<< - вывести список в поток вывода
		- add - добавить элемент в конец списка
		- sort - отсортировать
		- addSort - добавить в отсортированный список с сохранением порядка сортировки
		- addList - слить вместе 2 списка.
		- write - вывести на экран элементы, удовлетворяющие условиям
		- remove - удалить элементы, удовлетворяющие условиям

		И специальный метод для каждого варианта :
		0 вариант : getBirthday - определяет ближайший день рождения и сколько до него осталось дней

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