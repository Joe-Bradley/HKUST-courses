#ifndef DATE_H
#define DATE_H

#define SUCCESS		1
#define FAILURE		0
#define	BAD_JDATE	0
#define BASE_YEAR	1900
typedef	long	julianDate;

class date {

protected:
	julianDate jDate;

public:
	//Constructors
	date(julianDate jDt = BAD_JDATE);
	date(int year, int month, int day);
	date(const date&);	// copy constructor

	//Destructor
	~date();

	//Assignment
	date& operator=(const date& dt);
	date& operator=(const julianDate& jDt);
	void setYMD(int year, int month, int day);

	//Useful Info
	int month() const;
	int day() const;
	int year() const;
	bool isLeapYear() const;
	/*
	int daysInYear() const;
	int dayOfWeek() const;
	bool isWeekDay() const;
	*/

	//Operations
	/*
	virtual void addYMD(int yrs, int mos, int days);
	virtual void addMonths(int months);
	virtual void addYears(int years);
	void operator+=(int days);
	void operator-=(int days);
	*/
	date& operator++();		// pre-increment
	date operator++(int);	// post-increment
	/*
	date& operator--();		// pre-decrement
	date operator--(int);	// post-decrement
	*/

	//Friends
	friend bool operator==(const date& d1, const date& d2);
	bool operator==(const date& dt);
	/*
	friend bool operator!=(const date& d1, const date& d2);
	friend bool operator<(const date& d1, const date& d2);
	friend bool operator>(const date& d1, const date& d2);
	friend bool operator>=(const date& d1, const date& d2);
	*/

	//Static
	static bool isLeapYear(int year);
	static int daysInYear(int year);
	static bool validYMD(int year, int month, int day);
	static bool isWeekDay(const julianDate& j);
	static julianDate YMD2julianDate(int year, int month, int day);
	static int julianDate2YMD(julianDate j, int* year, int* month, int* day);

};

#endif