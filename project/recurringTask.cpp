#include "recurringTask.h"


//@author: A0119322N

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

void recurringTask::AddRecurring(int n,string recurType,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	try{
	if(recurType=="daily")
		DailyRec(n,e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="weekly")
	    WeeklyRec(n,e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="monthly")
		MonthlyRec(n,e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="yearly")
		YearlyRec(n,e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	}
	catch(const string ERROR_MESSAGE){
		logic function;
		function.printMessage(ERROR_MESSAGE);
	}
	return;
}


void recurringTask::DailyRec(int n, int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
                                                         
	logic function;
	parser parse;

	if(n==0){
		n=30;   //the default recurring period for daily task is set to be 30 days
	}

	for(int i=1;i<=n;i++){
		if(type=="timed"){
			if(!DayRecValid(e_date,e_month,e_year,s_date,s_month,s_year)){    //to check wether the recurring period is within 1 day
				return;
			}
		}
		if (parse.isValidDate(e_date,e_month,e_year)){
          addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		  e_date++;
		  s_date++;
		}
		else{                                                                //move to next month
			e_date=1;
			e_month++;
		    s_date=e_date;
			s_month=e_month;
		 if (parse.isValidDate(e_date,e_month,e_year)){
              addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	    
		}
		 else{
			 e_year++;                                                         //move to next year
			 e_date=1;
			 e_month=1;
			 s_date=e_date;
			 s_month=e_month;
		     s_year=e_year;
			 if(parse.isValidDate(e_date,e_month,e_year))
			  addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		 }
		     e_date=e_date+1;
			 s_date=e_date;		 
		}   }
	return;
}

void recurringTask::WeeklyRec(int n,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	logic function;                         
	parser parse;

	if(n==0){
		n=52;                      //default recurring period for weekly task is half year(26)weeks;
	}
	for(int i=1;i<=n;i++){
		if(type=="deadline"){
		if (parse.isValidDate(e_date,e_month,e_year)){
           addRecDeadline( e_date,  e_month,  e_year, toDoList);		 
		}
		else{
			ChangeWeekDeadline(e_date, e_month, e_year,s_date, s_month,s_year, type, toDoList);
		}
		}
		if(type=="timed"){
		 if(!WeekRecValid(e_date,e_month,e_year,s_date,s_month,s_year)){                   //to check wether the recurring period is within 1 week
				return;
		 }
		 if (parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
             addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);		
		}
		else{
			if (!parse.isValidDate(e_date,e_month,e_year)&&!parse.isValidDate(s_date,s_month,s_year)){    //if both start and end date are not valid
			 moveToNextMonth(e_date, e_month, e_year);  //move to next month                             
			 moveToNextMonth(s_date, s_month, s_year);

			if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
			  addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
			   
			}
			else{
				moveToNextYear(e_date, e_month, e_year);         //move to the next year
				moveToNextYear(s_date, s_month, s_year); 		
				if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
				    addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
				}
			
			}
			}
			else{
			if(!parse.isValidDate(e_date,e_month,e_year)){                 //if only end date is not valid
			     moveToNextMonth(e_date, e_month, e_year); 
			if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
			    addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
			   
			}
			else{
		     	moveToNextYear(e_date, e_month, e_year);   
				if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
				    addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
		
				}
			}
			}

			if(!parse.isValidDate(s_date,s_month,s_year)){
			 moveToNextMonth(s_date, s_month, s_year);
			if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
			   addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
			    
			}
			else{
				moveToNextYear(s_date, s_month, s_year); 	
				if(parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(e_date,e_month,e_year)){
				    addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);	
		
				}
			}
		}

		}
	}
	}   
		e_date=e_date+7;
		s_date=s_date+7;
	
}        return;
}

