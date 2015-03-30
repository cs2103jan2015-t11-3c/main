#include "logic.h"


string logic::displayAll(vector<task> &toDoList) {
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




