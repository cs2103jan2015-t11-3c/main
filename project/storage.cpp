#include "storage.h"
#include <vector>
#include <sstream>
#include <fstream> 
#include <iostream>
#include <stdlib.h> 

storage::storage(void)
{
	_filePath="";
	_fileName="SaveFile";
}

storage::~storage(void)
{
}

void storage::setFileName(string newFileName) {
	_fileName = newFileName;
}

void storage::setFilePath(string newFilePath) {
	_filePath = newFilePath;
}

string storage::getCurrentFileName() {
	return _fileName;
}

string storage::getCurrentFilePath() {
	return _filePath;
}

string storage::toString(vector<task> &toDoList) {
	ostringstream oss;
	
	if(toDoList.size()>0) {

		for(int i=0;i<toDoList.size();i++)
			oss << i+1 << ". " <<toDoList[i].returntext() <<endl
			<< "Start: "<<toDoList[i]. returnstartdate()<<"/"<<" "<<toDoList[i].returnstartmonth()<<"/"<<" "<<toDoList[i].returnstartyear()<<"\t"<<toDoList[i].returnstarttime()<<endl
			<< "End: "<< toDoList[i].returnenddate()<<"/"<<" "<<toDoList[i].returnendmonth()<<"/"<<" "<<toDoList[i].returnendyear()<<"\t "<<toDoList[i].returnendtime()<<endl
			<< "Type: "<<toDoList[i].returntype()<<endl
			<<"Completed: "<<toDoList[i].returnstatus()<<endl<<endl;
	}

	return oss.str();
}


void storage::saveToSaveFile(const string fileName,vector<task> &toDoList) {
	fstream textFile;
	
	textFile.open(getFileNameAndDirectory(_filePath,fileName), fstream::out);
	textFile << toString(toDoList);
	textFile.close();
	
}

 vector<task> storage::readToDoListFromTextFile(string fileName) {
	fstream textFile;
	string input;
	textFile.open(fileName.c_str());
	
	//Remove the index of each line, eg: remove "1)" from "1) Some List Entry"
	//Adds the rest of the line to the to-do list after removing leading and following whitespaces
	 while(getline(textFile,input)) {
		size_t pos = input.find('.');
		input = input.substr(pos+2);
		
		string text;
		int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
		task datainput;

		task i;
		bool status;
		char buffer;
	    string type;
		string description;
		string extra;

		
		i.edittext(input);
		getline(textFile,description);
		istringstream start(description);
		int sdate,smonth,syear,stime,edate,emonth,eyear,etime;
		start>>extra>>sdate>>buffer>>smonth>>buffer>>syear>>stime;

		getline(textFile,description);
		istringstream end(description);
		end>>extra>>edate>>buffer>>emonth>>buffer>>eyear>>etime;
		
		i.edits_date(sdate);
		i.edits_month(smonth);
		i.edits_year(syear);
		i.edits_time(stime);
		i.edite_date(edate);
		i.edite_month(emonth);
		i.edite_year(eyear);
		i.edite_time(etime);
    
		
		getline(textFile,description);
		istringstream Type(description);
		Type>>extra>>type;
		i.editType(type);

		getline(textFile,description);
		istringstream in(description);
		in>>extra>>status;
		i.editDone(status);
		

	    getline(textFile,description);
		_toDoList.push_back(i);

	}
	textFile.close();
	return _toDoList;
}

 bool storage::changeDirectory(string newFilePath, string fileName,vector<task> &toDoList){
	 
	string newFileNameAndDirectory = newFilePath + "\\" + fileName;

	if(fileExists(newFileNameAndDirectory)) {
		return false;
	}
	 setFilePath(newFilePath);
	// string URL=newFilePath +  fileName;
	fstream outFile;
	outFile.open(getFileNameAndDirectory(newFilePath,fileName), fstream::out | fstream::app);
	
	//outFile.open(URL.c_str(),fstream::out);
	outFile<< toString(toDoList);
	outFile.close();

	system("del SaveFile");
	
	return true;
}

 bool storage::changeFileName(string newfileName,vector<task> &toDoList){
	 
    string newFileNameAndDirectory = _filePath + "\\" + newfileName;
	if(fileExists(newFileNameAndDirectory)) {
		return false;
	}
	 setFileName(newFileNameAndDirectory);
	fstream outFile;
	outFile.open(getFileNameAndDirectory(_filePath,newfileName), fstream::out | fstream::app);
	
	outFile<< toString(toDoList);
	outFile.close();

	system("del SaveFile");
	
	return true;
}
 bool storage::fileExists(const string& fileName) {
	return (ifstream(fileName.c_str()));
}

 string storage::getFileNameAndDirectory(string filePath, string fileName) {
	if(filePath == "") {
		return fileName;
	} else {
		return (filePath + "\\" + fileName);
	}
}


bool storage::isFloatDuplicated(task newTask, vector<task> &toDoList) {
	for (int i=1;i<=toDoList.size();i++) {
		if(( toDoList[i-1].returntype() == "float")&&(newTask.returntext()==toDoList[i-1].returntext()))
				return true;
		}
	return false;
}


bool storage::isDeadlineDuplicated(task newTask, vector<task> &toDoList) {

	for (int i=1;i<=toDoList.size();i++) {
		if(toDoList[i-1].returntype() == "deadline"){
		if ((newTask.returntext())==(toDoList[i-1].returntext())) {
			if ((newTask.returnendyear()==toDoList[i-1].returnendyear())&&(newTask.returnendmonth()== toDoList[i-1].returnendmonth())
				&&(newTask.returnenddate()==toDoList[i-1].returnenddate())&&(newTask.returnendtime()==toDoList[i-1].returnendtime()))
				return true;
		}
		}
	}
	return false;
}


bool storage:: isTimeClashed(task newTask, vector<task> &toDoList){
	for (int i=1;i<=toDoList.size();i++) {
		if ((newTask.returnendyear())==(toDoList[i-1].returnendyear())&&(newTask.returnendmonth())==(toDoList[i-1].returnendmonth())
				&&(newTask.returnenddate())==(toDoList[i-1].returnenddate())
				&&(newTask.returnstartyear())==(toDoList[i-1].returnstartyear())&&(newTask.returnstartmonth())==(toDoList[i-1].returnstartmonth())
				&&(newTask.returnstartdate())==(toDoList[i-1].returnstartdate()))
			if ((newTask.returnendtime())>=(toDoList[i-1].returnstarttime())
				&& (newTask.returnstarttime())<(toDoList[i-1].returnendtime())) 
				return true;
			}
		
	
	return false;
}