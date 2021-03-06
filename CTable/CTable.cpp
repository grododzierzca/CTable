

#include <iostream>
#include <string>
#include "CTable.h"
#include "const_values.h"
#include "ui.h"

using namespace std;

CTable::CTable() {
	name = DEFAULT_NAME;
	setSize(DEFAULT_SIZE);
	cout << MESSAGE_CTABLE_NO_ARGUMENTS_CREATED + name + "\n";
}

CTable::CTable(string name, int size) {
	this->name = name;
	if(setSize(size)) cout << MESSAGE_CTABLE_WITH_ARGUMENTS_CREATED + name + "\n";
}

CTable::CTable(const CTable &other_ctable) {
	this->name = other_ctable.name + TEXT_IS_A_COPY;
	setTableTo(other_ctable);
	cout << MESSAGE_CTABLE_COPY_CREATED + name + "\n";
}

CTable::~CTable() {
	if (array != NULL) delete[] array;
	cout << MESSAGE_CTABLE_DELETED;
}

//Methods

bool CTable::checkIfMemoryAvailable(int size) {
	int* temp = new (nothrow) int[size];
	if (temp == NULL) {
		cout << ERROR_INSUFFICIENT_MEMORY;
		return false;
	}
	else {
		delete[] temp;
		return true;
	}
}

bool CTable::setSize(int new_size) {
	if (new_size < 0) {
		cout << ERROR_EXPECTED_NATURAL_NUMBER;
		return false;
	}
	if (checkIfMemoryAvailable(new_size)) {
		int*new_table = new (nothrow) int[new_size];
		if (array == NULL) { //first time initialise
			array = new_table;
			array_size = new_size;
			for (int i = 0; i < array_size; i++) {
				array[i] = DEFAULT_VALUE;
			}
			return true;
		}else {
			if (new_size >= array_size) {
				for (int i = 0; i < array_size; i++) {
					new_table[i] = array[i];
				}
				for (int i = array_size; i < new_size; i++) {
					new_table[i] = DEFAULT_VALUE;
				}
			}
			else {
				cout << WARNING_CTABLE_DATA_LOSS << endl;
				for (int i = 0; i < new_size; i++) {
					new_table[i] = array[i];
				}
			}
			delete[] array;
			array = new_table;
			array_size = new_size;
		}
		cout << MESSAGE_CTABLE_SIZE_CHANGED << new_size <<endl;
		return true;
	}else {
		cout << ERROR_INSUFFICIENT_MEMORY << endl;
		return false;
	}
}

void CTable::setName(string new_name) {
	this->name = new_name;
	cout << MESSAGE_CTABLE_NAME_CHANGED + new_name << endl;
}

bool CTable::setValue(int position, int new_value) {
	if (position > size()) {
		cout << ERROR_INDEX_OUT_OF_BOUNDS;
		return false;
	}
	else if (position < 0) {
		cout << ERROR_EXPECTED_NATURAL_NUMBER;
		return false;
	}
	array[position] = new_value;
	cout << MESSAGE_CTABLE_VALUE_CHANGED + to_string(new_value) << endl;
	return true;
}

bool CTable::setTableTo(const CTable &other_ctable) {
	int other_size = other_ctable.array_size;
	int* other_array = other_ctable.array;
	if (!checkIfMemoryAvailable(other_size)) return false;
	int* temp = new (nothrow) int[other_size];
	for (int i = 0; i < other_size; i++) {
		temp[i] = other_array[i];
	}
	array = temp;
	array_size = other_size;
	return true;
}

string CTable::getName() {
	return name;
}
int CTable::size() {
	return array_size;
}
int CTable::length() {
	return array_size + 1;
}
int CTable::getValue(int position) {
	if (position < 0) {
		cout << ERROR_EXPECTED_NATURAL_NUMBER;
		return NULL;
	}
	else if (position > size()) {
		cout << ERROR_INDEX_OUT_OF_BOUNDS;
		return NULL;
	}
	else {
		return array[position];
	}
}
void CTable::deleteArray() {
	if(array != NULL) delete[] array;
}
CTable* CTable::clone() {
	if (!checkIfMemoryAvailable(size())) {
		return NULL;
	}
	return new CTable(*this);
}
string CTable::toString() {
	string result =  "Table: " + name + ", size: " + to_string(size()) + "\nElements: [";
	for (int i = 0; i < array_size; i++) {
		result += to_string(array[i]) + ", ";
	}
	if (array_size > 0) {
		result.pop_back();
		result.pop_back();
	}
	
	result += "]\n";
	return result;
}