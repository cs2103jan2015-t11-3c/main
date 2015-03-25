#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class task{
public://!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int type;
	bool complete;

public:
	task(void);
	~task(void);

	void addItemtypeone(string text);
	void addItemtypetwo(string task, int _e_date, int _e_month, int _e_year, int _e_time);
	void addItemtypethree(string task, int _s_date, int _s_month, int _s_year, int _s_time, int _e_date, int _e_month, int _e_year, int _e_time);
	void completed(int index, vector<task> &toDoList);
	void edittext(int index, string PartTochange, vector<task> &toDoList);
	void edits_time(int index, int PartTochange, vector<task> &toDoList);
	void edits_date(int index, int PartTochange, vector<task> &toDoList);
	void edits_month(int index, int PartTochange, vector<task> &toDoList);
	void edits_year(int index, int PartTochange, vector<task> &toDoList);
	void edite_time(int index, int PartTochange, vector<task> &toDoList);
	void edite_date(int index, int PartTochange, vector<task> &toDoList);
	void edite_month(int index, int PartTochange, vector<task> &toDoList);
	void edite_year(int index, int PartTochange, vector<task> &toDoList);


	string displaytypeone(int index, vector<task> &toDoList);
	string displaytypetwo(int index, vector<task> &toDoList);
	string displaytypethree(int index, vector<task> &toDoList);

	int returntype(int index, vector<task> &toDoList);
};

#endif