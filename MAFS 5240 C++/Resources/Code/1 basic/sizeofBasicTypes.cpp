#include <iostream>
using namespace std;

int sizeofBasicTypes () {
	cout << endl << endl;
	cout << "Type\t\tSize" << endl;
	cout << "----\t\t----" << endl;
	cout << "bool\t\t" << sizeof(bool) << endl;
	cout << "char\t\t" << sizeof(char) << endl;
	cout << "wchar_t\t\t" << sizeof(wchar_t) << endl;
	cout << "short\t\t" << sizeof(short) << endl;
	cout << "int\t\t" << sizeof(int) << endl;
	cout << "long\t\t" << sizeof(long) << endl;
	cout << "float\t\t" << sizeof(float) << endl;
	cout << "double\t\t" << sizeof(double) << endl;
	cout << "long double\t" << sizeof(long double) << endl;
	cout << "long long\t" << sizeof(long long) << endl; 
	return 0;
}