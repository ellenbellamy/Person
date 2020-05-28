#include "pch.h"

#include "../PersonCLI.h"

#include <fstream>
#include <stdio.h>

class PersonCLITests : public ::testing::Test
{
protected:
	PersonCLI cli;

	const char* const personsFileName = "persons.list";

	PersonList storedPersons{
		Person("111", "Mary", "Smith", "2001-12-11", "+98765432100"),
		Person("444", "Mary", "Smith", "2001-11-11", "+98765432100"),
		Person("333", "Mary", "Smith", "2001-11-01", "+98765432100"),
		Person("555", "Mary", "Smith", "2001-11-11", "+98765432100"),
		Person("222", "Mary", "Smith", "2001-12-21", "+98765432100"),
		Person("777", "Mary", "Smith", "2001-12-11", "+98765432100"),
		Person("222", "Mary", "Smith", "2001-12-11", "+98765432100")
	};


	void SetUp() {
		std::ofstream o(personsFileName);

		o << storedPersons << std::endl;
	}

	void TearDown() {
		//remove(personsFileName);
	}


	ostringstream executeCommandsFrom(istream& input) {
		ostringstream output;
		cli.start(input, output);
		return output;
	}
	ostringstream executeCommandsFrom(string inputString) {
		return executeCommandsFrom(istringstream(inputString));
	}
	ostringstream executeCommandsFrom(const char* inputString) {
		return executeCommandsFrom(istringstream(inputString));
	}
};


TEST_F(PersonCLITests, Help) {
	EXPECT_EQ(
		executeCommandsFrom("help\n").str(),
		"    help				--- вывести на экран список команд\n"
		"    clear				--- очистить список\n"
		"    load <filename>	--- добавить список из файла\n"
		"    save <filename>	--- сохранить список в файле\n"
		"    add				--- добавить элемент (переходит в режим ввода, начинающийся с \n"
		"    sort				--- отсортировать\n"
		"    find <условия>		--- вывести на экран элементы, удовлетворяющие условиям\n"
		"    delete <условия>	--- удалить элементы, удовлетворяющие условиям\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ДР\n"
	);
}


