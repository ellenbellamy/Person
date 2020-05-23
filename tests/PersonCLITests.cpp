#include "pch.h"

#include "../PersonCLI.h"

#include <fstream>
#include <stdio.h>

class PersonCLITests : public ::testing::Test
{
protected:
	PersonCLI cli;

	const char* const personsFileName = "persons.list";

	void SetUp() {
		std::ofstream o(personsFileName);

		PersonList personList({
				Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100")
			});

		o << personList << std::endl;
	}

	void TearDown() {
		//remove(personsFileName);
	}
};


TEST_F(PersonCLITests, Help) {

	stringstream
		input,
		output;

	input << "help\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
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

	stringstream
		input,
		output;

	input << "abracadabra\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, Exit) {

	stringstream
		input,
		output;

	input << "exit\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"Finished\n"
	);
}


TEST_F(PersonCLITests, CommandSquence) {

	stringstream
		input,
		output;

	input
		<< "help\n"
		<< "abracadabra\n"
		<< "exit\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
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


TEST_F(PersonCLITests, Load) {

	stringstream
		input,
		output;

	input << "abracadabra\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, PersonsIsEmptyByDefault) {
	ASSERT_TRUE(cli.getPersons().isEmpty());
}

/*

		ќпределить в функции main интерпретатор командной строки, реализующий команды :
		- help --- вывести на экран список команд
		- clear --- очистить список
		- load <filename> --- добавить список из файла
		- save <filename> --- сохранить список в файле
		- add(переходит в режим ввода, начинающийс€ с ">") --- добавить элемент
		- sort --- отсортировать
		- find <услови€> --- вывести на экран элементы, удовлетвор€ющие услови€м
		- delete <услови€> --- удалить элементы, удовлетвор€ющие услови€м
		- exit --- завершить работу и выйти.
		- birthday --- вывести на экран людей, у которых ближайший ƒ–

*/

