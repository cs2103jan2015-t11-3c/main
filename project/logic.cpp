#include "logic.h"
#include <iostream>

string logic::displayAll(vector<task> &tempVec) {
	vector<task> temp, other;
	vector<vector<task>> temps;
	ostringstream oss;
	int i = 0;
	task temp_t;
	if(tempVec.size()==0)
		printMessage(ERROR_LIST_IS_EMPTY);
	else {
		separateFloatAndOthers(tempVec, temp, other);

		sorttext(temp);
		oss <<"Float Task: " << endl << printFloatTasks(temp, i);

		if(other.size() != 0){
			sortdates(other);
			sortOthers(other, temp);
			oss << printOthers(temp, i);
		}
	}
	tempVec = temp;
	return oss.str();
}

void logic::separateFloatAndOthers(vector<task> & tempVec, vector<task> & floattemp, vector<task> & other){
	for(unsigned j = 0; j < tempVec.size(); j++){
			if(tempVec[j].returntype() == "float"){
				floattemp.push_back(tempVec[j]);
			}
			else
				other.push_back(tempVec[j]);
		}
}

string logic::printFloatTasks(vector<task> & floattemp, int i){
	ostringstream oss;
	for(unsigned j = 0; j < floattemp.size(); j++){
			oss << floattemp[j].displayFloat(i) << endl;
			i++;
		}
	return oss.str();
}

void logic::sortOthers(vector<task> & other, vector<task> & temp){
	vector<task> temporary;
	temporary.push_back(other[0]);
	for(int j = 0; j < other.size() - 1 ; j++){
		if((other[j].returnenddate() == other[j+1].returnenddate()) && (other[j].returnendmonth() == other[j+1].returnendmonth()) && 
			(other[j].returnendyear() == other[j].returnendyear())){
				temporary.push_back(other[j+1]);
		}
		else{
			sortEndTime(temporary);
			for( unsigned k = 0; k<temporary.size(); k++)
				temp.push_back(temporary[k]);
			temporary.clear();
			temporary.push_back(other[j+1]);
		}
	}
	sortEndTime(temporary);
	for( unsigned k = 0; k<temporary.size(); k++)
		temp.push_back(temporary[k]);
}

string logic::printOthers(vector<task> & temp, int i){
	ostringstream oss;
	i++;
	oss << endl << "Date: " << temp[i].returnenddate() << "/" << temp[i].returnendmonth() << "/" << temp[i].returnendyear() << endl;
	if(temp[i].returntype() == "deadline")
		oss << temp[i].displayDefaultTasks(i) << endl;
	else if(temp[i].returntype() == "timed"){
		if((temp[i].returnenddate() != temp[i].returnenddate())||(temp[i].returnendmonth() != temp[i].returnstartmonth()))
			oss << temp[i].displayDefaultTasksOver2days(i) << endl;
		else
			oss <<  temp[i].displayDefaultTasksWithTwoTimes(i) << endl;
	}

	while(i != temp.size() - 1){
		if((temp[i].returnenddate() != temp[i+1].returnenddate())||(temp[i].returnendmonth() != temp[i+1].returnendmonth()) || 
			(temp[i].returnendyear() != temp[i+1].returnendyear()))
			oss << endl << "Date: " << temp[i+1].returnenddate() << "/" << temp[i+1].returnendmonth() << "/" << temp[i+1].returnendyear() << endl;
		if(temp[i+1].returntype() == "deadline")
			oss << temp[i+1].displayDefaultTasks(i+1) << endl;
		else if(temp[i+1].returntype() == "timed"){
			if((temp[i+1].returnenddate() != temp[i+1].returnstartdate())||(temp[i+1].returnendmonth() != temp[i+1].returnstartmonth()))
				oss << temp[i+1].displayDefaultTasksOver2days(i+1) << endl;
			else
				oss <<  temp[i+1].displayDefaultTasksWithTwoTimes(i+1) << endl;
		}
		i++;
	}
	return oss.str();
}

void logic::editTask(int index, string description, vector<task> &toDoList) {

	if(toDoList[index].returntype() == "float") {
		editFloatClass(toDoList, description, index);
	} else if(toDoList[index].returntype() == "deadline"){
		editDeadlineClass(toDoList, description, index);
	}
	else if(toDoList[index].returntype() == "timed"){
		editTimedClass(toDoList, description, index);
	}
}

