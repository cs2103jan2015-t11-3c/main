#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class undo{
private:
	vector<task> memory;
	int num;

public:
	undo(void);
	~undo(void);

	//convert toDoList to undo class
	//pre: undomemory vecotr, main vector
	//post: none
	undo converttoundoclass(vector<undo> &undomemory, vector<task> toDoList);

	// return vector<task>
	//pre: none
	//post: none
	vector<task> returnmemory();

	// return num
	//pre: none
	//Post: none
	int returnnum();
};

