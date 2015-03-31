#include "logic.h"


<<<<<<< HEAD
void logic::readToDoListFromTextFile(string fileName, vector<task> &toDoList) {
	fstream textFile;
	string input;//deleted string temp
	textFile.open(fileName.c_str());

	//Remove the index of each line, eg: remove "1)" from "1) Some List Entry"
	//Adds the rest of the line to the to-do list after removing leading and following whitespaces
	while(getline(textFile,input)) {
		size_t pos = input.find('.');
		input = input.substr(pos+1);
		parser parse;

		parse.trimString(input);
		string text;
		int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
		task datainput;

		if(parse.checktype(input) == 1){
			parse.splitinputtypeone(input, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(input) == 2){
			parse.splitinputtypetwo(input, text, e_date, e_month, e_year, e_time);
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(input) == 3){
			parse.splitinputtypethree(input, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}

	}
	textFile.close();
}


void logic::executeCommand(string command, string description, vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector <task>timedVec) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
    logic function;
	task datainput;
	storage store;
	parser parse;
	bool result=true;

	parse.trimString(description);

	if(!parse.isValidCommand(command, description))
		return;
	else if(command=="add" ||command =="+") {
		if(parse.checktype(description) == 1){  //floating task: add swimming 
			parse.splitinputtypeone(description, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput); //push back the floating task "swimming" into the vector toDoList
		}
		else if(parse.checktype(description) == 2){
			parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
			if(!isValidDate(e_date,e_month,e_year)) {
				cout << "inValid date, try again" << endl;
			}
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(description) == 3){
			parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			if(!isValidDate(e_date,e_month,e_year)&&!isValidDate(s_date,s_month,s_year)) {
				cout << "inValid Start and End Dates, try again" << endl;
			}else if(!isValidDate(s_date,s_month,s_year)) {
				cout << "inValid Start Date, try again" << endl;
			}else if(!isValidDate(e_date,e_month,e_year)) {
				cout << "inValid End Date, try again" << endl;
			} else {
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
			}
		}
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="delete"||command=="-"||command=="remove") {

		function.deleteItem(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="display"||command=="show") {
		cout << function.displayAll(fileName, toDoList);
		return;
	}
	else if(command=="clear"||command=="clear all") {
		function.clearAll(fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "edit"||command=="modify"||command=="change") {
		function.editTask(checkfororiginalindex(description, floatVec, deadlineVec, timedVec),fileName,description, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="exit") {
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "done") {
		function.markcompleted(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		return;
	}
	else if(command == "search") {
		function.searchTask(toDoList, fileName, description);
		return;
	}

}

//check whether input date is valid function starts here
bool logic::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool logic::isValidDate(unsigned short day,unsigned short month,unsigned short year){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}
//check whether input date is valid ends here

//search functions start here
void logic::searchTask(vector<task> &toDoList, string fileName, string description) {
	vector<task> tempVec;
	unsigned int i;
	task task;
	logic logic;
	for(i = 0; i < toDoList.size(); ++i) {
	if(!isCheckSearchStringDigit(description)) { //searched word is not a digit-->can only be found in task name
		unsigned int t = -1;
		t = (task.returntext(i,toDoList)).find(description);
		if(t != -1) {
			tempVec.push_back(toDoList[i]);
	}
	} else if(isCheckSearchStringDigit(description)) { // searched word is a pure digit-->can only be found in time/date/month/year
		int convertedInt = convertNumStringToInt(description);
		if(task.returnstarttime(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendtime(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if(task.returnstartdate(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnenddate(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnstartmonth(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendmonth(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnstartyear(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendyear(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else {}
	}
	}
	cout << logic.displayAll(fileName, tempVec);
}

bool logic::isCheckSearchStringDigit(string description) {
	unsigned int i;
	bool result = true;
	for(i = 0; i < description.size(); ++i) {
		if(!isdigit(description[i])) {
			result = false;
		}
	}
return result;
}

int logic::convertNumStringToInt(string description) {
	int convertedNum;
	convertedNum = atoi(description.c_str());
return convertedNum;
}
//search functions end here

int logic::checkfororiginalindex(string description, vector<task>floatVec, vector<task>deadlineVec, vector<task>timedVec){
	string temp;
	parser parse;
	int index, originindex;

	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"){
		originindex = floatVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "deadline"){
	    originindex = deadlineVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "timed"){
		originindex = timedVec[index].returntempnum();
	    return originindex;
	}
	else{
		originindex = parse.convertStringToIntegerIndex(description);
		return originindex;
	}
}

string logic::displayAll(const string fileName, vector<task> &toDoList) {
=======
string logic::displayAll(vector<task> &toDoList) {
>>>>>>> 9fc3cc0009c4f5bb75ba04ba831eabe0a8b823e5
	task temp;
	ostringstream oss;
	if(toDoList.size()==0)
		printMessage(ERROR_LIST_IS_EMPTY);
	else {
		for(unsigned i = 0; i < toDoList.size(); i++){
			if(toDoList[i].returntype() == 1)
				oss << toDoList[i].displaytypeone(i);
			else if(toDoList[i].returntype() == 2)
				oss << toDoList[i].displaytypetwo(i);
			else if(toDoList[i].returntype() == 3)
			    oss <<  toDoList[i].displaytypethree(i);
		}
	}
	return oss.str();
}

void logic::deleteItem(const int index, vector<task> &toDoList) {
	int size = toDoList.size();
	if(size==0) {
		printMessage(ERROR_LIST_IS_EMPTY);
	}
	else if(index>=size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		toDoList.erase(toDoList.begin()+index);
		cout << "deleted";
	}
}

void logic::clearAll(vector<task> &toDoList) {
	toDoList.clear();
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY);
}

void logic::editTask(int index, string description, vector<task> &toDoList) {
	string TextAfterIndex, VariableToChange, PartTochange, temp;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	task taskclass;
	char c;

	int size = toDoList.size();
	if(size == 0) {
		printMessage(ERROR_LIST_IS_EMPTY);
		return;
	}
	else if(index > size||index < 0) {
		printMessage(ERROR_INVALID_INDEX);
		return;
	}
	else if(toDoList[index].returntype() == 1){
		size_t pos = description.find("-name");
		PartTochange = description.substr(pos+6);
		toDoList[index].edittext(PartTochange);
	}
	else if(toDoList[index].returntype() == 2){
		size_t foundname = description.find("-name");
		size_t founddue = description.find("-due");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
		}
		else if(founddue!=std::string::npos){
			PartTochange = description.substr(founddue+5);
			istringstream in(PartTochange);
			in>>e_time;;
			in>>temp;
			in>>e_date;
			in>>c;
		    in>>e_month;
			in>>c;
		    in>>e_year;

			toDoList[index].edite_time(e_time);
			toDoList[index].edite_date(e_date);
			toDoList[index].edite_month(e_month);
			toDoList[index].edite_year(e_year);
		}
	}
	else if(toDoList[index].returntype() == 3){
		size_t foundname = description.find("-name");
		size_t foundstart = description.find("-start");
		size_t foundend = description.find("-end");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		    toDoList[index].edittext(PartTochange);
		}
		else if(foundstart!=std::string::npos){
			PartTochange = description.substr(foundstart+7);
			istringstream in(PartTochange);
			in>>s_time;
			in>>temp;
			in>>s_date;
			in>>c;
		    in>>s_month;
			in>>c;
		    in>>s_year;

			toDoList[index].edits_time(s_time);
			toDoList[index].edits_date(s_date);
			toDoList[index].edits_month(s_month);
			toDoList[index].edits_year(s_year);
		}
		else if(foundend!=std::string::npos){
			PartTochange = description.substr(foundend+5);
			istringstream in(PartTochange);
			in>>e_time;
			in>>temp;
			in>>e_date;
			in>>c;
		    in>>e_month;
			in>>c;
		    in>>e_year;

			toDoList[index].edite_time(e_time);
			toDoList[index].edite_date(e_date);
			toDoList[index].edite_month(e_month);
			toDoList[index].edite_year(e_year);
		}
	}
}

void logic::markcompleted(int index, vector<task> &toDoList){
	task temp;
	int size = toDoList.size();
	index = index - 1;

	if(size==0) {
		printMessage(ERROR_LIST_IS_EMPTY);
	}
	else if(index>=size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		toDoList[index].editDone(true);
		cout << "task marked completed";
	}
}

void logic::sorttext(vector<task> &toDoList){
	int size = toDoList.size();
	task temp;
	
	for(int i=0; i<size-1; ++i){
		for(int j=1; j<size-i; ++j){
			if(toDoList[j-1].returntext().compare(toDoList[j].returntext())>0){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}

/* //will cause assertion error, need to debug
void logic::sortdates(vector<task> &toDoList){
	unsigned int i, j;
	task temp;

	for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(toDoList[j-1].returnendyear() > toDoList[j].returnendyear()) {
				vector<task> tempVec;
				tempVec.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec[0];
				tempVec.pop_back();
 			}
			else{}
		}
	
	}//sort year

	for(i = 0; i < toDoList.size()-1; ++i) {
		if(toDoList[i].returnendyear() == toDoList[i+1].returnendyear()){
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((toDoList[j-1].returnendmonth() > toDoList[j].returnendmonth())
				&&(toDoList[j-1].returnendyear() == toDoList[j].returnendyear())) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else{}
	}//sort month

	for(i = 0; i < toDoList.size()-1; ++i) {
		if((toDoList[i].returnendyear() == toDoList[i+1].returnendyear())
			&&(toDoList[i].returnendmonth() == toDoList[i+1].returnendmonth())) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((toDoList[j-1].returnenddate() > toDoList[j].returnenddate())
				&&(toDoList[j-1].returnendyear() == toDoList[j].returnendyear())
				&&(toDoList[j-1].returnendmonth() == toDoList[j].returnendmonth())) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}//sort date
	
};*/

/*void logic::sorttime(vector<task> &toDoList){
	task temp;
	unsigned int i , j;
	int tempone, temptwo;

	for(i = 0; i < toDoList.size()-1; ++i) {
		tempone = toDoList[i].returnendyear();
		temptwo = toDoList[i+1].returnendyear();
		if(( tempone == temptwo)
			&&(toDoList[i].returnendmonth() == toDoList[i+1].returnendmonth())
			&&(toDoList[i].returnendyear() ==toDoList[i+1].returnendyear())) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((toDoList[j-1].returnendtime() > toDoList[j-1].returnendtime())
				&&(toDoList[j-1].returnenddate() == toDoList[j].returnenddate())
				&&(toDoList[j-1].returnendyear() == toDoList[j].returnendyear())
				&&(toDoList[j-1].returnendmonth() == toDoList[j].returnendmonth())) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}
}*/

void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}




