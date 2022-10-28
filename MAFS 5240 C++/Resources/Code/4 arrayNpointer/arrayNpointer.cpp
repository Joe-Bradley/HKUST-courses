#include <iostream>

using namespace std;

int main () {
	int iMatrix[3][4] = {0,1,2,3,10,11,12,13,20,21,22,23};
	int (*ip)[4] = iMatrix;	//pointer to an array of 4 integers
	cout << (*ip)[0] << (*ip)[1] << (*ip)[2] << (*ip)[3] << endl;
	ip = &iMatrix[2];
	cout << (*ip)[0] << (*ip)[1] << (*ip)[2] << (*ip)[3] << endl;

	// array of 4 pointers
	int *aip[4] = { &iMatrix[1][0],  &iMatrix[1][1], &iMatrix[1][2], &iMatrix[1][3] };
	cout << *aip[0] << *aip[1] << *aip[2] << *aip[3] << endl;

	double d = 0.0;
	if (d) cout << "d = 0.1" << endl;

	char pc[] = { '1', '\0' , '\0', '\0' };
	int *intp = reinterpret_cast<int*>(pc);
	//int *intp = (int*)pc;
	cout << *intp << endl;

	int ival=5; int *pval = &ival;
	int *&p = pval;		//reference to a pointer
	cout << *p << endl;


}