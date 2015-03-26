#include "Task.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

task::task(void) {}

task::~task(void) {}

void task::inserttempnum(int index){
	tempnum = index;
};

void task::addItemtypeone(string _text){

	text = _text;
	s_date=0;
	s_month=0;
	s_year=0;
	s_time=0;
	e_date=0;
	e_month=0;
	e_year=0;
	e_time=0;
	type = 1;
	complete = false;
}

void task::addItemtypetwo(string task, int _e_date, int _e_month, int _e_year, int _e_time){ 

	text = task;
	s_date=0;
	s_month=0;
	s_year=0;
	s_time=0;
	e_date= _e_date;
	e_month= _e_month;
	e_year= _e_year;
	e_time= _e_time;
	type = 2;
	complete = false;
}

void task::addItemtypethree(string task, int _s_date, int _s_month, int _s_year, int _s_time, int _e_date, int _e_month, int _e_year, int _e_time){ 
	
	text = task;
	s_date= _s_date;
	s_month= _s_month;
	s_year= _s_year;
	s_time= _s_time;
	e_date= _e_date;
	e_month= _e_month;
	e_year= _e_year;
	e_time= _e_time;
	type = 3;
	complete = false;
}

void task::completed(int index, vector<task> &toDoList){
	complete = true;
};

void task::edittext(int index, string PartTochange, vector<task> &toDoList){
	toDoList[index].text = PartTochange;
};

void task::edits_time(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].s_time = PartTochange;
};

void task::edits_date(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].s_date = PartTochange;
};

void task::edits_month(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].s_month = PartTochange;
};

void task::edits_year(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].s_year = PartTochange;
};

void task::edite_time(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].e_time = PartTochange;
};

void task::edite_date(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].e_date = PartTochange;
};

void task::edite_month(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].e_month = PartTochange;
};

void task::edite_year(int index, int PartTochange, vector<task> &toDoList){
	toDoList[index].e_year = PartTochange;
};

string task::displaytypeone(int index, vector<task> &toDoList){
	ostringstream oss;
	oss << endl<<  index+1 << "." << toDoList[index].text;
	return oss.str();
}

string task::displaytypetwo(int index, vector<task> &toDoList){
	ostringstream oss;
	oss << endl<<  index+1 << "." << toDoList[index].text <<  " by " << toDoList[index].e_time << " on " << toDoList[index].e_date<<"/"
			<< toDoList[index].e_month << "/" << toDoList[index].e_year;
	return oss.str();
}//changed "/"

string task::displaytypethree(int index, vector<task> &toDoList){
	ostringstream oss;
	 oss << endl << index+1 << "." << toDoList[index].text << " from " <<toDoList[index].s_time << " on "<<toDoList[index].s_date<<"/"
			<< toDoList[index].s_month << "/" << toDoList[index].s_year << " to " << toDoList[index].e_time << " on " << toDoList[index].e_date<<"/"
			<< toDoList[index].e_month << "/" << toDoList[index].e_year ;
	return oss.str();
}//changed "/"

int task::returntype(int index, vector<task> &toDoList){
	return toDoList[index].type;
}

string task::returntext(int index, vector<task>&toDoList){
	return toDoList[index].text;
}

int task::returnenddate(int index, vector<task>&toDoList){
	return toDoList[index].e_date;
}

int task::returnendmonth(int index, vector<task>&toDoList){
	return toDoList[index].e_month;
}

int task::returnendyear(int index, vector<task>&toDoList){
	return toDoList[index].e_year;
}

int task::returnendtime(int index, vector<task>&toDoList){
	return toDoList[index].e_time;
}

int task::returnstartdate(int index, vector<task>&toDoList){
	return toDoList[index].s_date;
}

int task::returnstartmonth(int index, vector<task>&toDoList){
	return toDoList[index].s_month;
}

int task::returnstartyear(int index, vector<task>&toDoList){
	return toDoList[index].s_year;
}

int task::returnstarttime(int index, vector<task>&toDoList){
	return toDoList[index].e_time;
}

int task::returntempnum(){
	return tempnum;
}