#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream> 
#include "task.h"

using namespace std;

class storage
{

public:
	storage(void);
	~storage(void);
	
	string toString(vector<task> &toDoList);

	void readToDoListFromTextFile(string fileName, vector<task> &toDoList) ;
	void saveToSaveFile(const string fileName, vector<task> &toDoList);

	bool changeDirectory(string newFilePath,string fileName, vector<task> &toDoList);
	bool fileExists(const string& fileName);
    string getFullFileName(string newFilePath, string fileName);

	bool isFloatDuplicated(task newTask, vector<task> &toDoList);	
	bool isDeadlineDuplicated(task newTask, vector<task> &toDoList);
	bool isTimeClashed(task newTask, vector<task> &toDoList);


};