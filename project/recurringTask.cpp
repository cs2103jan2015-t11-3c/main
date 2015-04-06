#include "recurringTask.h"

recurringTask::recurringTask(void )
{
}

recurringTask::recurringTask(string text, int stime ,int etime )
{    description=text;
	 s_time=stime;
	 e_time=etime;
}

recurringTask::~recurringTask(void)
{
}

void recurringTask::AddRecurring(string recurType,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	
	if(recurType=="daily")
		DailyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="weekly")
	    WeeklyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="monthly")
		MonthlyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="yearly")
		YearlyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	return;
}


void recurringTask::DailyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	int n=30;                                                                   //the default recurring period for daily task is set to be 30 days
	logic function;

	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
          addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		  e_date=e_date+1;
		  s_date=s_date+1;
		}
		else{                                                                //move to next month
			e_date=1;
			e_month++;
		    s_date=e_date;
			s_month=e_month;
		 if (function.isValidDate(e_date,e_month,e_year)){
              addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	    
		}
		 else{
			 e_year++;                                                         //move to next year
			 e_date=1;
			 e_month=1;
			 s_date=e_date;
			 s_month=e_month;
		     s_year=e_year;
			 if(function.isValidDate(e_date,e_month,e_year))
			  addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		 }
		     e_date=e_date+1;
			 s_date=e_date;		 
		}   }
	return;
}

void recurringTask::WeeklyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	int n=52;                           //default recurring period for weekly task is half year(26)weeks;
	logic function;
   
	for(int i=1;i<=n;i++){
		if(type=="deadline"){
		if (function.isValidDate(e_date,e_month,e_year)){
            addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);		 
		}
		else{
			ChangeWeekDeadline(e_date, e_month, e_year,s_date, s_month,s_year, type, toDoList);
		}
		  e_date=e_date+7;
		}
		if(type=="timed"){
		 if (function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
             addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);		
		}
		else{
			if (!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)){
			 moveToNextMonth(e_date, e_month, e_year);  //move to next month                             
			 moveToNextMonth(s_date, s_month, s_year);

			if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
			 addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			   
			}
			else{
				moveToNextYear(e_date, e_month, e_year);         //move to the next year
				moveToNextYear(s_date, s_month, s_year); 		
				if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
			
			}
			}
			else{
			if(!function.isValidDate(e_date,e_month,e_year)){
			     moveToNextMonth(e_date, e_month, e_year); 
			if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
			   addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			   
			}
			else{
		     	moveToNextYear(e_date, e_month, e_year);   
				if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		
				}
			}
			}

			if(!function.isValidDate(s_date,s_month,s_year)){
			 moveToNextMonth(s_date, s_month, s_year);
			if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
			   addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			    
			}
			else{
				moveToNextYear(s_date, s_month, s_year); 	
				if(function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(e_date,e_month,e_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		
				}
			}
		}

			}
		}  }     e_date=e_date+7;
		        s_date=s_date+7;
	
}        return;
}

