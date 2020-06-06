#include "pch.h"

#include "../PersonCLI.h"

#include <fstream>
#include <stdio.h>


namespace PersonListTesting {

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
			"    help				--- ������� �� ����� ������ ������\n"
			"    clear				--- �������� ������\n"
			"    load <filename>	--- �������� ������ �� �����\n"
			"    save <filename>	--- ��������� ������ � �����\n"
			"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
			"    sort				--- �������������\n"
			"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
			"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
			"    exit				--- ��������� ������ � �����\n"
			"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n"
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
			"    help				--- ������� �� ����� ������ ������\n"
			"    clear				--- �������� ������\n"
			"    load <filename>	--- �������� ������ �� �����\n"
			"    save <filename>	--- ��������� ������ � �����\n"
			"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
			"    sort				--- �������������\n"
			"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
			"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
			"    exit				--- ��������� ������ � �����\n"
			"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n"

			"ERROR: Unknown command: abracadabra\n"

			"Finished\n"
		);
	}


	TEST_F(PersonCLITests, CommandSquence1) {
		EXPECT_EQ(
			executeCommandsFrom(
				"help\n"
			).str(),
			"    help				--- ������� �� ����� ������ ������\n"
			"    clear				--- �������� ������\n"
			"    load <filename>	--- �������� ������ �� �����\n"
			"    save <filename>	--- ��������� ������ � �����\n"
			"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
			"    sort				--- �������������\n"
			"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
			"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
			"    exit				--- ��������� ������ � �����\n"
			"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n"
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
			executeCommandsFrom("delete Mary Smith 1591452500 +98765432100\n").str(),
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



	TEST_F(PersonCLITests, Birthday) {
		time_t today = time(NULL);
		vector<Person> indexedPersons = {
				Person("111", "Mary", "Smith", today + (15 * 60 * 60 * 24), "+98765432100"),
				Person("222", "Mary", "Smith", today + (17 * 60 * 60 * 24), "+98765432100"),
				Person("333", "Mary", "Smith", today + (3 * 60 * 60 * 24), "+98765432100"),
				Person("444", "Mary", "Smith", today + (15 * 60 * 60 * 24), "+98765432100"),
				Person("555", "Mary", "Smith", today - (1 * 60 * 60 * 24), "+98765432100"),
				Person("777", "Mary", "Smith", today - (364 * 60 * 60 * 24), "+98765432100")
		};
		cli.setPersons(list<Person>(begin(indexedPersons), end(indexedPersons)));

		EXPECT_EQ(
			executeCommandsFrom("birthday\n").str(),
			(ostringstream() << "Next celebrant: " << indexedPersons[5] <<"\n").str()
		);


		//tuple<Person, time_t, int> celebrantInfo = persons.nextCelebrant();
		//EXPECT_EQ(celebrantInfo, (tuple<Person, time_t, int>(indexedPersons[2], 1, indexedPersons[2].getBirthday())));



		/*
			Person("111", "Mary", "Smith", "2001-12-11", "+98765432100"),
			Person("222", "Mary", "Smith", "2001-11-11", "+98765432100"),
			Person("333", "Mary", "Smith", "2001-11-01", "+98765432100"),
			Person("444", "Mary", "Smith", "2001-11-11", "+98765432100"),
			Person("555", "Mary", "Smith", "2001-12-21", "+98765432100"),
			Person("777", "Mary", "Smith", "2001-12-11", "+98765432100"),
			Person("888", "Mary", "Smith", "2001-12-11", "+98765432100")
		*/

	}
}

/*

		���������� � ������� main ������������� ��������� ������, ����������� ������� :
		+ help --- ������� �� ����� ������ ������
		+ clear --- �������� ������
		+ load <filename> --- �������� ������ �� �����
		+ save <filename> --- ��������� ������ � �����
		+ add(��������� � ����� �����, ������������ � ">") --- �������� �������
		+ sort --- �������������
		+ find <�������> --- ������� �� ����� ��������, ��������������� ��������
		+ delete <�������> --- ������� ��������, ��������������� ��������
		+ exit --- ��������� ������ � �����.
		+ birthday --- ������� �� ����� �����, � ������� ��������� ��

*/

