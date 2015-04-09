#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(parsertest)
	{
	public:
		
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



		TEST_METHOD(TestNoDescription)
		{
		    parser p;
			string testCommand = "add";
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

		TEST_METHOD(Testchecktype)
		{
		    parser p;
			string testString = p.checktype("add homework /by 1100 tmr");
			string expected ="deadline";
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

		TEST_METHOD(TesttrimString)
		{
		    parser p;
			string testString="   dec ";
			p.trimString(testString);
			string expected ="dec";
			Assert::AreEqual (testString, expected);
		
		}


	
	};
}