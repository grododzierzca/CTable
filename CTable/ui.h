
#include <string>
#include <vector>
#include "CTable.h"

using namespace std;

//Messages
const string MESSAGE_CTABLE_NO_ARGUMENTS_CREATED = "Created no-argument CTable: ";
const string MESSAGE_CTABLE_WITH_ARGUMENTS_CREATED = "Created CTable: ";
const string MESSAGE_CTABLE_COPY_CREATED = "Created a copy of CTable: ";
const string MESSAGE_CTABLE_DELETED = "CTable has been deleted.\n";
const string MESSAGE_CTABLE_NAME_CHANGED = "Changed name to: ";
const string MESSAGE_CTABLE_VALUE_CHANGED = "Changed value to: ";
const string MESSAGE_CTABLE_SIZE_CHANGED = "Changed size to: ";

const string MESSAGE_UI_GET_INPUT = "Please enter your command...";
const string MESSAGE_UI_AVAILABLE_COMMANDS = "List of available commands: ";
const string MESSAGE_UI_HELP_HELP = "Help contains list of commands and available arguments.\nUsage: help <command>.\n";
const string MESSAGE_UI_HELP_EXIT = "Quits the program. Wow.\nUsage: exit <no arguments needed>.\n";
const string MESSAGE_UI_HELP_CREATE = "Create a new CTable object.\nUsage: create <name> <size>.\nAlternative version: create <name> <size> arg1 arg2 arg3 ... argSIZE";
const string MESSAGE_UI_HELP_DELETE = "Deletes CTable with given specific name.\nUsage: delete <specific name>.\n";
const string MESSAGE_UI_HELP_VIEW = "Displays CTable with given specific name.\nUsage: view <specific name>.\n";
const string MESSAGE_UI_HELP_EDIT = "Allows editing of CTable with given specific name.\nUsage: edit <specific name> <property to edit> <index> <new value>.\nExample: edit name new_name\n edit value 10 2\n";
const string MESSAGE_UI_HELP_DISPLAY = "Displays all existing CTables.\n";
const string MESSAGE_UI_HELP_CLONE = "Clones given Ctable.\nUsage: clone <specific name>\n";
const string MESSAGE_UI_HELP_TEST = "Test modification. Usage: test <specific name>\n";
const string MESSAGE_UI_NO_ELEMENTS_TO_DISPLAY = "There are no elements to display.";

//Errors
const string ERROR_EXPECTED_NATURAL_NUMBER = "Inserted value should be a natural number.\n";
const string ERROR_INDEX_OUT_OF_BOUNDS = "Inserted value exceeds CTable size.\n";
const string ERROR_INSUFFICIENT_MEMORY = "Insufficient memory to perform this action.\n";
const string ERROR_UI_WRONG_COMMAND = "Wrong command. Please use 'help' to get a list of available commands.";
const string ERROR_UI_WRONG_ARGUMENT = "Wrong argument. Please use 'help <command>' to get list of available arguments.";
const string ERROR_UI_ELEMENT_DOES_NOT_EXIST = "Element does not exist.";

//Warnings
const string WARNING_UI_NAME_REPEATING = "Warning! The name does already exist!";
const string WARNING_CTABLE_DATA_LOSS = "Warning! This operation may erase some of your data!";

//Various text
const string COMMAND_HELP = "help";
const string COMMAND_EXIT = "exit";
const string COMMAND_EDIT = "edit";
const string COMMAND_CREATE = "create";
const string COMMAND_DELETE = "delete";
const string COMMAND_VIEW = "view";
const string COMMAND_DISPLAY = "display";
const string COMMAND_CLONE = "clone";
const string COMMAND_DUMMY = "dummy";
const string COMMAND_TEST = "test";
const string TEXT_IS_A_COPY = "_copy";

//Commands
const int NUMBER_OF_MAIN_COMMANDS = 9;
const string COMMANDS[NUMBER_OF_MAIN_COMMANDS] = {COMMAND_TEST, COMMAND_EXIT, COMMAND_CREATE, COMMAND_DELETE, COMMAND_HELP, COMMAND_EDIT, COMMAND_DISPLAY, COMMAND_VIEW, COMMAND_CLONE};
//create <name> <size>
//delete <spec_name>
//view <spec_name>
//help <command_name>
//edit <target property> <new value>
//display
//clone <name>
//exit
const int NUMBER_OF_EDIT_COMMANDS = 3;
const string EDIT_COMMANDS[NUMBER_OF_EDIT_COMMANDS] = { "name", "size", "value" };



//Functions in ui.cpp
vector<string> runUI(istringstream &stream);
void displayPrompt();
void getInput(istringstream &stream);
bool analyzeInput(string input);
void nextString(istringstream &stream, string &target);
bool nextInt(istringstream &stream, int &target);
void help();
void help(string argument);
CTable* create(string name, int size);
CTable* clone(CTable* other_table);
bool isInt(const string &input);
void vTest(CTable other_table);