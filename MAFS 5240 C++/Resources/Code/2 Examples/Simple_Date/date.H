#ifndef date_H
#define date_H

class Date {
public:
   Date(int = 1, int = 1, int = 1900);  // default constructor
   void print(void);
   void setDate(int, int, int);
   void setMonth(int);
   void setDay(int);
   void setYear(int);
   int getMonth(void);
   int getDay(void);
   int getYear(void);
   int leapYear(void);
   int monthDays(void);
   void nextDay(void);
private:
   int month;
   int day;
   int year;
};

#endif