void logic::editFloatClass(vector<task> & toDoList, string description, int index){
	string PartToChange;
	size_t pos = description.find("-name");
	PartToChange = description.substr(pos+6);
	toDoList[index].edittext(PartToChange);
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
}

void logic::editDeadlineClass(vector<task> & toDoList, string description, int index){
	string PartTochange, temp;
	char c;
	int e_date, e_month, e_year, e_time;

	size_t foundname = description.find("-name");
	size_t founddue = description.find("-due");
	if(foundname!=std::string::npos){
		PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
	} else if(founddue!=std::string::npos){
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
	printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
}

void logic::editTimedClass(vector<task> & toDoList, string description, int index){
	string PartTochange, temp;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	char c;

	size_t foundname = description.find("-name");
	size_t foundstart = description.find("-start");
	size_t foundend = description.find("-end");
	if(foundname!=std::string::npos){
		PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
	}
	else{ 
		if(foundstart!=std::string::npos){
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
		if(foundend!=std::string::npos){
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
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
}

void logic::deleteItem(const int index, vector<task> &toDoList) {
		if (system("CLS")) system("clear");
		printMessage(MESSAGE_ITEM_DELETED_SUCCESSFULLY);
		toDoList.erase(toDoList.begin()+index);
}

void logic::clearAll(vector<task> &toDoList) {
	toDoList.clear();
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY);
}

void logic::pushback(vector<task>& toDoList, vector<task>& tempVec, int index){
	task task_;
	task_ = toDoList[index];
	task_.inserttempnum(index);
	tempVec.push_back(task_);
}

void logic::markcompleted(int index, vector<task> &toDoList){
	task temp;
	int size = toDoList.size();

	toDoList[index].editDone(true);
	if (system("CLS")) system("clear");
	printMessage(toDoList[index].returntext(), "completed");
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


void logic::sortdates(vector<task> &toDoList){
	unsigned int i, j;
	task temp;

	for(i = 0; i<toDoList.size(); ++i)
		toDoList[i].edittemp((toDoList[i].returnendyear()*10000)+(toDoList[i].returnendmonth()*100)+(toDoList[i].returnenddate()));

    for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(toDoList[j-1].returntemp() > toDoList[j].returntemp()){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}

void logic::sortEndTime(vector<task> &toDoList){
	task temp;
	unsigned int i , j;

    for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(toDoList[j-1].returnendtime() > toDoList[j].returnendtime()){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}



void logic::searchTask(vector<task> &toDoList, vector<task> &tempVec, string description) {
	tempVec.clear();

	if(!isCheckSearchStringDigit(description)) {
		searchWord(toDoList,description,tempVec);
	} else {
		searchDigit(toDoList,description,tempVec);
	}

	if( tempVec.size() == 0) {
		printMessage(MESSAGE_SEARCH_FAILED);
	} else {
	    cout << displayAll(tempVec);
	}
}

void logic::searchWord(vector<task> &toDoList, string description, vector<task> &tempVec) {
	for(int i = 0; i < toDoList.size(); ++i) {
		//searched word is not a digit-->can only be found in task name
			unsigned int t = -1;
			t = (toDoList[i].returntext()).find(description);
			if(t != -1) {
				pushback(toDoList, tempVec, i);
			}
	}
}

void logic::searchDigit(vector<task> &toDoList, string description, vector<task> &tempVec) {
	for(int i = 0; i < toDoList.size(); ++i) { // searched word is a pure digit-->can only be found in time/date/month/year
			unsigned int t = -1;
			t = (toDoList[i].returntext()).find(description);
			if(t != -1) {
				pushback(toDoList, tempVec, i);
			}
			int convertedInt = convertNumStringToInt(description);
			if(toDoList[i].returnstarttime() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnendtime() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if(toDoList[i].returnstartdate() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnenddate() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnstartmonth() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnendmonth() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnstartyear() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else if (toDoList[i].returnendyear() == convertedInt) {
				pushback(toDoList, tempVec, i);
			} else {}
	}
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

void logic::displayToday(vector<task> &tempVec, vector<task> &toDoList,int size) {
	int day, month, year;
	parser parse;
	for(int i=0; i<size; i++) {
			day = toDoList[i].returnenddate();
			month = toDoList[i].returnendmonth();
			year = toDoList[i].returnendyear();
			if(day == parse.getSystemDay() && (month == parse.getSystemMonth())&& (year == parse.getSystemYear())){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayTomorrow(vector<task> &tempVec, vector<task> &toDoList,int size) {
	int day, month, year;
	parser parse;
	for(int i=0; i<size; i++){
			day = toDoList[i].returnenddate();
			month = toDoList[i].returnendmonth();
			year = toDoList[i].returnendyear();
			if((day == (parse.getSystemDay())+1) && (month == parse.getSystemMonth())&& (year == parse.getSystemYear())){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayNotDone(int size,vector<task> &toDoList,vector<task> &tempVec) {
		for(int i=0; i<size; i++){
			bool status = toDoList[i].returnstatus();
			if(status == false){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayDone(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
			bool status = toDoList[i].returnstatus();
			if(status == true){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayFloat(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type == "float"){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayDeadline(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type =="deadline"){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayTimed(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type =="timed"){
				pushback(toDoList, tempVec, i);
			}
		}
}

void logic::displayEverything(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++) {
			pushback(toDoList, tempVec, i);
	}
}

void logic::display(vector<task> &toDoList, vector<task> &tempVec, string fileName, string description){
	int size, day, month, year;
	int count = 0;
	size = toDoList.size();

	if(description == "today"){
		count++;
		displayToday(tempVec, toDoList, size);
	}
	else if(description == "tomorrow" || description == "tmr" || description == "tomor"){
		count++;
		displayTomorrow(tempVec, toDoList, size);
	}
	else if(description == "not done"){
		count++;
		displayNotDone(size,toDoList,tempVec);
	}
	else if(description == "done"){
		count++;
		displayDone(size,toDoList,tempVec);
	}
	else if(description == "float"){
		count++;
		displayFloat(size,toDoList,tempVec);
	}
	else if(description == "deadline"){
		count++;
		displayDeadline(size,toDoList,tempVec);
	}
	else if(description == "timed"){
		count++;
		displayTimed(size,toDoList,tempVec);
	} 
	else if(description == "all"){
		count++;
		displayEverything(size,toDoList,tempVec);
	}

	if(count == 0) {
		printMessage(MESSAGE_INVALID_DISPLAY_COMMAND);
	} else {
		cout << displayAll(tempVec);
	}
}

//check whether input date is valid function starts here
bool logic::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool logic::isValidDate(unsigned short day,unsigned short month,unsigned short year){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12 || year > 2030)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}

bool logic::isValidTime(int time) {
	if((time>=0)&&(time<=2400)) {
		return 1;
	} else {
		return 0;
	}
}

bool logic::checkIsDateOverdue(int day, int month, int year,int timing) {
	bool result = true;
	parser p;
	int sysDay, sysMonth, sysYear, sysHr, sysMin, sysTime;
	
	sysDay = p.getSystemDay();
	sysMonth = p.getSystemMonth();
	sysYear = p.getSystemYear();
	sysHr = p.getSystemHour();
	sysMin = p.getSystemMinute();
	sysTime = sysHr * 100 + sysMin;

	if(year < sysYear) {
		return false;
	} else if(year == sysYear && month < sysMonth) {
		return  false;
	} else if(year == sysYear && month == sysMonth && day < sysDay) {
		return false;
	} else if(year == sysYear && month == sysMonth && day == sysDay && timing < sysTime) {
		return false;
	}
	return result;
}
//check whether input date is valid ends here


void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage( string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

bool logic::checkIfStartTimeIsEarlierThanEndTime (int s_day,int s_month,int s_year,int s_time,int e_day,int e_month,int e_year,int e_time) {
	bool result = true;
	
	if(checkIsSameDate(e_day,s_day) && checkIsSameMonth(e_month,s_month) && checkIsSameYear(e_year,s_year)) {
		if(s_time >= e_time) {
			return result;
		} else {
			return !result;
		}
	}
}

bool logic::checkIsSameDate(int e_day,int s_day) {
	return (e_day == s_day);
}
bool logic::checkIsSameMonth(int e_month,int s_month) {
	return (e_month == s_month);
}
bool logic::checkIsSameYear(int e_year,int s_year) {
	return (e_year == s_year);
}