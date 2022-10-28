#include "Date.h"
#include <set>
#include <fstream>

using namespace std;

enum DayOfWeek {SUN, MON, TUE, WED, THU, FRI, SAT};
set<int> holidays;

Date add1Day(Date dt) {
	// TODO
	return 20120924;
}

Date minus1Day(Date dt) {
	// TODO
	return 20120924;
}

bool isWeekEnd(Date dt) {
	// TODO
	return false;
}

bool isHoliday(Date dt) {
	// TODO
	return false;
}

bool isBusinessDay(Date dt) {
	// TODO
	return false;
}

int dateDiff(Date d1, Date d2) {  // d1 < d2
	// TODO
	return 0;
}

Date monthend(Date dt) {
	// TODO
	return 20210924;
}

Date nextMonthend(Date dt) {
	// TODO
	return 20210924;
}

bool loadHoliday(const char* filename) {
	ifstream holFile(filename);
	if (!holFile) return false;
	
	Date dt;
	while (holFile >> dt) {
		holidays.insert(dt);
	}

	holFile.close();
	return true;
}

bool removeHoliday() {
	holidays.clear();
	return true;
}