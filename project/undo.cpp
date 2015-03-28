#include "undo.h"

undo::undo(void) {}

undo::~undo(void) {}


undo undo::converttoundoclass(vector<undo> &undomemory, vector<task> toDoList){
	int index = undomemory.size();
	undo task;

	task.memory = toDoList;
	task.num = index;
	return task;
}

vector<task> undo::returnmemory(){
	return memory;
}

int undo::returncommandnumber(){
	return num;
}
