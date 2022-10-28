#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<int> ivec(10);
	int ivalue=0;
	for (vector<int>::iterator i=ivec.begin(); i!=ivec.end(); ++i)
		*i = ivalue++;

	vector<int>::iterator i=ivec.begin();
	i += 10;
	if (i == ivec.end()) cout << "iterator i == ivec.end()\n";
	++i;	// run time error
	return 0;
}