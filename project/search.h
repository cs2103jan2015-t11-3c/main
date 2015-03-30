#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include "Task.h"
#include "logic.h"
#include "parser.h"
#include "default.h"

using namespace std;

class searchclass{
public:
	void searchexecuteCommand(string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentundomemory);
	int checkfororiginalindex(string description, vector<task>tempvec);
	void searchTask(vector<task> &, vector<task> &, string, string);
	bool isCheckSearchStringDigit(string);
	int convertNumStringToInt(string);
	void pushback(vector<task>& toDoList, vector<task>& tempVec, int index);
	
};
#endif
