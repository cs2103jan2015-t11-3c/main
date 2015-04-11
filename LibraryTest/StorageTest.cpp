#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(StorageTestcpp)
	{
	public:
		
		TEST_METHOD(TestgetFileNameAndDirectory)
		{
			storage *s=storage::getInstance();
			string testString=s->getFileNameAndDirectory("C:", "SaveFile");
			string expected="C:\\SaveFile";
			Assert::AreEqual (expected,testString);
		}
		/*
		TEST_METHOD(TestgetFileName)
		{
			storage *s=storage::getInstance();
			string testString=s->getCurrentFileName();
			
			string expected="SaveFile";
			Assert::AreEqual (expected,testString);
		}
		
		TEST_METHOD(TestchangeFileName)
		{
			storage *s=storage::getInstance();
			s->setFileName("Save");
			string testString=s->getCurrentFileName();
			string expected="Save";
			Assert::AreEqual (expected,testString);
		}
        */
		TEST_METHOD(TestFloatDuplicated)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
			task Existing("shopping");
			Existing.addFloatItem();
			Itemlist.push_back(Existing);
			bool expected=true;
			bool duplicated=s->isFloatDuplicated(NewTask,Itemlist);
			Assert::AreEqual (expected,duplicated);
		}

		TEST_METHOD(TestFloatnotDuplicated)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
			task Existing("sh");
			Existing.addFloatItem();
			Itemlist.push_back(Existing);
			bool expected=false;
			bool duplicated=s->isFloatDuplicated(NewTask,Itemlist);
			Assert::AreEqual (expected,duplicated);
		}


		TEST_METHOD(TestisDeadlineDuplicated)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
		    NewTask.addDeadlineItem(27,04,2015,1000);
			defaultclass default;
			string description;
			default.addDeadlineTask("shopping /by 1000 on 27/04/2015",Itemlist,s);
			bool expected=true;
			bool duplicated=s->isDeadlineDuplicated(NewTask,Itemlist);
			Assert::AreEqual (expected,duplicated);
		
		}

		TEST_METHOD(TestisDeadlinenotDuplicated)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
		    NewTask.addDeadlineItem(27,04,2015,1000);
			defaultclass default;
			string description;
			default.addDeadlineTask("add meething /by 1000 on 27/04/2015",Itemlist,s);
			bool expected=false;
			bool duplicated=s->isDeadlineDuplicated(NewTask,Itemlist);
			Assert::AreEqual (expected,duplicated);
		}

		TEST_METHOD(TestIsTimeClashed)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
		    NewTask.addTimedItem(27,04,2015,900,27,04,2015,1100);
			defaultclass default;
			string description;
			default.addTimedTask("add meeting /from 1000 on 27/04/2015 /to 1300 on 27/04/2015",Itemlist,s);
			bool expected=true;
			bool clashed=s->isTimeClashed(NewTask,Itemlist);
			Assert::AreEqual (expected,clashed);
		}


		TEST_METHOD(TestIsTimenotClashed)
		{
			storage *s=storage::getInstance();
			task NewTask("shopping");
			vector <task> Itemlist;
		    NewTask.addTimedItem(27,04,2015,900,27,04,2015,1100);
			defaultclass default;
			string description;
			default.addTimedTask("add meeting /from 1100 on 27/04/2015 /to 1300 on 27/04/2015",Itemlist,s);
			bool expected=false;
			bool clashed=s->isTimeClashed(NewTask,Itemlist);
			Assert::AreEqual (expected,clashed);
		}



		TEST_METHOD(TestfileExistance)
		{
			storage *s=storage::getInstance();
			bool exist=s->fileExists("hellofile");
			bool expected=false;	
			Assert::AreEqual (expected,exist);
		}

	
	};
	
}