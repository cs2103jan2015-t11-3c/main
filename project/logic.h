#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include "undo.h"

using namespace std;

//Constants

const string DEFAULT_SAVE_FILENAME = "SaveFile";
const int FILE_NAME_ARG_NUMBER = 1;
const string MESSAGE_ITEM_ADDED_SUCCESSFULLY = "added to file";
const string MESSAGE_ITEM_DELETED_SUCCESSFULLY = "deleted from file";
const string MESSAGE_ITEMS_CLEARED_SUCCESSFULLY = "all content deleted from file";
const string ERROR_LIST_IS_EMPTY = "file is empty";
const string INVALID_INDEX = "invalid index";


//Global Variables
static string fileName = "";

//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute

class logic{
public:

	void sortEndTime(vector<task> &);

	string displayAll(vector<task> &);
	
	void deleteItem(const int index, vector<task> &toDoList);
	void clearAll(vector<task> &toDoList);
	void editTask(int index, string description, vector<task> &toDoList);
	void markcompleted(int index, vector<task> &toDoList);
	void sorttext(vector<task> &toDoList);
	void sortdates(vector<task> &);
	void sorttime(vector<task> &);

	void searchTask(vector<task> &, vector<task> &, string, string);
	bool isCheckSearchStringDigit(string);
	int convertNumStringToInt(string);

	void display(vector<task> &, vector<task> &, string, string);
	int getSystemDay();
	int getSystemMonth();
	int getSystemYear();

	void pushback(vector<task>& toDoList, vector<task>& tempVec, int index);

	bool isleapyear(unsigned short);
	bool isValidDate(unsigned short,unsigned short,unsigned short);
	bool isValidTime(int);
	bool checkIsDateOverdue(int, int, int);

	void printMessage(const string);
	void printMessage(const string, const string);
	
};

