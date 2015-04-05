#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;
//Constants
const string DELIMITERS = " \n\t\v";
const string ERROR_MISSING_DESCRIPTION = "no description entered";
const string ERROR_INVALID_COMMAND = "invalid command";
const string ERROR_MISSING_INDEX="missing index";

class parser{
public:
	bool isValidCommand(const string command, const string description);
	void trimString(string &description);
	int convertStringToIntegerIndex(const string description);
	int parser::convertStringToInteger(const string description);
	string checktype(string description);
	
	void splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time);
	void splitinputTimed(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time);

	bool isNumerical(string month);
	int convertAlphabetMonthToInteger (string month);

	void printMessage(const string message);
	bool containShortForm(string description);
	string shortForm(string description);


};

