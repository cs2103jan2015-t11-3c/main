#pragma once
#include "Task.h"
#include "logic.h"

//@author: A0119322N
class recurringTask
{
private:
	string description;
	int s_time;
	int e_time;

public:
	recurringTask(void);
	recurringTask(string , int  ,int );
	~recurringTask(void);

	void AddRecurring(int ,string ,int ,int ,int ,int ,int ,int ,string ,vector<task> &);

	void DailyRec(int ,int ,int ,int ,int ,int ,int ,string ,vector<task> &);
	void WeeklyRec(int ,int ,int ,int ,int ,int ,int ,string ,vector<task> &);
	void MonthlyRec(int ,int ,int ,int ,int ,int ,int ,string ,vector<task> &);
	void YearlyRec(int ,int ,int ,int ,int ,int ,int ,string ,vector<task> &);

	bool isValidforMoreDays(int );
	void addRecDeadline( int , int , int , vector<task> &);
	void addRecTimed(int ,int ,int ,int ,int ,int ,vector<task> &);
	int getNumDays(int ,int );
	void addTodifferentType(string , int ,int ,int ,int ,int ,int ,vector<task> &);
    void ChangeWeekDeadline(int &,int &,int &,int ,int ,int ,string ,vector<task> &);
    void ChangeMonthDeadline(int &,int &,int &,int ,int ,int ,string ,vector<task> &);
	void moveToNextMonth(int &, int &, int &);
	void moveToNextYear(int &, int &, int &);
	int getDaysInterval(int ,int ,int ,int , int , int );
	int DayInYear(int , int , int );
	bool MonthRecValid(int ,int ,int ,int ,int ,int );
	bool WeekRecValid(int ,int ,int ,int ,int ,int );
	bool DayRecValid(int ,int ,int ,int ,int ,int );




};

