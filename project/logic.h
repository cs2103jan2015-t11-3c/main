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
#include "search.h"

using namespace std;

//Constants
const string DELIMITERS = " \n\t\v";
const string DEFAULT_SAVE_FILENAME = "SaveFile.txt";
const int FILE_NAME_ARG_NUMBER = 1;
const string MESSAGE_ITEM_ADDED_SUCCESSFULLY = "added to file";
const string MESSAGE_ITEM_DELETED_SUCCESSFULLY = "deleted from file";
const string MESSAGE_ITEMS_CLEARED_SUCCESSFULLY = "all content deleted from file";
const string ERROR_LIST_IS_EMPTY = "file is empty";
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
	string displayAll(vector<task> &);
	void deleteItem(const int index, vector<task> &toDoList);
	void clearAll(vector<task> &toDoList);
	void editTask(int index, string description, vector<task> &toDoList);
	void markcompleted(int index, vector<task> &toDoList);
	void sorttext(vector<task> &toDoList);
	//void sortdates(vector<task> &);
	//void sorttime(vector<task> &);

	bool isleapyear(unsigned short);
	bool isValidDate(unsigned short,unsigned short,unsigned short);

	void printMessage(const string);
	void printMessage(const string, const string);
	
};
#endif 
