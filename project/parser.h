#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;
//@author: A0119322N
//Constants
const string DELIMITERS = " \n\t\v";
const string ERROR_MISSING_DESCRIPTION = "no description entered";
const string ERROR_INVALID_COMMAND = "invalid command";
const string ERROR_MISSING_INDEX="missing index";
const string ERROR_MISSING_CHANGINGPART="using the correct format to change";
const string ERROR_MESSAGE_INVALIDMONTH="Invalid Month Entered!";
const string ERROR_MESSAGE_INVALIDEDITFORMAT="Invalid edit format entered!";
class parser{
public:
	bool isValidCommand(const string command, const string description);
	void trimString(string &description);
	int convertStringToIntegerIndex(const string description);
	int convertStringToInteger(const string description);
	string checktype(string description);
	
	//for add function
	void splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time);
	void splitinputTimed(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time);

	//recurreng command word
	int getStartPosition(string);
	int getEndPosition(string);
	int getRecurPeriod(string);
	string getRecurruingCommandWord(string);

	//to make sure month is in integer format
	bool isNumerical(string month);
	int convertAlphabetMonthToInteger (string month);
	int convertMonth(string month);

	//for today, tomorrow, flexibility
	bool containShortForm(string description);
	string shortForm(string description);
	void getInfo(string description, int &e_date, int &e_month, int &e_year);

	bool canFindPartoChange(string description);
	
	//for search function
	bool isCheckSearchStringDigit(string);
	int convertNumStringToInt(string);

	//check whether input date and time valid or not
	bool isleapyear(unsigned short);
	bool isValidDate(unsigned short,unsigned short,unsigned short);
	bool isValidTime(int);
	bool checkIsDateOverdue(int, int, int, int);

	//call for present time and date
	int getSystemDay();
	int getSystemMonth();
	int getSystemYear();
	int getSystemHour();
	int getSystemMinute();


};

