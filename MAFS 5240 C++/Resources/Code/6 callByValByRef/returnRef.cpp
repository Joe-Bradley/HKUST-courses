#include <iostream>
#include <string>

using namespace std;

// find shorter of two strings
string &shorterString(string &s1, 
                      string &s2)
     {
         return s1.size() < s2.size() ? s1 : s2;
     }

int main() {
	string slong("longlong"), sshort("short");
	cout << shorterString(slong, sshort) << endl;
	// assign to returned reference string object
	shorterString(slong, sshort) = "short changed";
	cout << sshort << endl;
	return 0;
}
