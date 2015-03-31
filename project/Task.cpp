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

void task::edittext(string PartTochange){
	text=PartTochange;
	return;
}
void task::edits_time(int PartTochange){
	s_time=PartTochange;
	return;

}
void task::edits_date(int PartTochange){
	s_date=PartTochange;
	return;
}
void task::edits_month(int PartTochange){
	s_month=PartTochange;
	return;
}
void task::edits_year(int PartTochange){
	s_year=PartTochange;
	return;
}
void task::edite_time(int PartTochange){
	e_time=PartTochange;
	return;
}
void task::edite_date(int PartTochange){
	e_date=PartTochange;
	return;
}
void task::edite_month(int PartTochange){
	e_month=PartTochange;
	return;
}
void task::edite_year(int PartTochange){
	e_year=PartTochange;
	return;
}

void task::editType(int PartTochange){
	type=PartTochange;
	return;
}
void task::editDone(bool PartTochange){
	complete=PartTochange;
	return;
}

void task::edittemp(int index){
	temp = index;
	return;
}


string task::displaytypeone(int index){
	ostringstream oss;
	oss << endl<<  index+1 << "." << text;
	return oss.str();
}

string task::displaytypetwo(int index){
	ostringstream oss;
	oss << endl<<  index+1 << "." << text <<  " by " << e_time << " on " << e_date<<"/"
			<< e_month << "/" << e_year;
	return oss.str();
}

string task::displaytypethree(int index){
	ostringstream oss;
	 oss << endl << index+1 << "." << text << " from " <<s_time << " on "<<s_date<<"/"
			<< s_month << "/" << s_year << " to " << e_time << " on " << e_date<<"/"
			<< e_month << "/" << e_year ;
	return oss.str();
}

int task::returntype(){
	return type;
}

bool task::returnstatus(){
	return complete;
}

string task::returntext(){
	return text;
}

int task::returnenddate(){
	return e_date;
}

int task::returnendmonth(){
	return e_month;
}

int task::returnendyear(){
	return e_year;
}

int task::returnendtime(){
	return e_time;
}

int task::returnstartdate(){
	return s_date;
}

int task::returnstartmonth(){
	return s_month;
}

int task::returnstartyear(){
	return s_year;
}

int task::returnstarttime(){
	return s_time;
}

int task::returntempnum(){
	return tempnum;
}

int task::returntemp(){
	return temp;
}