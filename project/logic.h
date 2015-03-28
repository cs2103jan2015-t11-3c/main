#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include "undo.h"

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
const string ERROR_MISSING_INDEX="missing index";

//Global Variables
static string fileName = "";

//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute

class logic{
public:
	void readToDoListFromTextFile(string fileName, vector<task> &toDoList);

	void executeCommand(string command, string description, vector<task> &toDoList, vector<task> &floatVec, 
		vector<task> &deadlineVec, vector<task> &timedVec, vector<undo> &undomemory, undo &currentmemory);
	int checkfororiginalindex(string description, vector<task>floatVec, vector<task>deadlineVec, vector<task>timedVec);
	
	string displayAll(const string, vector<task> &);
	void deleteItem(const int, const string, vector<task> &);
	void clearAll(const string, vector<task> &);
	void editTask(int , string , string , vector<task> &);
	void markcompleted(int, const string, vector<task> &);
	void sorttext(vector<task> &);
	void sortdates(vector<task> &);
	void sorttime(vector<task> &);

	void searchTask(vector<task> &, string, string);
	bool isCheckSearchStringDigit(string);
	int convertNumStringToInt(string);

	void printMessage(const string);
	void printMessage(const string, const string);
};
#endif 