#include <bitset>
#include <iostream>

using namespace std;

int main() {
	bitset<16> bitvec16 = 0xFF00;
	cout << "bitset<16> bitvec16 = 0xFF00" << endl;
	cout << "bitvec16 = " << bitvec16 << endl;
	bitset<32> bitvec32 = 0xFF00;
	cout << "bitset<32> bitvec32 = 0xFF00" << endl;
	cout << "bitvec32 = " << bitvec32 << endl;
}