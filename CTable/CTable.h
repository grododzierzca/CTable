#pragma once
#include <string>
#include <iostream>

using namespace std;

class CTable {
public:
	//Constructors
	CTable();
	CTable(string table_name, int table_size);
	CTable(const CTable &other_ctable);
	//Deconstructor
	~CTable();
	//Methods
	//All setters REQUIRE the arguments to be valid type
	bool setSize(int new_size);
	void setName(string new_name);
	bool setValue(int position, int new_value);
	bool setTableTo(const CTable &other_ctable);
	
	string getName();
	int size(); //number of elements
	int length(); //length of an array (size + 1)
	int getValue(int position);
	CTable* clone();
	string toString();
	void deleteArray();
private:
	//Class members
	string name;
	int* array;
	int array_size;
	
	//Methods
	bool checkIfMemoryAvailable(int size);

};