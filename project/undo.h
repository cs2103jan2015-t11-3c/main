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

	undo converttoundoclass(vector<undo> &undomemory, vector<task> toDoList);
	vector<task> returnmemory();
	int returnnum();
};

