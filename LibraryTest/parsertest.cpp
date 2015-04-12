#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(parsertest)
	{
	public:
		
		TEST_METHOD(TestNoDescription)
		{
		    parser p;
			string testCommand = "add";
			string testDescription="";
			int expected = 0;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
		}

		TEST_METHOD(TestValidCommand)
		{
		    parser p;
			string testCommand = "add";
			string testDescription="shopping";
			int expected = 1;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
			int testDone=p.isValidCommand("clear",testDescription);
			Assert::AreEqual (expected,testDone);
		
		}

		TEST_METHOD(TestClearCommand)
		{
		    parser p;
			string testCommand = "clear";
			string testDescription="";
			int expected = 1;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
		}

		TEST_METHOD(TestEditCommand)
		{
		    parser p;
			string testCommand = "edit";
			string testDescription="1";
			int expected = 1;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
		}

		TEST_METHOD(TestDoneCommand)
		{
		    parser p;
			string testCommand = "done";
			string testDescription="";
			int expected = 0;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
		}

		TEST_METHOD(TestInValidCommand)
		{
		    parser p;
			string testCommand = "do";
			string testDescription="shopping";
			int expected = 0;
			int test=p.isValidCommand(testCommand,testDescription);
			Assert::AreEqual (expected,test);
		}

		TEST_METHOD(TestconvertAlphabetMonthToInteger)
		{
		    parser p;
			int testString = p.convertAlphabetMonthToInteger("dec");
			int expected = 12;
			Assert::AreEqual (testString, expected);
		
		}
		
		TEST_METHOD(TestconvertStringToIntegerIndex)
		{
		    parser p;
			int testString = p.convertStringToIntegerIndex("20");
			int expected = 19;
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(TestconvertStringToInteger)
		{
		    parser p;
			int testString = p.convertStringToInteger("20");
			int expected = 20;
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(Testchecktypefloat)
		{
		    parser p;
			string testString = p.checktype("add homework ");
			string expected ="float";
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(Testchecktypedeadline)
		{
		    parser p;
			string testString = p.checktype("add homework /by 1100 tmr");
			string expected ="deadline";
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(Testchecktypetimed)
		{
		    parser p;
			string testString = p.checktype("add homework /from 1100 tmr /to 1200 tmr");
			string expected ="timed";
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(TestnotNumerical)
		{
		    parser p;
			bool testString = p.isNumerical("feb");
			bool expected = false;
			Assert::AreEqual (testString, expected);		
		}

		TEST_METHOD(TestNumerical)
		{
		    parser p;
			bool testString = p.isNumerical("12");
			bool expected = true;
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(TestshortForm)
		{
		    parser p;
			string testString = p.shortForm("add meeting /by 1100 tmr");
			string expected = "tomorrow";
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(TestsplitinputDeadline)
		{
		    parser p;
			string description="meeting /by 1100 on 23/04/2015";
			string text;
			int e_date, e_month, e_year, e_time;
			p.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);	
			string Exptext="meeting";
			int Expe_date=23;
			int Expe_month=04;
			int Expe_year=2015;
			int Expe_time=1100;
			Assert::AreEqual (text,Exptext );
			Assert::AreEqual (e_date,Expe_date );
			Assert::AreEqual (e_month,Expe_month );
			Assert::AreEqual (e_year,Expe_year );
			Assert::AreEqual (e_time,Expe_time );
		
		}

		TEST_METHOD(TestsplitinputTimed)
		{
		    parser p;
			string description="meeting /from 1000 on 22/04/2015 /to 1100 on 23/05/2015";
			string text;
			int e_date, e_month, e_year, e_time,s_date, s_month, s_year, s_time;
			p.splitinputTimed(description, text,s_date,s_month,s_year,s_time, e_date, e_month, e_year, e_time);	
			string Exptext="meeting";
			int Exps_date=22;
			int Exps_month=04;
			int Exps_year=2015;
			int Exps_time=1000;
			int Expe_date=23;
			int Expe_month=05;
			int Expe_year=2015;
			int Expe_time=1100;
			Assert::AreEqual (text,Exptext );
			Assert::AreEqual (e_date,Expe_date );
			Assert::AreEqual (e_month,Expe_month );
			Assert::AreEqual (e_year,Expe_year );
			Assert::AreEqual (e_time,Expe_time );
			Assert::AreEqual (s_date,Exps_date );
			Assert::AreEqual (s_month,Exps_month );
			Assert::AreEqual (s_year,Exps_year );
			Assert::AreEqual (s_time,Exps_time );
		
		}

		TEST_METHOD(TesttrimString)
		{
		    parser p;
			string testString="   dec ";
			p.trimString(testString);
			string expected ="dec";
			Assert::AreEqual (testString, expected);
		
		}

		TEST_METHOD(testchecksearchstringdigit){
			string testone = "meeting", testtwo = "25", testthree = "14haha";
			parser parse;
			bool result;

			result = parse.isCheckSearchStringDigit(testone);
			Assert::AreEqual(false, result);

			result = parse.isCheckSearchStringDigit(testtwo);
			Assert::AreEqual(true, result);

			result = parse.isCheckSearchStringDigit(testthree);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testCovertNumtoString){
			string testone = "14", testtwo = "100";
			int result;
			parser parse;

			result = parse.convertNumStringToInt(testone);
			Assert::AreEqual(14, result);

			result = parse.convertNumStringToInt(testtwo);
			Assert::AreEqual(100, result);
		}

		TEST_METHOD(testLeapYear){
			int testone = 2016, testtwo = 2014;
			bool result;
			parser parse;

			result = parse.isleapyear(testone);
			Assert::AreEqual(true, result);
			
			result = parse.isleapyear(testtwo);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testValidDate){
			parser parse;
			bool result;

			result = parse.isValidDate(5, 11, 2014);
			Assert::AreEqual(true, result);

			result = parse.isValidDate(32, 13, 2014);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testCheckIsDateOverdue){
			logic function;
			bool result;
			parser parse;

			result = parse.checkIsDateOverdue(19, 12, 2016, 1400);
			Assert::AreEqual(true, result);

			result = parse.checkIsDateOverdue(1, 4, 2015, 1400);
			Assert::AreEqual(false, result);
		}


	
	};
}