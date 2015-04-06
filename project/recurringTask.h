#pragma once
#include "Task.h"
#include "logic.h"
class recurringTask
{
private:
	string description;
	int s_time;
	int e_time;
public:
	recurringTask(void);
	recurringTask(string text, int stime ,int etime);
	~recurringTask(void);

	void AddRecurring(string recurType,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);

	void DailyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);
	void WeeklyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);
	void MonthlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);
	void YearlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);
	bool isValidforMoreDays(int month);
	void addRecDeadline( int e_date, int e_month, int e_year, vector<task> &toDoList);
	void addRecTimed(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList);

	int getNumDays(int month,int year);

	void addTodifferentType(string type, int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList);

	void ChangeWeekDeadline(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);
    void ChangeMonthDeadline(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList);


	void moveToNextMonth(int &date, int &month, int &year);
	void moveToNextYear(int &date, int &month, int &year);


	int recurPeriod();


};

