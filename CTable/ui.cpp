#include <iostream>
#include "ui.h"
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> runUI(istringstream &stream) {
	string input;
	displayPrompt();
	getInput(stream);
	nextString(stream, input);
	vector <string> command; //command: command argument1 (optional) argument2

	for (string s; stream >> s;) {
		command.push_back(s);
	}
	if (command.empty()) {
		command.push_back(COMMAND_DUMMY+" ");
		return command;
	}
	if (!analyzeInput(command.front())) {
		cout << ERROR_UI_WRONG_COMMAND<<endl;
		runUI(stream);
	}
	return command;
}

void getInput(istringstream &stream) {
	string input = "";
	stream.clear();
	getline(cin, input);
	input = COMMAND_DUMMY + " " + input;
	stream.str(input);
}

void displayPrompt() {
	cout << MESSAGE_UI_GET_INPUT << endl;
}

bool analyzeInput(string input) {
	for (int i = 0; i < NUMBER_OF_MAIN_COMMANDS; i++) {
		if (input == COMMANDS[i]) return true;
	}
	return false;
}

void nextString(istringstream &stream, string &target) {
	stream >> target;
}

bool nextInt(istringstream &stream, int &target) {
	if (stream >> target) return true;
	return false;
}

void help() {
	cout << MESSAGE_UI_AVAILABLE_COMMANDS;
	copy(COMMANDS, COMMANDS + NUMBER_OF_MAIN_COMMANDS, ostream_iterator<string>(cout, ", "));
	cout << endl;
}

void help(string argument) {
	if (argument == COMMAND_HELP) cout << MESSAGE_UI_HELP_HELP;
	else if (argument == COMMAND_EXIT) cout << MESSAGE_UI_HELP_EXIT;
	else if (argument == COMMAND_CREATE) cout << MESSAGE_UI_HELP_CREATE;
	else if (argument == COMMAND_DELETE) cout << MESSAGE_UI_HELP_DELETE;
	else if (argument == COMMAND_VIEW) cout << MESSAGE_UI_HELP_VIEW;
	else if (argument == COMMAND_DISPLAY) cout << MESSAGE_UI_HELP_DISPLAY;
	else if (argument == COMMAND_CLONE) cout << MESSAGE_UI_HELP_CLONE;
	else if (argument == COMMAND_EDIT) cout << MESSAGE_UI_HELP_EDIT;
	else if (argument == COMMAND_TEST) cout << MESSAGE_UI_HELP_TEST;
	else cout << ERROR_UI_WRONG_ARGUMENT;
}


CTable* create(string name, int size){
	return new CTable(name, size);
}


CTable* clone(CTable* other_table) {
	return new CTable(*other_table);
}

bool isInt(const string &input){
	string::const_iterator it = input.begin();
	while (it != input.end() && isdigit(*it)) ++it;
	return !input.empty() && it == input.end();
}

void vTest(CTable other_table) {
	other_table.setSize(1);
}
