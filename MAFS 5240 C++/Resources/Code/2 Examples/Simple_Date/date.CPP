#include <iostream>
#include "date.h"

using namespace std;

Date::Date(int m, int d, int y) { setDate(m, d, y);}

int Date::getDay() { return day;}

int Date::getMonth() { return month;}

int Date::getYear() { return year;}

void Date::setDay(int d)
{
   if (month == 2 && leapYear())
      day = (d <= 29 && d >= 1) ? d : 1;
   else
      day = (d <= monthDays() && d >= 1) ? d : 1;
}

void Date::setMonth(int m) { month = m <= 12 && m >= 1 ? m : 1;}

void Date::setYear(int y) { year = y;}

void Date::setDate(int mo, int dy, int yr)
{
   setMonth(mo);
   setDay(dy);
   setYear(yr);
}

void Date::print()
   { cout << month << '-' << day << '-' << year << "\n"; }

void Date::nextDay()
{
   setDay( day + 1 );

   if ( day == 1 ) {
      setMonth( month + 1 );

      if ( month == 1 )
         setYear(year + 1);
   }
}

int Date::leapYear(void)
{
   if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
         return 1;
      else
         return 0;    // not a leap year
}

int Date::monthDays(void)
{
   const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   return month == 2 && leapYear() ? 29 : days[month - 1];
}