#pragma once
#include "task.h"

using namespace std;

class storage
{
private:
	vector<task> _toDoList;

public:
	storage(void);
	~storage(void);
	
	string toString(vector<task> &toDoList);
	void displayAll(const string fileName);
	void saveToSaveFile(const string fileName,vector<task> &toDoList);

	vector<task> readToDoListFromTextFile(string fileName) ;

	 bool storage::changeDirectory(string newFilePath,string fileName,vector<task> &toDoList);
	 bool storage::fileExists(const string& fileName);
     string getFullFileName(string newFilePath, string fileName);

	bool isTaskDuplicated(task newTask);
	bool isFloatDuplicated(task newTask);	
	bool isDeadlineDuplicated(task newTask);
	bool isTimeClashed(task newTas);


};
