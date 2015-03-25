#include <iostream>
#include <vector>
#include <sstream>
#include "logic.h"
#include "parser.h"
#include <fstream> 
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &);
void showDefaultTaskList(vector<task> &);//ui


int main(int argc, char *argv[]) {
	vector<task> toDoList;
	logic function;

	getTextFileName(argc, argv);
	function.readToDoListFromTextFile(getTextFileName(argc, argv), toDoList );//logic function 
	printWelcomeMessage();
	showDefaultTaskList(toDoList);
	readinput(toDoList);

	return 0;
}

string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];//input.txt
	return fileName;
}

void printWelcomeMessage() {
	cout << "**********************************************************************" << endl;
	cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
	cout << "**********************************************************************" << endl;
}

void showDefaultTaskList(vector<task> &toDoList) { //ui
	int index;

	vector<task> tempVec;
	vector<task> floatVec;
	vector<task> deadlineVec;
	vector<task> timedVec;
	
	for(index = 0; index != toDoList.size(); ++index) {
		tempVec.push_back(toDoList[index]);
	}


	for(index = 0; index != tempVec.size(); ++index) {
		if(tempVec[index].s_time!=0){
			timedVec.push_back(tempVec[index]);
			tempVec[index].e_time=0;

		}
		else if(tempVec[index].e_time != 0){
			deadlineVec.push_back(tempVec[index]);
		}
		else {
			floatVec.push_back(tempVec[index]);
		}
	}

	//*************************(1) float task (1)****************************************************************************

	//sort::
	vector<string> sortFloatTasksVec;
	for(index = 0; index != floatVec.size(); ++index){
		sortFloatTasksVec.push_back(floatVec[index].text);
	}
	sort(sortFloatTasksVec.begin(),sortFloatTasksVec.end());
	//finish sorting

	cout << "Floating tasks:" << endl;
	for(index = 0; index != floatVec.size(); ++index) {
		ostringstream oss;
		oss << endl<<  index+1 << "." << sortFloatTasksVec[index];
	    cout << oss.str() << endl;
	}
	

	//*************************(2) deadline task (2)****************************************************************************
    unsigned int i, j;

	for(i = 0; i < deadlineVec.size(); ++i) {
		for(j = 1; j < deadlineVec.size() - i; ++j) {
			if(deadlineVec[j-1].e_year > deadlineVec[j].e_year) {
				vector<task> tempVec;
				tempVec.push_back(deadlineVec[j-1]);
				deadlineVec[j-1] = deadlineVec[j];
				deadlineVec[j] = tempVec[0];
				tempVec.pop_back();
 			}
		}
	}//sort year
	
	
	for(i = 0; i < deadlineVec.size()-1; ++i) {
		if(deadlineVec[i].e_year == deadlineVec[i+1].e_year) {
		for(j = 1; j < deadlineVec.size()-i; ++j) {
			if((deadlineVec[j-1].e_month > deadlineVec[j].e_month)&&(deadlineVec[j-1].e_year == deadlineVec[j].e_year)) {
				vector<task> tempVec1;
				tempVec1.push_back(deadlineVec[j-1]);
				deadlineVec[j-1] = deadlineVec[j];
				deadlineVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort month

	for(i = 0; i < deadlineVec.size()-1; ++i) {
		if((deadlineVec[i].e_year == deadlineVec[i+1].e_year)&&(deadlineVec[i].e_month == deadlineVec[i+1].e_month)) {
		for(j = 1; j < deadlineVec.size()-i; ++j) {
			if((deadlineVec[j-1].e_date > deadlineVec[j].e_date)&&(deadlineVec[j-1].e_year == deadlineVec[j].e_year)&&(deadlineVec[j-1].e_month == deadlineVec[j].e_month)) {
				vector<task> tempVec1;
				tempVec1.push_back(deadlineVec[j-1]);
				deadlineVec[j-1] = deadlineVec[j];
				deadlineVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort date


	for(i = 0; i < deadlineVec.size()-1; ++i) {
		if((deadlineVec[i].e_year == deadlineVec[i+1].e_year)&&(deadlineVec[i].e_month == deadlineVec[i+1].e_month)&&(deadlineVec[i].e_date == deadlineVec[i+1].e_date)) {
		for(j = 1; j < deadlineVec.size()-i; ++j) {
			if((deadlineVec[j-1].e_time > deadlineVec[j].e_time)&&(deadlineVec[j-1].e_year == deadlineVec[j].e_year)
				&&(deadlineVec[j-1].e_month == deadlineVec[j].e_month)&&(deadlineVec[j-1].e_date == deadlineVec[j].e_date)) {
				vector<task> tempVec1;
				tempVec1.push_back(deadlineVec[j-1]);
				deadlineVec[j-1] = deadlineVec[j];
				deadlineVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else{}
	}//sort end-time

	cout << endl << "Deadline tasks:" << endl;
	for(index = 0; index != deadlineVec.size(); ++index) {
		ostringstream oss;
		oss << endl<<  index+1 << "." << deadlineVec[index].text <<  " by " << deadlineVec[index].e_time << " on " << deadlineVec[index].e_date<<"/"
			<< deadlineVec[index].e_month << "/" << deadlineVec[index].e_year;
	    cout << oss.str() << endl;
	}


	//*************************(3i) timed task (3i)****************************************************************************

	
	for(i = 0; i < timedVec.size(); ++i) {
		for(j = 1; j < timedVec.size() - i; ++j) {
			if(timedVec[j-1].e_year > timedVec[j].e_year) {
				vector<task> tempVec;
				tempVec.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec[0];
				tempVec.pop_back();
 			}
		}
	}//sort year



	
	for(i = 0; i < timedVec.size()-1; ++i) {
		if(timedVec[i].e_year == timedVec[i+1].e_year) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].e_year == timedVec[j].e_year)&&(timedVec[j-1].e_month > timedVec[j].e_month)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort month

	
	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_year == timedVec[i+1].e_year)&&(timedVec[i].e_month == timedVec[i+1].e_month)) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].e_date > timedVec[j].e_date)&&(timedVec[j-1].e_year == timedVec[j].e_year)&&(timedVec[j-1].e_month == timedVec[j].e_month)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort date


	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_year == timedVec[i+1].e_year)
			&&(timedVec[i].e_month == timedVec[i+1].e_month)&&(timedVec[i].e_date == timedVec[i+1].e_date)) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].e_time > timedVec[j].e_time)&&(timedVec[j-1].e_year == timedVec[j].e_year)
					&&(timedVec[j-1].e_month == timedVec[j].e_month)&&(timedVec[j-1].e_date == timedVec[j].e_date)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else{}
	}//sort end-time

	//*************************(3ii) timed task (3ii)****************************************************************************

	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_time == timedVec[i+1].e_time)&&(timedVec[i].e_year == timedVec[i+1].e_year)
			&&(timedVec[i].e_month == timedVec[i+1].e_month)&&(timedVec[i].e_date == timedVec[i+1].e_date)){
		for(j = 1; j < timedVec.size() - i; ++j) {
			if(timedVec[j-1].s_year > timedVec[j].s_year) {
				vector<task> tempVec;
				tempVec.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec[0];
				tempVec.pop_back();
 			}
		}
		}
		else{}
	}//sort year if end time all the same



	
	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_time == timedVec[i+1].e_time)&&(timedVec[i].e_year == timedVec[i+1].e_year)
			&&(timedVec[i].e_month == timedVec[i+1].e_month)&&(timedVec[i].e_date == timedVec[i+1].e_date)) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].s_year == timedVec[j].s_year)&&(timedVec[j-1].s_month > timedVec[j].s_month)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort month

	
	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_time == timedVec[i+1].e_time)&&(timedVec[i].e_year == timedVec[i+1].e_year)
			&&(timedVec[i].e_month == timedVec[i+1].e_month)&&(timedVec[i].e_date == timedVec[i+1].e_date)) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].s_date > timedVec[j].s_date)&&(timedVec[j-1].s_year == timedVec[j].s_year)
					&&(timedVec[j-1].s_month == timedVec[j].s_month)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else {}
	}//sort date

	
	for(i = 0; i < timedVec.size()-1; ++i) {
		if((timedVec[i].e_time == timedVec[i+1].e_time)&&(timedVec[i].e_year == timedVec[i+1].e_year)
			&&(timedVec[i].e_month == timedVec[i+1].e_month)&&(timedVec[i].e_date == timedVec[i+1].e_date)) {
			for(j = 1; j < timedVec.size()-i; ++j) {
				if((timedVec[j-1].s_time > timedVec[j].s_time)&&(timedVec[j-1].s_year == timedVec[j].s_year)
					&&(timedVec[j-1].s_month == timedVec[j].s_month)&&(timedVec[j-1].s_date == timedVec[j].s_date)) {
				vector<task> tempVec1;
				tempVec1.push_back(timedVec[j-1]);
				timedVec[j-1] = timedVec[j];
				timedVec[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else{}
	}//sort end-time
	

	cout << endl << "Timed tasks:" << endl;
	for(index = 0; index != timedVec.size(); ++index) {
		ostringstream oss;
	    oss << endl << index+1 << "." << timedVec[index].text << " from " <<timedVec[index].s_time << " on "<<timedVec[index].s_date<<"/"
			<< timedVec[index].s_month << "/" << timedVec[index].s_year << " to " << timedVec[index].e_time << " on " << timedVec[index].e_date<<"/"
			<< timedVec[index].e_month << "/" << timedVec[index].e_year ;
	    cout << oss.str() << endl;
	
	}

	cout << "**********************************************************************" << endl;

}



void readinput(vector<task> &toDoList){
	string command, description;
	logic function;

	while(command!="exit"){
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
		function.executeCommand(command, description, toDoList);
	};
}
