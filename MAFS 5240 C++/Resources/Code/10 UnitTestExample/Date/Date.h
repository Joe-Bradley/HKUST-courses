#pragma once

#define SUCCESS		1
#define FAILURE		0
#define	BAD_JDATE	0
#define BASE_YEAR	1900

typedef	long	julianDate;

class __declspec(dllexport) date {

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

	date operator-(int days);
	date operator+(int days);

	date& operator++();		// pre-increment
	date operator++(int);	// post-increment

	date& operator--();		// pre-decrement
	date operator--(int);	// post-decrement

	bool operator==(const date& dt);
	friend __declspec(dllexport) bool operator<(const date&, const date&);

	//Static
	static bool isLeapYear(int year);
	static int daysInYear(int year);
	static bool validYMD(int year, int month, int day);
	static bool isWeekDay(const julianDate& j);
	static julianDate YMD2julianDate(int year, int month, int day);
	static int julianDate2YMD(julianDate j, int* year, int* month, int* day);
};

