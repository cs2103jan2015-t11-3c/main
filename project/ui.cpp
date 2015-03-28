#include <iostream>
#include <vector>
#include <sstream>
#include "logic.h"
#include "parser.h"
#include "Task.h"
#include <fstream> 
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;
string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec);
void showDefaultTaskList(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec);


int main(int argc, char *argv[]) {
	vector<task> toDoList, floatVec, deadlineVec, timedVec;//global scope
	logic function;

	getTextFileName(argc, argv);
	function.readToDoListFromTextFile(getTextFileName(argc, argv), toDoList );
	printWelcomeMessage();
	readinput(toDoList, floatVec, deadlineVec, timedVec);

	return 0;
}

string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
	return fileName;
}

void printWelcomeMessage() {
	cout << "**********************************************************************" << endl;
	cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
	cout << "**********************************************************************" << endl;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	cout << "Current Singapore Local Time: ";
    cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
	cout << "**********************************************************************" << endl;
}

void showDefaultTaskList(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec) {
	int index, i=0, j=0, k=0;
	task temp;
	logic function;
	vector<task> tempVec;
	floatVec.clear();
	deadlineVec.clear();
	timedVec.clear();
	
	for(index = 0; index != toDoList.size(); ++index) {
		tempVec.push_back(toDoList[index]);
	}


	for(index = 0; index != tempVec.size(); ++index) {
		if(temp.returntype(index, tempVec) == 1){
			floatVec.push_back(tempVec[index]);
			floatVec[i].inserttempnum(index);
			i++;
		}
		else if(temp.returntype(index, tempVec) == 2){
			deadlineVec.push_back(tempVec[index]);
			deadlineVec[j].inserttempnum(index);
			j++;
		}
		else {
			timedVec.push_back(tempVec[index]);
			timedVec[k].inserttempnum(index);
			k++;
		}
	}
	
	//*************************(1) float task (1)****************************************************************************
	function.sorttext(floatVec);
	
	cout << "Floating tasks:" << endl;
	for(index = 0; index != floatVec.size(); ++index)
		cout << temp.displaytypeone(index, floatVec);


	//*************************(2) deadline task (2)****************************************************************************
    function.sortdates(deadlineVec);
	function.sorttime(deadlineVec);

	cout << endl << endl << "Deadline tasks:" << endl;
	for(index = 0; index != deadlineVec.size(); ++index) 
		cout << temp.displaytypetwo(index, deadlineVec);


	//*************************(3) timed task (3)****************************************************************************
	function.sortdates(timedVec);
	function.sorttime(timedVec);
	
	cout << endl << endl <<  "Timed tasks:" << endl;
	for(index = 0; index != timedVec.size(); ++index)
	    cout << temp.displaytypethree(index, timedVec);

	cout << endl <<"**********************************************************************" << endl;
	
}

void readinput(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec){
	string command, description;
	logic function;

	while(command!="exit"){
		//showDefaultTaskList(toDoList, floatVec, deadlineVec, timedVec);
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
		function.executeCommand(command, description, toDoList, floatVec, deadlineVec, timedVec);
	};
}


