#include <iostream>
#include "CTable.h"
#include "ui.h"
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;



int main() {
	vector<CTable*> CTables;
	istringstream stream;
	vector<string> input;
	int number_of_ctables_ever = 0;
	
	int number_of_args;

	cout << "___________________" << endl;
	cout << "| _______________ |" << endl;
	cout << "| |XXXXXXXXXXXXX| |" << endl;
	cout << "| | C.T.A.B.L.E.| |" << endl;
	cout << "| |XXXXXXXXXXXXX| |" << endl;
	cout << "| |XXX v.1.3 XXX| |" << endl;
	cout << "| |XXXXXXXXXXXXX| |" << endl;
	cout << "|_________________|" << endl;
	cout << "    _[_______]_" << endl;
	cout << "___[___________]___" << endl;
	cout << "|        [_____][] |" << endl;
	cout << "|        [_____][] |" << endl;
	cout << "L__________________J" << endl;
	do {

		input.clear();
		input = runUI(stream);
		string command = input.front();
		number_of_args = input.size()-1;

		switch (number_of_args) {
		case 0:
			if (command != COMMAND_HELP && command != COMMAND_DISPLAY && command != COMMAND_DUMMY && command != COMMAND_EXIT) cout << ERROR_UI_WRONG_ARGUMENT << endl;
			if (command == COMMAND_DISPLAY) {
				if (CTables.empty()) cout << MESSAGE_UI_NO_ELEMENTS_TO_DISPLAY << endl;
				else {
					for (int i = 0; i < CTables.size(); i++) {
						cout << CTables.at(i)->toString();
					}
				}
			}
			else if (command == COMMAND_HELP) help();
			else if (command == COMMAND_EXIT) {
				for (int i = 0; i < CTables.size(); i++) {
					delete CTables.at(i);
				}
				return 0;
			}
			break;
		case 1:
			if (command != COMMAND_HELP && command != COMMAND_DELETE && command != COMMAND_VIEW && command != COMMAND_DISPLAY && command != COMMAND_CLONE && command != COMMAND_TEST) cout << ERROR_UI_WRONG_ARGUMENT << endl;
			else if (command == COMMAND_HELP) help(input.at(1));
			else if (command == COMMAND_VIEW) {
				bool flag = false;
				for (int i = 0; i < CTables.size(); i++) {
					if (CTables.at(i)->getName() == input.at(1)) {
						cout << CTables.at(i)->toString() << endl;
						flag = true;
					}	
				}
				if (!flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl;
			}
			else if (command == COMMAND_CLONE) {
				bool flag = false;
				for (int i = 0; i < CTables.size(); i++) {
					if (CTables.at(i)->getName() == input.at(1)) {
						CTables.push_back(clone(CTables.at(i)));
						flag = true;
					}
				}
				if (!flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl;
			}
			else if (command == COMMAND_TEST) {
				bool flag = false;
				for (int i = 0; i < CTables.size(); i++) {
					if (CTables.at(i)->getName() == input.at(1)) {
						vTest(*CTables.at(i));
						flag = true;
					}
				}
				if (!flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl;
			}
			else {
				bool flag = false;
				for (int i = 0; i < CTables.size(); i++) {
					if (CTables.at(i)->getName() == input.at(1)) {
						delete CTables.at(i);
						CTables.erase(CTables.begin()+i);
						flag = true;
					}
				}
				if (!flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl;
			}/*delete*/
			break;
		case 2:
			if (command == COMMAND_TEST || command == COMMAND_HELP || command == COMMAND_DELETE || command == COMMAND_VIEW || command == COMMAND_DISPLAY) cout << ERROR_UI_WRONG_ARGUMENT << endl;
			else if (command == COMMAND_CREATE) {
				if (!isInt(input.at(2)) || stoi(input.at(2)) < 0) cout << ERROR_UI_WRONG_ARGUMENT << endl;
				else {
					CTables.push_back(create(input.at(1), stoi(input.at(2))));
					CTables.back()->setName(CTables.back()->getName() + "_" + to_string(number_of_ctables_ever)); //The specific name of a CTable is name_number
					number_of_ctables_ever++;
				}
			}
			
			break;
		case 3:
			if (command != COMMAND_EDIT && command != COMMAND_CREATE) {
				cout << ERROR_UI_WRONG_ARGUMENT << endl;
			}
			if (command == COMMAND_CREATE) {
				if (!isInt(input.at(2))) cout << ERROR_EXPECTED_NATURAL_NUMBER << endl;
				else if (stoi(input.at(2)) < input.size() - 3) cout << ERROR_UI_WRONG_ARGUMENT << endl;
				else {
					string name = input.at(1) + "_" + to_string(number_of_ctables_ever);
					int size = stoi(input.at(2));
					bool flag = true;
					CTable* new_table = new CTable(name, size);
					for (int i = 3; i < input.size() || !flag; i++) {
						if (!isInt(input.at(i))) flag = false;
						else new_table->setValue(i - 3, stoi(input.at(i)));
					}
					if (!flag) cout << ERROR_UI_WRONG_ARGUMENT << endl;
					else {
						CTables.push_back(new_table);
						number_of_ctables_ever++;
					}
				}
			}
			else {
				CTable* table_to_edit = NULL;
				bool* flag = new bool(false);
				string CTable_to_edit = input.at(1);
				for (int i = 0; i < CTables.size(); i++) {
					if (CTable_to_edit == CTables.at(i)->getName()) {
						*flag = true;
						table_to_edit = CTables.at(i);
					}
				}
				
				if (!*flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl; //no CTable with given name
				else {
					string property_to_edit = input.at(2);
					*flag = false;
					for (int i = 0; i < NUMBER_OF_EDIT_COMMANDS; i++) {
						if (property_to_edit == EDIT_COMMANDS[i]) {
							*flag = true;
						}
					}
					if (!*flag) cout << ERROR_UI_WRONG_ARGUMENT << endl;  //wrong property to edit
					else {
						if (property_to_edit == "name") {
							table_to_edit->setName(input.at(3));
							for (int i = 0; i < CTables.size(); i++) {
								if (table_to_edit->getName() == CTables.at(i)->getName() && table_to_edit != CTables.at(i)) {
									cout << WARNING_UI_NAME_REPEATING << endl;
									table_to_edit->setName(input.at(3) + "_" + to_string(number_of_ctables_ever));
									number_of_ctables_ever++;
								}
							}
						}
						else if (property_to_edit == "size") {
							if(isInt(input.at(3))) table_to_edit->setSize(stoi(input.at(3)));
							else cout << ERROR_EXPECTED_NATURAL_NUMBER << endl;
						}
					}
				}

			}/*edit*/
			break;
		case 4:
			if (command != COMMAND_EDIT && command != COMMAND_CREATE) cout << ERROR_UI_WRONG_ARGUMENT << endl;
			if (command == COMMAND_CREATE) {
				if (!isInt(input.at(2))) cout << ERROR_EXPECTED_NATURAL_NUMBER << endl;
				else if (stoi(input.at(2)) < input.size() - 3) cout << ERROR_UI_WRONG_ARGUMENT << endl;
				else {
					string name = input.at(1) + "_" + to_string(number_of_ctables_ever);
					int size = stoi(input.at(2));
					bool flag = true;
					CTable* new_table = new CTable(name, size);
					for (int i = 3; i < input.size() || !flag; i++) {
						if (!isInt(input.at(i))) flag = false;
						else new_table->setValue(i - 3, stoi(input.at(i)));
					}
					if (!flag) cout << ERROR_UI_WRONG_ARGUMENT << endl;
					else {
						CTables.push_back(new_table);
						number_of_ctables_ever++;
					}
				}
			}
			else {
				CTable* table_to_edit = NULL;
				bool flag = false;
				string CTable_to_edit = input.at(1);
				for (int i = 0; i < CTables.size(); i++) {
					if (CTable_to_edit == CTables.at(i)->getName()) {
						flag = true;
						table_to_edit = CTables.at(i);
					}
				}
				if (!flag) cout << ERROR_UI_ELEMENT_DOES_NOT_EXIST << endl; //no CTable with given name
				else if (input.at(2) != "value") cout << ERROR_UI_WRONG_ARGUMENT << endl;
				else {
					if (!isInt(input.at(3)) || !isInt(input.at(4))) cout << ERROR_EXPECTED_NATURAL_NUMBER << endl;
					else table_to_edit->setValue(stoi(input.at(3)), stoi(input.at(4)));
				}
			}/*edit*/
			break;
		default:
			if(command != COMMAND_CREATE) cout << ERROR_UI_WRONG_COMMAND << endl;
			else {
				if (!isInt(input.at(2))) cout << ERROR_EXPECTED_NATURAL_NUMBER << endl;
				else if (stoi(input.at(2)) < input.size() - 3) cout << ERROR_UI_WRONG_ARGUMENT << endl;
				else {
					string name = input.at(1) + "_" + to_string(number_of_ctables_ever);
					int size = stoi(input.at(2));
					bool flag = true;
					CTable* new_table = new CTable(name, size);
					for (int i = 3; i < input.size() || !flag; i++) {
						if (!isInt(input.at(i))) flag = false;
						else new_table->setValue(i - 3, stoi(input.at(i)));
					}
					if (!flag) cout << ERROR_UI_WRONG_ARGUMENT << endl;
					else {
						CTables.push_back(new_table);
						number_of_ctables_ever++;
					}
				}
			}
			break;
		}
	} while (true);



	return 0;
}
