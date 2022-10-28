#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(JULIANDATE)
		{
			int jDt = date::YMD2julianDate(2017, 11, 24);
			Assert::AreEqual(jDt, 43063);
		}

		TEST_METHOD(YEAR_MONTH_DAY)
		{
			// TODO: Your test code here
			date dt = 43063;
			Assert::AreEqual(dt.year(), 2017);
			Assert::AreEqual(dt.month(), 11);
			Assert::AreEqual(dt.day(), 23);
		}

		TEST_METHOD(FINDMAX)
		{
			int a[] = { 1, 23, 4, 5,10 };
			Assert::IsTrue(Max(a, 5) == 23);
		}

		TEST_METHOD(AVERAGE)
		{
			int a[] = { 1, 2, 3, 4, 5};
			Assert::AreEqual(Avg(a, 5), 3.0, 0.00001);
		}
	};
}