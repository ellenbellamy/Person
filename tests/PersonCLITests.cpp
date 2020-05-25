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
		Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"),
		Person("222", "Mary", "Smith", "2001-01-01", "+98765432100")
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
		"    add				--- добавить элемент (переходит в режим ввода, начинающийс€ с \n"
		"    sort				--- отсортировать\n"
		"    find <услови€>		--- вывести на экран элементы, удовлетвор€ющие услови€м\n"
		"    delete <услови€>	--- удалить элементы, удовлетвор€ющие услови€м\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ƒ–\n"
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
		"    add				--- добавить элемент (переходит в режим ввода, начинающийс€ с \n"
		"    sort				--- отсортировать\n"
		"    find <услови€>		--- вывести на экран элементы, удовлетвор€ющие услови€м\n"
		"    delete <услови€>	--- удалить элементы, удовлетвор€ющие услови€м\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ƒ–\n"

		"ERROR: Unknown command: abracadabra\n"

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
	string newFileName( "saving_persons.test");

	cli.setPersons(storedPersons);

	executeCommandsFrom(string("save ") + newFileName + "\n").str();

	PersonList p;
	ifstream(newFileName) >> p;

	EXPECT_EQ(p, storedPersons);
}



/*

		ќпределить в функции main интерпретатор командной строки, реализующий команды :
		+ help --- вывести на экран список команд
		+ clear --- очистить список
		+ load <filename> --- добавить список из файла
		- save <filename> --- сохранить список в файле
		- add(переходит в режим ввода, начинающийс€ с ">") --- добавить элемент
		- sort --- отсортировать
		- find <услови€> --- вывести на экран элементы, удовлетвор€ющие услови€м
		- delete <услови€> --- удалить элементы, удовлетвор€ющие услови€м
		+ exit --- завершить работу и выйти.
		- birthday --- вывести на экран людей, у которых ближайший ƒ–

*/

