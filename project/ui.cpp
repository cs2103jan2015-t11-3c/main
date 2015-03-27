#include <iostream>
#include <vector>
#include <sstream>
#include "logic.h"
#include "parser.h"
#include "Task.h"
#include <fstream> 
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;
//DON'T MESS WITH THE REPO
string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec);
void showDefaultTaskList(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec);//ui


int main(int argc, char *argv[]) {
	vector<task> toDoList, floatVec, deadlineVec, timedVec;
	logic function;

	getTextFileName(argc, argv);
	function.readToDoListFromTextFile(getTextFileName(argc, argv), toDoList );//logic function 
	printWelcomeMessage();
	readinput(toDoList, floatVec, deadlineVec, timedVec);

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

void readinput(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec){
	string command, description;
	logic function;

	while(command!="exit"){
		showDefaultTaskList(toDoList, floatVec, deadlineVec, timedVec);
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
		function.executeCommand(command, description, toDoList, floatVec, deadlineVec, timedVec);
	};
}

void showDefaultTaskList(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec) { //ui
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



