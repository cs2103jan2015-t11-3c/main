#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Constants
const string DELIMITERS = " \n\t\v";
const string DEFAULT_SAVE_FILENAME = "SaveFile.txt";
const int FILE_NAME_ARG_NUMBER = 1;
const string MESSAGE_ITEM_ADDED_SUCCESSFULLY = "added to";
const string MESSAGE_ITEM_DELETED_SUCCESSFULLY = "deleted from";
const string MESSAGE_ITEMS_CLEARED_SUCCESSFULLY = "all content deleted from";
const string ERROR_LIST_IS_EMPTY = "is empty";
const string ERROR_INVALID_INDEX = "invalid index";
const string ERROR_MISSING_DESCRIPTION = "no description entered";
const string ERROR_INVALID_COMMAND = "invalid command";

//Global Variables
static string fileName = "";

//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute
class Timetable {
private:
	vector<string> _items;
	int _size;

public:
	Timetable(void);
	~Timetable(void);
	void readItem(const string);
	void addItem(const string, const string);
	void deleteItem(const int, const string);
	void displayAll(const string);
	void clearAll(const string);
	void saveToSaveFile(const string);
	string toString();
	static void printMessage(const string);
	static void printMessage(const string, const string);
	static void printMessage(const string, const string, const string);
};
#endif 

//Alvin