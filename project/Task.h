#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class task{
private:
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	string type;
	int tempnum;
	int temp;
	bool complete;


public:
	task(void);
	~task(void);
	task(string task);
	void addFloatItem();
	void addDeadlineItem(int _e_date, int _e_month, int _e_year, int _e_time);
	void addTimedItem(int _s_date, int _s_month, int _s_year, int _s_time, 
		                  int _e_date, int _e_month, int _e_year, int _e_time);

	void edittext(string PartTochange);
	void edits_time(int PartTochange);
	void edits_date(int PartTochange);
	void edits_month(int PartTochange);
	void edits_year(int PartTochange);
	void edite_time(int PartTochange);
	void edite_date(int PartTochange);
	void edite_month(int PartTochange);
	void edite_year(int PartTochange);
	void editType(string PartTochange);
	void editDone(bool PartTochange);
	void inserttempnum(int index);
	void edittemp(int index);

	string returntype();
	bool returnstatus();
	string returntext();
	int returnenddate();
	int returnendmonth();
	int returnendyear();
	int returnendtime();
	int returnstartdate();
	int returnstartmonth();
	int returnstartyear();
	int returnstarttime();
	int returntempnum();
	int returntemp();

	string displayFloat(int index);
	string displayDeadline(int index);
	string displayTimed(int index);
	string displayDefaultTasks(int);
	string displayDefaultTasksWithTwoTimes(int);
	string displayDefaultTasksOver2days(int);

};



