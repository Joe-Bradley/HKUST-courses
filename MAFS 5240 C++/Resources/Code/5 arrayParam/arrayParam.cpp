#include <iostream>

using namespace std;

void accessAs1DArray(int *iArray) {
	//Access iArray as 1-D array
	for (size_t i=0; i!=12; ++i)
		cout << "iArray[" << i << "]\t= " << iArray[i] << endl;
}

void accessAs4x3Array(int iArray[][3]) {
	//Access iArray as 4x3 array
	for (size_t row=0; row!=4; ++row) {
		cout << "row " << row << ":\t";
		for (size_t col=0; col!=3; ++col)
			cout << iArray[row][col] << "\t";
		cout << endl;
	}
}

int main() {
	cout << "Pass a 1-D array:" << endl;
	int iA[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
	accessAs1DArray(iA);

	cout << endl << "Pass a 1-D array as a 2-D array:" << endl;
	accessAs4x3Array(reinterpret_cast<int (*)[3]> (iA));

	cout << endl << "Pass a 2-D array as a 1-D array:" << endl; 
	int iA3x4[3][4] = {0,1,2,3,10,11,12,13,20,21,22,23};
	accessAs1DArray(&iA3x4[0][0]);
	return 1;
}
	