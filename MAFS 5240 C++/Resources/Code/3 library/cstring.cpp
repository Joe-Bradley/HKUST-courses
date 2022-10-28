#include <cstring>
#include <iostream>

using namespace std;

int main() {
	char *cStyleString =  "C Style String";
	char noNull[] = {'C', '+', '+'};
	cout << strlen(cStyleString) << endl; // ?
	cout << strlen(noNull) << endl;       // ?

	const char *cp1 = "A string example";
	const char *cp2 = "A different string";

	char largeStr[16 + 18 + 2];      // will hold cp1 a space and cp2
	strcpy(largeStr, cp1);     // copies cp1 into largeStr
	cout << largeStr << endl;
	strcat(largeStr, " ");     // adds a space at end of largeStr
	strcat(largeStr, cp2);     // concatenates cp2 to largeStr
	// prints A string example A different string
	cout << largeStr << endl;

	char largeStr1[16 + 18 + 2]; 
	strncpy(largeStr1, cp1, 17); // includes the null
	strncat(largeStr1, " ", 2); 
	strncat(largeStr1, cp2, 19); // adds at most 18 char, 
								// plus a null
	cout << largeStr1 << endl;

}
