#include "PersonCLI.h"

#include <sstream>

void PersonCLI::start(istream& input, ostream& output) {
	string line;
	while (getline(input, line)) {
		output << process(line);
	}
}

PersonList PersonCLI::getPersons() {
	return persons;
}


string PersonCLI::process(const string& commandString) {
	if (commandString == "help") {
		return
			"    help				--- ������� �� ����� ������ ������\n"
			"    clear				--- �������� ������\n"
			"    load <filename>	--- �������� ������ �� �����\n"
			"    save <filename>	--- ��������� ������ � �����\n"
			"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
			"    sort				--- �������������\n"
			"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
			"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
			"    exit				--- ��������� ������ � �����\n"
			"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n";
	}
	if (commandString == "exit") {
		return "Finished\n";
	}

	return "ERROR: Unknown command: " + commandString + "\n";
}
