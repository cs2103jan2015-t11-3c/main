#include "Task.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
//work in progress

task::task(void) {
}

task::~task(void) {
}


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

void task::addItemtypetwo(string text, int _e_date, int _e_month, int _e_year, int _e_time){ 

	text = text;
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

void task::addItemtypethree(string text, int _s_date, int _s_month, int _s_year, int _s_time, int _e_date, int _e_month, int _e_year, int _e_time){ 
	
	text = text;
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

string task::displaytypeone(int index, vector<task> &toDoList){
	ostringstream oss;
	oss << endl<<  index+1 << "." << toDoList[index].text;
	return oss.str();
}

string task::displaytypetwo(int index, vector<task> &toDoList){
	ostringstream oss;
	oss << endl<<  index+1 << "." << toDoList[index].text <<  " by " << toDoList[index].e_time << " on " << toDoList[index].e_date<<" "
			<< toDoList[index].e_month << " " << toDoList[index].e_year;
	return oss.str();
}

string task::displaytypethree(int index, vector<task> &toDoList){
	ostringstream oss;
	 oss << endl << index+1 << "." << toDoList[index].text << " from " <<toDoList[index].s_time << " on "<<toDoList[index].s_date<<" "
			<< toDoList[index].s_month << " " << toDoList[index].s_year << " to " << toDoList[index].e_time << " on " << toDoList[index].e_date<<" "
			<< toDoList[index].e_month << " " << toDoList[index].e_year ;
	return oss.str();
}

int task::returntype(int index, vector<task> &toDoList){
	return toDoList[index].type;
}