void recurringTask::MonthlyRec(int n,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){	
	logic function;
	parser parse;
    if(n==0){
      n=12;                          //default recurring period is 12 month if user do not specify
    }
	
	for(int i=1;i<=n;i++){
		if(type=="deadline"){
		if (parse.isValidDate(e_date,e_month,e_year)){
             addRecDeadline( e_date,  e_month,  e_year, toDoList);			
		}
		else{
			ChangeMonthDeadline(e_date, e_month, e_year,s_date, s_month,s_year, type, toDoList);
		}
		 e_month++;
		}

		if(type=="timed"){                                                          //to check wether the recurring period is within 1 Month
			if(!MonthRecValid(e_date,e_month,e_year,s_date,s_month,s_year)){
				return;
			}

		   if (parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year)){
            addRecTimed( e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);		 
	    	}
		
		else if(!isValidforMoreDays(e_month)||!isValidforMoreDays(s_month)){                                    //same year, if the date is 31st of the month, make it the last day of each month 
			 if(s_date==31&&parse.isValidDate(s_date-1,s_month,s_year)){
				if(s_date==e_date&&s_month==e_month)                                                        
		         addRecTimed( e_date-1, e_month, e_year,s_date-1, s_month,s_year,  toDoList);	
				else if (parse.isValidDate(e_date,e_month,e_year)&&parse.isValidDate(s_date-1,s_month,s_year))
			     addRecTimed( e_date, e_month, e_year,s_date-1, s_month,s_year,  toDoList);	
			   }
			if(e_date==31&&parse.isValidDate(e_date-1,e_month,e_year)&&s_month!=2){                               
			    if (parse.isValidDate(e_date-1,e_month,e_year)&&parse.isValidDate(s_date,s_month,s_year))
			     addRecTimed( e_date-1, e_month, e_year,s_date, s_month,s_year,  toDoList);	
			   }
			    else if((e_date==31||e_date==30||s_date==31||s_date==30)&&(e_month==2||s_month==2)){                       //special case for Feburary
				if((s_date==31||s_date==30)&&s_month==2){
				if(parse.isleapyear(s_year)){
				 if(parse.isValidDate(29,s_month,s_year)&&parse.isValidDate(e_date,e_month,e_year))
			       addRecTimed(e_date, e_month, e_year,29, s_month,s_year,  toDoList);
				}
				else{   
				if(parse.isValidDate(28,s_month,s_year)&&parse.isValidDate(e_date,e_month,e_year))
			     addRecTimed( e_date, e_month, e_year,28, s_month,s_year,  toDoList);
				}
				}


				if((e_date==31||e_date==30)&&e_month==2){                                              
				if(parse.isleapyear(e_year)){                                                          //if it is feb of a leap year, marke the end date for the task to be 29
				 if(parse.isValidDate(s_date,s_month,s_year)&&parse.isValidDate(29,e_month,e_year))
			       addRecTimed(29, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				else{   
				if(parse.isValidDate(s_date,s_month,s_year)&&parse.isValidDate(28,e_month,e_year))     //if it is feb of a normal year, marke the end date for the task to be 28  
			      addRecTimed( 28, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				}

				if((e_month==2)&&s_month==2){
				if(parse.isleapyear(e_year)){
				 if(parse.isValidDate(29,s_month,s_year)&&parse.isValidDate(29,e_month,e_year))
			       addRecTimed( 29, e_month, e_year,29, s_month,s_year,  toDoList);
				}
				else{   
				if(parse.isValidDate(s_date,s_month,s_year)&&parse.isValidDate(28,e_month,e_year))
			      addRecTimed( 28, e_month, e_year,28, s_month,s_year,  toDoList);
				}
			}}}
		
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
	
void recurringTask::YearlyRec(int n,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	logic function;
	parser parse;
	 if(n==0){
		  n=5;
   }

	for(int i=1;i<=n;i++){
		if (parse.isValidDate(e_date,e_month,e_year)){
           addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		  e_year=e_year+1;
		  s_year++;
		}
	}
		return;
}

//to check wethere the month contain 31 days, reutrns true if it has 31 days
bool recurringTask::isValidforMoreDays(int month){
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
		return true;
	}
	else{
		return false;
	}
}

//get number of days in each month
int recurringTask::getNumDays(int month,int year){
	logic function;
	parser parse;

	int LMonth[7]={1,3,5,7,8,10,12};
	int SMonth[]={4,6,9,11};
	for(int i=0;i<7;i++){
		if(LMonth[i]==month)
			return 31;
		else if(SMonth[i]==month)
			return 30;
	}
	
	if(month==2&&parse.isleapyear(year))
		return 29;
	else
		return 28;
}

void recurringTask::addRecDeadline(int e_date, int e_month, int e_year, vector<task> &toDoList){
	 task datainput(description);
	 datainput.addDeadlineItem(e_date, e_month, e_year, e_time);
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addRecTimed(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList){
	 task datainput(description);
	 datainput.addTimedItem( s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
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


void recurringTask::moveToNextMonth(int &date, int &month, int &year){
	date=date%getNumDays(month,year);                      
	month++;             
}

void recurringTask::moveToNextYear(int &date, int &month, int &year){
	   year++;                                           //move to the next year
	   month=1;
	   date%=getNumDays(month,year); 
}


void recurringTask::ChangeWeekDeadline(int &e_date,int &e_month,int &e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){
	logic function;
	parser parse;
	       moveToNextMonth(e_date, e_month, e_year);                                        
			if(parse.isValidDate(e_date,e_month,e_year)){
			   addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

			}
			else{
			    moveToNextYear(e_date, e_month, e_year); 
				if(parse.isValidDate(e_date,e_month,e_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);      
				}
			}
			
}


void recurringTask::ChangeMonthDeadline(int &e_date,int &e_month,int &e_year,int s_date,int s_month,int s_year,string type,vector<task> &toDoList){

	logic function;
	parser parse;
	if(!isValidforMoreDays(e_month)){                                    //same year, if the date is 31st of the month, make it the last day of each month 
			if(e_date==31&&parse.isValidDate(e_date-1,e_month,e_year)){
		        addTodifferentType(type, e_date-1, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
			else if((e_date==31||e_date==30)&&e_month==2){                       //special case for Feburary
				if(parse.isleapyear(e_year)){
				  addTodifferentType(type, 29, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				else{
			     addTodifferentType(type, 28, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
			}
		}
	
		    moveToNextYear(e_date, e_month, e_year); 
			
			if(parse.isValidDate(e_date,e_month,e_year)){
		     addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
	
		
}

//to check wether the recurring period for daily recurring task is within 1 day
bool recurringTask::DayRecValid(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year){
	if(getDaysInterval(e_date,e_month,e_year,s_date,s_month,s_year)>=1){
		cout<<"Please enter the recurring task with time interval within 1 day"<<endl;
		return false;
	}

	return true;
}


//to check wether the recurring period for weekly recurring task is within 1 week
bool recurringTask::WeekRecValid(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year){
	if(getDaysInterval(e_date,e_month,e_year,s_date,s_month,s_year)>7){
		cout<<"Please enter the recurring task with time interval within 1 week"<<endl;
		return false;
	}

	return true;
}

//to check wether the recurring period for monthly recurring task is within 1 month
bool recurringTask::MonthRecValid(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year){
	if(getDaysInterval(e_date,e_month,e_year,s_date,s_month,s_year)>31){
		cout<<"Please enter the recurring task with time interval within 1 month"<<endl;
		return false;
	}

	return true;
}

//get the number of interval days between any 2 date
//precondition: the start date is before the end date
//postcondition: number of days interval is returned
int recurringTask::getDaysInterval(int eday,int emonth,int eyear,int sday, int smonth, int syear){
	logic function;
	parser parse;
   if(syear == eyear && smonth == emonth)
     {
          return  eday - sday;
    }else if(syear == eyear)
     {
         int startday,  endday;
		 
         startday = DayInYear(syear, smonth, sday);
         endday = DayInYear(eyear, emonth, eday);
         return endday-startday;
		}else{
          int d1,d2,d3;
         if(parse.isleapyear(syear))
             d1 = 366 - DayInYear(syear,smonth, sday);     //remaining days in that year
         else
             d1 = 365 - DayInYear(syear,smonth, sday);
         d2 = DayInYear(eyear,emonth,eday); 
		 
		  d3 = 0;
         for(int year = syear + 1; year < eyear; year++)
         {
             if(parse.isleapyear(year))
                 d3 += 366;
             else
                 d3 += 365;
         }
         return d1 + d2 + d3;

}
}


int recurringTask::DayInYear(int year, int month, int day){
    logic function;
	parser parse;
    int DAY[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(parse.isleapyear(year))
        DAY[1] = 29;
    for(int i=0; i<month - 1; ++i)
    {
        day += DAY[i];
    }
    return day;
}

