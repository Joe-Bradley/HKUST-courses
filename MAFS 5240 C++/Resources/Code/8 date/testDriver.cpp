#include "date.h"
#include <iostream>

using namespace std;

int main ()
{

	cout << "Testing static function \"YMD2julianDate\":" << endl;
	cout << "2100 28 Jan is :\t" << date::YMD2julianDate(2100,1,28) << endl;
	cout << "2040 1 Jan is :\t" << date::YMD2julianDate(2040,1,1) << endl;
	cout << endl;

	cout << "Testing static function \"julianDate2YMD\":" << endl;
	int y,m,d;
	int retcode = date::julianDate2YMD(73078,&y,&m,&d);
	cout << "Julian Date 73078 is :\t" << "year " << y << " month " << m << " day " << d << endl;
	cout << endl;
	
	cout << "Testing constructor: \"date dt1(73078)\":" << endl;
	date dt1(73078);
	cout << "year " << dt1.year() << " month " << dt1.month() << " day " << dt1.day() << endl;
	cout << endl;

	cout << "Testing constructor: \"date dt2(2010,1,28)\":" << endl;
	date dt2(2010,1,28);
	cout << "year " << dt2.year() << " month " << dt2.month() << " day " << dt2.day() << endl;
	cout << endl;

	cout << "Testing constructor: \"date dt3(dt2)\":" << endl;
	date dt3(dt2);
	cout << "year " << dt3.year() << " month " << dt3.month() << " day " << dt3.day() << endl;
	cout << endl;

	cout << "Testing global \"==\" operator (dt2 == dt3):" << endl;
	if (dt2 == dt3)
		cout << "dt2 equals dt3" << endl;
	else
		cout << "dt2 is not equal to dt3" << endl;
	cout << endl;

	cout << "Testing \"==\" operator (dt2 == dt3):" << endl;
	if (dt2.operator ==(dt3))
		cout << "dt2 equals dt3" << endl;
	else
		cout << "dt2 is not equal to dt3" << endl;
	cout << endl;

	cout << "Testing \"==\" operator (dt2 == 73078):" << endl;
	if (dt2 == 73078)
		cout << "dt2 equals dt3" << endl;
	else
		cout << "dt2 is not equal to dt3" << endl;
	cout << endl;

	cout << "Testing \"=\" operator (dt4 = 73078):" << endl;
	date dt4 = 73078;
	cout << "year " << dt4.year() << " month " << dt4.month() << " day " << dt4.day() << endl;

	cout << endl;
	cout << "Testing \"isWeekDay\":" << endl;
	cout << "28 Jan 2008 is Monday" << endl;
	cout << "Week Day? ";
	if (date::isWeekDay(39475))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	
	cout << endl;
	cout << "27 Jan 2008 is Sunday" << endl;
	cout << "Week Day? ";
	if (date::isWeekDay(39474))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << endl;
	cout << "2008 is leap year? " << date::isLeapYear(2008) << endl;
	cout << "2008 is leap year? " << (date::isLeapYear(2008) ? "Yes" : "No") << endl;
	cout << "2009 is leap year? " << date::isLeapYear(2009) << endl;
	cout << "2009 is leap year? " << (date::isLeapYear(2009) ? "Yes" : "No") << endl;

	cout << endl;
	cout << "Testing Prefix ++:" << endl;
	cout << "dt1.year() dt1.month() dt1.day() = " 
		 << dt1.year() << " " << dt1.month() << " " << dt1.day() <<endl;
	cout << "dt1.year() dt1.month() (++dt1).day() = " 
		 << dt1.year() << " " << dt1.month() << " " << (++dt1).day() <<endl;

	cout << endl;
	cout << "Testing Postfix ++:" << endl;
	cout << "dt1.year() dt1.month() dt1.day() = " 
		 << dt1.year() << " " << dt1.month() << " " << dt1.day() <<endl;
	cout << "dt1.year() dt1.month() (dt1++).day() = " 
		 << dt1.year() << " " << dt1.month() << " " << (dt1++).day() <<endl;
	cout << "dt1.year() dt1.month() dt1.day() = " 
		 << dt1.year() << " " << dt1.month() << " " << dt1.day() <<endl;

	return 0;
}