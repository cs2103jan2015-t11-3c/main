#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include "Task.h"

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
class Data{
public:
	string task;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int type;
	bool complete;
};

class logic{
public:
	vector<Data> _items;
	int _size;

	logic(void);
	~logic(void);
	static void executeCommand(string, string, logic *, logic *);
	void readItem(const Data);
	void addItemtypeone(string);
	void addItemtypetwo(string task, int e_date, int e_month, int e_year, int e_time);
	void addItemtypethree(string task, int s_date, int s_month, int s_year, int s_time, int e_date, int e_month, int e_year, int e_time);
	
	string displaytypeone(int index);
	string displaytypetwo(int index);
	string displaytypethree(int index);
	string displayAll(const string);

	void deleteItem(const int, const string);
	void clearAll(const string);
	void editTask(int &, string , string );
	void markcompleted(int, const string);

	static void readToDoListFromTextFile(string fileName, logic *toDoList);

	static void printMessage(const string);
	static void printMessage(const string, const string);
	void getsize();
};
#endif 