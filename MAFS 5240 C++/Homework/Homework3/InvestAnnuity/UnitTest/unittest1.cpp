#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_CLASS_INITIALIZE(LOADHOLIDAYS)
		{
			char* file = "C:/Users/cdshum/Documents/temp/InvestAnnuity/Holiday.txt";
			Assert::IsTrue(loadHoliday(file));
		}

		TEST_CLASS_CLEANUP(REMOVEHOLIDAYS)
		{
			removeHoliday();
		}
		TEST_METHOD(FEB2000)
		{
			Date d = 20000228;
			d = add1Day(d);
			Assert::IsTrue(d == 20000229);
			d = add1Day(d);
			Assert::IsTrue(d == 20000301);
			d = minus1Day(d);
			Assert::IsTrue(d == 20000229);
		}
		TEST_METHOD(FEB2001)
		{
			Date d = 20010228;
			d = add1Day(d);
			Assert::IsTrue(d == 20010301);
			d = add1Day(d);
			Assert::IsTrue(d == 20010302);
			d = minus1Day(minus1Day(d));
			Assert::IsTrue(d == 20010228);
		}
		TEST_METHOD(DEC2001)
		{
			Date d = 20011231;
			d = add1Day(d);
			Assert::IsTrue(d == 20020101);
			d = add1Day(d);
			Assert::IsTrue(d == 20020102);
			d = minus1Day(minus1Day(d));
			Assert::IsTrue(d == 20011231);
		}
		TEST_METHOD(ISWEEKEND)
		{
			Date d = 20210918; //SAT
			Assert::IsTrue(isWeekEnd(d));
			d = add1Day(d); //SUN
			Assert::IsTrue(isWeekEnd(d));
			d = add1Day(d); //MON
			Assert::IsFalse(isWeekEnd(d));
			d = 20210829; //SUN
			Assert::IsTrue(isWeekEnd(d));
			d = minus1Day(d); //SAT
			Assert::IsTrue(isWeekEnd(d));
			d = minus1Day(d); //FRI
			Assert::IsFalse(isWeekEnd(d));
		}
		TEST_METHOD(MONTHEND)
		{
			Date d = 20210917;
			Assert::IsTrue(monthend(d) == 20210930);
			d = 20211017;
			Assert::IsTrue(monthend(d) == 20211029); // weekdend
			d = 20211217;
			Assert::IsTrue(monthend(d) == 20211230); // in Holiday file
		}

		TEST_METHOD(INVESTANNUITY) {
			Assert::AreEqual(6243.22, InvestAnnuity(20210922, 5, 10000, 10, 3), 0.02);
			Assert::AreEqual(8542.06, InvestAnnuity(20210924, 10, 10000, 15, 2), 0.02);
		}
	};
}