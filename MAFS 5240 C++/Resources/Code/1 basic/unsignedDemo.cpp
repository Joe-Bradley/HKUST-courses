#include <iostream>
using namespace std;

int unsignedDemo () {
	unsigned ui; /* 32 bits */

	cout << endl << endl;
	ui = 0xFFFFFFFF;
	cout << "max value for \"unsigned int\" or \"unsigned long\" is \"(2 ^ 32)-1\" = " << ui << endl;

	ui = -1;
	cout << endl;
	cout << "\"-1\" in \"unsigned int\" = " << ui << endl;
	ui = -2;
	cout << "\"-2\" in \"unsigned int\" = " << ui << endl;
	ui = 4294967296; /* warning from compiler: truncation from '__int64' to 'unsigned int' */
	cout << "\"4294967296\" in \"unsigned int\" = " << ui << endl;
	ui = 4294967297; /* warning from compiler: truncation from '__int64' to 'unsigned int' */
	cout << "\"4294967297\" in \"unsigned int\" = " << ui << endl;

	cout << endl << endl;
	unsigned long long ull; /* 64 bits */
	ull = 0xFFFFFFFFFFFFFFFF;
	cout << "max value for \"unsigned long long\" is \"(2 ^ 64)-1\" = " << ull << endl;
	ull = -1;
	cout << "\"-1\" in \"unsigned long long\" = " << ull << endl;
	ull = -2;
	cout << "\"-2\" in \"unsigned long long\" = " << ull << endl;
	return 0;
}