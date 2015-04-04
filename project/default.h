#ifndef DEFAULT_H
#define DEFAULT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Task.h"
#include "logic.h"
#include "parser.h"
#include "undo.h"
#include "recurringTask.h"

using namespace std;

class defaultclass{
private:
	vector<task> floatVec;
	vector<task> deadlineVec;
	vector<task> timedVec;
	vector<task> todayTaskVec;
	vector<task> tomorTaskVec;
	
public:
	void updatedefaultmemory(vector<task> &toDoList);

	void showDefaultTaskList(vector<task> &toDoList, defaultclass &defaultmemory);
	void defaultexecuteCommand(storage *store, string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentmemory);
	int checkfororiginalindex(string description, defaultclass defaultmemory, vector<task> &tempVec);

	bool defaultclass::checkIfIsToday(int e_day,int e_month,int e_year);
	bool defaultclass::checkIfIsTomorrow(int e_day,int e_month,int e_year);
};
#endif


