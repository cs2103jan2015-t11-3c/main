#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(StorageTestcpp)
	{
	public:
		
		TEST_METHOD(TestgetFullFileName)
		{
			storage s;
			string testString=s.getFullFileName("C:", "SaveFile");
			string expected="C:\\SaveFile";
			Assert::AreEqual (expected,testString);
		}

		TEST_METHOD(TestFloatDuplicated)
		{
			storage s;
			task NewTask("shopping");
			vector <task> Itemlist;
			task Existing("shopping");
			Existing.addFloatItem();
			Itemlist.push_back(Existing);
			bool expected=true;
			bool duplicated=s.isFloatDuplicated(NewTask,Itemlist);
			Assert::AreEqual (expected,duplicated);
		}



		TEST_METHOD(TestfileExistance)
		{
			storage s;
			bool exist=s.fileExists("hellofile");
			bool expected=false;	
			Assert::AreEqual (expected,exist);
		}

	
	};
}