TEST_F(PersonCLITests, UnknownCommand) {
	EXPECT_EQ(
		executeCommandsFrom("abracadabra\n").str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}


TEST_F(PersonCLITests, Exit) {
	EXPECT_EQ(
		executeCommandsFrom("exit\n").str(),
		"Finished\n"
	);
}


TEST_F(PersonCLITests, CommandSquence) {
	EXPECT_EQ(
		executeCommandsFrom(
			"help\n"
			"abracadabra\n"
			"exit\n"
		).str(),
		"    help				--- вывести на экран список команд\n"
		"    clear				--- очистить список\n"
		"    load <filename>	--- добавить список из файла\n"
		"    save <filename>	--- сохранить список в файле\n"
		"    add				--- добавить элемент (переходит в режим ввода, начинающийся с \n"
		"    sort				--- отсортировать\n"
		"    find <условия>		--- вывести на экран элементы, удовлетворяющие условиям\n"
		"    delete <условия>	--- удалить элементы, удовлетворяющие условиям\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ДР\n"

		"ERROR: Unknown command: abracadabra\n"

		"Finished\n"
	);
}


TEST_F(PersonCLITests, CommandSquence1) {
	EXPECT_EQ(
		executeCommandsFrom(
			"help\n"
		).str(),
		"    help				--- вывести на экран список команд\n"
		"    clear				--- очистить список\n"
		"    load <filename>	--- добавить список из файла\n"
		"    save <filename>	--- сохранить список в файле\n"
		"    add				--- добавить элемент (переходит в режим ввода, начинающийся с \n"
		"    sort				--- отсортировать\n"
		"    find <условия>		--- вывести на экран элементы, удовлетворяющие условиям\n"
		"    delete <условия>	--- удалить элементы, удовлетворяющие условиям\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ДР\n"
	);

	EXPECT_EQ(
		executeCommandsFrom(
			"abracadabra\n"
		).str(),
		"ERROR: Unknown command: abracadabra\n"
	);

	EXPECT_EQ(
		executeCommandsFrom(
			"exit\n"
		).str(),
		"Finished\n"
	);


}


TEST_F(PersonCLITests, PersonsIsEmptyByDefault) {
	ASSERT_TRUE(cli.getPersons().isEmpty());
}


TEST_F(PersonCLITests, Clear) {
	cli.getPersons().add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
	ASSERT_FALSE(cli.getPersons().isEmpty());

	executeCommandsFrom(istringstream("clear\n"));
	ASSERT_FALSE(cli.getPersons().isEmpty());
}


TEST_F(PersonCLITests, Load) {
	executeCommandsFrom(string("load ") + personsFileName + "\n").str();
	EXPECT_EQ(cli.getPersons(), storedPersons);
}


TEST_F(PersonCLITests, Save) {
	cli.setPersons(storedPersons);

	string newFileName("saving_persons.test");
	executeCommandsFrom(string("save ") + newFileName + "\n");

	PersonList p;
	ifstream(newFileName) >> p;

	EXPECT_EQ(p, storedPersons);
}


TEST_F(PersonCLITests, Sort) {
	cli.setPersons(storedPersons);

	executeCommandsFrom("sort\n");

	storedPersons.sort();
	EXPECT_EQ(cli.getPersons(), storedPersons);
}


TEST_F(PersonCLITests, Add) {
	EXPECT_EQ(
		executeCommandsFrom(
			"add\n"
		).str(),
		">"
	);



	EXPECT_EQ(
		executeCommandsFrom(
			"111 Mary Smith 978296400 +98765432100\n"
		).str(),
		">"
	);

	EXPECT_EQ(
		cli.getPersons(),
		PersonList({
			Person("111", "Mary", "Smith", "2001-01-01", "+98765432100")
			})
	);



	EXPECT_EQ(
		executeCommandsFrom(
			"222 Mary Smith 978296400 +98765432100\n"
		).str(),
		">"
	);

	EXPECT_EQ(
		cli.getPersons(),
		PersonList({
			Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("222", "Mary", "Smith", "2001-01-01", "+98765432100")
			})
	);


	EXPECT_EQ(
		executeCommandsFrom(
			"333 Mary Smith 978296400 +98765432100\n"
		).str(),
		">"
	);

	EXPECT_EQ(
		cli.getPersons(),
		PersonList({
			Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("333", "Mary", "Smith", "2001-01-01", "+98765432100")
			})
	);



	EXPECT_EQ(
		executeCommandsFrom(
			"\n"
		).str(),
		"Added"
	);
}


TEST_F(PersonCLITests, Find) {
	cli.setPersons(storedPersons);

	EXPECT_EQ(
		executeCommandsFrom("find Anna Mary Smith 978296400 +98765432100\n").str(),
		"Found:\n"
	);

	EXPECT_EQ(
		executeCommandsFrom("find * Mary Smith * +98765432100\n").str(),
		"Found:\n"
		"111 Mary Smith 1008018000 +98765432100\n"
		"444 Mary Smith 1005426000 +98765432100\n"
		"333 Mary Smith 1004562000 +98765432100\n"
		"555 Mary Smith 1005426000 +98765432100\n"
		"222 Mary Smith 1008882000 +98765432100\n"
		"777 Mary Smith 1008018000 +98765432100\n"
		"222 Mary Smith 1008018000 +98765432100\n"
	);
}


TEST_F(PersonCLITests, Delete) {
	cli.setPersons(storedPersons);

	EXPECT_EQ(
		executeCommandsFrom("delete Mary Smith 978296400 +98765432100\n").str(),
		"Deleted\n"
	);
	EXPECT_EQ(cli.getPersons(), storedPersons);


	EXPECT_EQ(
		executeCommandsFrom("delete 222 Mary Smith * +98765432100\n").str(),
		"Deleted\n"
	);
	EXPECT_EQ(cli.getPersons(), PersonList({
		Person("111", "Mary", "Smith", "2001-12-11", "+98765432100"),
		Person("444", "Mary", "Smith", "2001-11-11", "+98765432100"),
		Person("333", "Mary", "Smith", "2001-11-01", "+98765432100"),
		Person("555", "Mary", "Smith", "2001-11-11", "+98765432100"),
		Person("777", "Mary", "Smith", "2001-12-11", "+98765432100")
		}));


	EXPECT_EQ(
		executeCommandsFrom("delete * Mary Smith * +98765432100\n").str(),
		"Deleted\n"
	);
	EXPECT_TRUE(cli.getPersons().isEmpty());
}



/*

		Определить в функции main интерпретатор командной строки, реализующий команды :
		+ help --- вывести на экран список команд
		+ clear --- очистить список
		+ load <filename> --- добавить список из файла
		+ save <filename> --- сохранить список в файле
		+ add(переходит в режим ввода, начинающийся с ">") --- добавить элемент
		+ sort --- отсортировать
		+ find <условия> --- вывести на экран элементы, удовлетворяющие условиям
		+ delete <условия> --- удалить элементы, удовлетворяющие условиям
		+ exit --- завершить работу и выйти.
		- birthday --- вывести на экран людей, у которых ближайший ДР

*/

