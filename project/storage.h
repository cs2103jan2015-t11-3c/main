#pragma once
#include "task.h"

using namespace std;

class storage
{
private:
	vector<task> _toDoList;
	string _filePath;
	string _fileName;

public:
	storage(void);
	~storage(void);
	
	string toString(vector<task> &toDoList);
	
	void saveToSaveFile(const string fileName,vector<task> &toDoList);
	vector<task> readToDoListFromTextFile(string fileName) ;

	bool changeDirectory(string newFilePath,string fileName,vector<task> &toDoList);
    bool storage::changeFileName(string newfileName,vector<task> &toDoList);
    bool fileExists(const string& fileName);
	void setFileName(string newFileName);
	void setFilePath(string newFilePath);
	string getCurrentFileName();
	string getCurrentFilePath();


    string getFileNameAndDirectory(string newFilePath, string fileName);

	bool isFloatDuplicated(task newTask, vector<task> &toDoList);
	bool isDeadlineDuplicated(task newTask, vector<task> &toDoList);
	bool isTimeClashed(task newTas, vector<task> &toDoList);


};