void recurringTask::MonthlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	int n=12;                          //default recurring period is 12 month if user do not specify
	logic function;
    
	for(int i=1;i<=n;i++){
		if(type=="deadline"){
		if (function.isValidDate(e_date,e_month,e_year)){
            addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			 
		}
		else{
			ChangeMonthDeadline(e_date, e_month, e_year,s_date, s_month,s_year, type, toDoList);
		}
		e_month++;
		}

		if(type=="timed"){
		   if (function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year)){
            addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	 
	    	}
		
		else if(!isValidforMoreDays(e_month)||!isValidforMoreDays(s_month)){                                    //same year, if the date is 31st of the month, make it the last day of each month 
			 if(s_date==31&&function.isValidDate(s_date-1,s_month,s_year)){
				if(s_date==e_date&&s_month==e_month)
		        addTodifferentType(type, e_date-1, e_month, e_year,s_date-1, s_month,s_year,  toDoList);
				else
			    if (function.isValidDate(e_date,e_month,e_year)&&function.isValidDate(s_date-1,s_month,s_year))
			    addTodifferentType(type, e_date, e_month, e_year,s_date-1, s_month,s_year,  toDoList);
			   }
			if(e_date==31&&function.isValidDate(e_date-1,e_month,e_year)&&s_month!=2){
			    if (function.isValidDate(e_date-1,e_month,e_year)&&function.isValidDate(s_date,s_month,s_year))
			    addTodifferentType(type, e_date-1, e_month, e_year,s_date, s_month,s_year,  toDoList);
			   }
			    else if((e_date==31||e_date==30||s_date==31||s_date==30)&&(e_month==2||s_month==2)){                       //special case for Feburary
				if((s_date==31||s_date==30)&&s_month==2){
				if(function.isleapyear(s_year)){
				 if(function.isValidDate(29,s_month,s_year)&&function.isValidDate(e_date,e_month,e_year))
			      addTodifferentType(type, e_date, e_month, e_year,29, s_month,s_year,  toDoList);
				}
				else{   
				if(function.isValidDate(28,s_month,s_year)&&function.isValidDate(e_date,e_month,e_year))
			     addTodifferentType(type, e_date, e_month, e_year,28, s_month,s_year,  toDoList);
				}
				}


				if((e_date==31||e_date==30)&&e_month==2){
				if(function.isleapyear(e_year)){
				 if(function.isValidDate(s_date,s_month,s_year)&&function.isValidDate(29,e_month,e_year))
			      addTodifferentType(type, 29, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				else{   
				if(function.isValidDate(s_date,s_month,s_year)&&function.isValidDate(28,e_month,e_year))
			     addTodifferentType(type, 28, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				}

				if((e_month==2)&&s_month==2){
				if(function.isleapyear(e_year)){
				 if(function.isValidDate(29,s_month,s_year)&&function.isValidDate(29,e_month,e_year))
			      addTodifferentType(type, 29, e_month, e_year,29, s_month,s_year,  toDoList);
				}
				else{   
				if(function.isValidDate(s_date,s_month,s_year)&&function.isValidDate(28,e_month,e_year))
			     addTodifferentType(type, 28, e_month, e_year,28, s_month,s_year,  toDoList);
				}
				}


				}
			}
		
			if(e_month+1>12){
			e_month=e_month%12;
			e_year++;
			}
			
			if(s_month+1>12){
			s_month=s_month%12;
			s_year++;
			}
		
		
			
		    e_month++;
		    s_month++;
		}}
			return;
}
	
void recurringTask::YearlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
    int n=5;
	logic function;

	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
           addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

		  e_year=e_year+1;
		  s_year++;
		}
	}
		return;
}

bool recurringTask::isValidforMoreDays(int month){
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
		return true;
	}
	else{
		return false;
	}
}

int recurringTask::getNumDays(int month,int year){
	logic function;
	int LMonth[7]={1,3,5,7,8,10,12};
	int SMonth[]={4,6,9,11};
	for(int i=0;i<7;i++){
		if(LMonth[i]==month)
			return 31;
		else if(SMonth[i]==month)
			return 30;
	}
	
	if(month==2&&function.isleapyear(year))
		return 29;
	else
		return 28;
}

void recurringTask::addRecDeadline(int e_date, int e_month, int e_year, vector<task> &toDoList){
	 task datainput(description);
	 datainput.addItemtypetwo(e_date, e_month, e_year, e_time);
	
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addRecTimed(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList){
	 task datainput(description);
	 datainput.addItemtypethree( s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addTodifferentType(string type, int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList){
	if(type=="deadline")
			addRecDeadline( e_date, e_month, e_year, toDoList);
	if(type=="timed")
			addRecTimed(e_date,e_month, e_year, s_date, s_month, s_year, toDoList);
	return;
}

int recurringTask::recurPeriod(){
	cout<<"Enter Recurring period: "<<endl;
	int n;
	cin>>n;
	return n;
}

void recurringTask::moveToNextMonth(int &date, int &month, int &year){
	date=date%getNumDays(month,year);                      
	month++;             
}

void recurringTask::moveToNextYear(int &date, int &month, int &year){
	   year++;                                           //move to the next year
	   month=1;
	   date%=getNumDays(month,year); 
}


void recurringTask::ChangeWeekDeadline(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	logic function;
	       moveToNextMonth(e_date, e_month, e_year);                                        
			if(function.isValidDate(e_date,e_month,e_year)){
			   addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

			}
			else{
			    moveToNextYear(e_date, e_month, e_year); 
				if(function.isValidDate(e_date,e_month,e_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);      
				}
			}
			
}


void recurringTask::ChangeMonthDeadline(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	logic function;
	if(!isValidforMoreDays(e_month)){                                    //same year, if the date is 31st of the month, make it the last day of each month 
			if(e_date==31&&function.isValidDate(e_date-1,e_month,e_year)){
		        addTodifferentType(type, e_date-1, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
			else if((e_date==31||e_date==30)&&e_month==2){                       //special case for Feburary
				if(function.isleapyear(e_year)){
				  addTodifferentType(type, 29, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				else{
			     addTodifferentType(type, 28, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
			}
		}
	else{
		    moveToNextYear(e_date, e_month, e_year); 
			if(function.isValidDate(e_date,e_month,e_year)){
		     addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
	}
			
}


