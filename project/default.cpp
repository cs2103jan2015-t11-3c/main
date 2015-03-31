#include "default.h"

void defaultclass::defaultexecuteCommand(string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentundomemory) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
    logic function;
	task datainput;
	storage store;
	parser parse;
	undo undofunction;
	searchclass searchfunction;
	defaultclass defaultmemory;

	defaultmemory.updatedefaultmemory(toDoList);
	
	while(command!="exit"){
		parse.trimString(description);

		if(parse.isValidCommand(command, description)){
			if(!parse.isValidCommand(command, description))
				return;
			else if(command=="add" ||command =="+") {
				if(parse.checktype(description) == 1){
					parse.splitinputtypeone(description, text);
					datainput.addItemtypeone(text);
					if(!store.isFloatDuplicated(datainput, toDoList))
					       toDoList.push_back(datainput);
					else
						function.printMessage("float task exist already");
				}
				else if(parse.checktype(description) == 2){
					parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
					datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
					if(!store.isDeadlineDuplicated(datainput, toDoList)){
						if(function.isValidDate(e_date,e_month,e_year)&&function.isValidTime(e_time)&&function.isValidTime(e_time)) {
					       toDoList.push_back(datainput);
						} if(!function.isValidDate(e_date,e_month,e_year)) {
							function.printMessage("invalid input date, try again");
					} if(!function.isValidTime(e_time)) {
						function.printMessage("invalid input timing, try again");
						} 
					}else {
							function.printMessage("deadline task exist already");
					}
				}
				else if(parse.checktype(description) == 3){
					parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					if(!store.isTimeClashed(datainput, toDoList)){
						if(!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)) {
							cout << "inValid Start and End Dates, try again" << endl;
						}else if(!function.isValidDate(s_date,s_month,s_year)) {
							cout << "inValid Start Date, try again" << endl;
						}else if(!function.isValidDate(e_date,e_month,e_year)) {
							cout << "inValid End Date, try again" << endl;
						}else if(!function.isValidTime(s_time)) {
							cout << "invalid Start Timing, try again" << endl;
						} else if(!function.isValidTime(e_time)) {
							cout << "invalid End Timing, try again" << endl;
						} else{
							toDoList.push_back(datainput);
						} 
					} else
						function.printMessage("timed slot clashes");
				}
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="delete"||command=="-"||command=="remove") {

				function.deleteItem(checkfororiginalindex(description, defaultmemory), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="display") {
				cout << function.displayAll(toDoList);
			}
			else if(command=="clear") {
				function.clearAll(toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command == "edit") {
				function.editTask(checkfororiginalindex(description, defaultmemory),description, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="exit") {
				store.saveToSaveFile(fileName,toDoList);
				return;
			}
			else if(command == "done") {
				function.markcompleted(checkfororiginalindex(description, defaultmemory), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
			}
			else if(command == "undo"){
				currentundomemory = undomemory[undomemory.size()-2];
				toDoList = currentundomemory.returnmemory();
				undomemory.pop_back();
			}
			else if(command == "search") {
				return;
			}
			else if(command == "default") {
				showDefaultTaskList(toDoList);
			}

		}
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
	}

}
int defaultclass::checkfororiginalindex(string description, defaultclass defaultmemory){
	string temp;
	int index, originindex;

	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"){
		originindex = defaultmemory.floatVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "deadline"){
	    originindex = defaultmemory.deadlineVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "timed"){
		originindex = defaultmemory.timedVec[index].returntempnum();
	    return originindex;
	}
	else{
	return 0;}
}

void defaultclass::updatedefaultmemory(vector<task> &toDoList){
	vector<task> tempVec, floatVec_, deadlineVec_, timedVec_;
	task temp;
	int index, i=0, j=0, k=0;

	floatVec.clear();
	deadlineVec.clear();
	timedVec.clear();

	for(index = 0; index != toDoList.size(); ++index)
		tempVec.push_back(toDoList[index]);

	for(index = 0; index != tempVec.size(); ++index){
		if(tempVec[index].returntype() == 1){
			floatVec_.push_back(tempVec[index]);
			floatVec_[i].inserttempnum(index);
			i++;
		}
		else if(tempVec[index].returntype() == 2){
			deadlineVec_.push_back(tempVec[index]);
			deadlineVec_[j].inserttempnum(index);
			j++;
		}
		else {
			timedVec_.push_back(tempVec[index]);
			timedVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
	timedVec = timedVec_;
	deadlineVec = deadlineVec_;
}


void defaultclass::showDefaultTaskList(vector<task> &toDoList) {
	int index, i=0, j=0, k=0;
	logic function;
	vector<task> tempVec;	
	defaultclass defaultmemory;

	defaultmemory.updatedefaultmemory(toDoList);
	//*************************(1) float task (1)****************************************************************************
	function.sorttext(defaultmemory.floatVec);
	
	cout << "Floating tasks:" << endl;
	for(index = 0; index != defaultmemory.floatVec.size(); ++index)
		cout << defaultmemory.floatVec[index].displaytypeone(index);


	//*************************(2) deadline task (2)****************************************************************************
    function.sortdates(defaultmemory.deadlineVec);
	function.sorttime(defaultmemory.deadlineVec);

	cout << endl << endl << "Deadline tasks:" << endl;
	for(index = 0; index != defaultmemory.deadlineVec.size(); ++index) 
		cout << defaultmemory.deadlineVec[index].displaytypetwo(index);


	//*************************(3) timed task (3)****************************************************************************
	function.sortdates(defaultmemory.timedVec);
	function.sorttime(defaultmemory.timedVec);
	
	cout << endl << endl <<  "Timed tasks:" << endl;
	for(index = 0; index != defaultmemory.timedVec.size(); ++index)
	    cout << defaultmemory.timedVec[index].displaytypethree(index);

	cout << endl <<"**********************************************************************" << endl;
	
}