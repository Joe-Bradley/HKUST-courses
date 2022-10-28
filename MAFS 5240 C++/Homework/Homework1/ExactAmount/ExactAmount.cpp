#include <iostream>

using namespace std;

int main() {
    int n10Dollar, n20Dollar, n50Dollar, n100Dollar, n500Dollar, bill;
    // Original number of coins in pocket
    cout << "Original number of bills in wallet:" << endl;
    cout << "Number of 10-Dollar bills: ";
    cin >> n10Dollar;
    cout << "Number of 20-Dollar bills: ";
    cin >> n20Dollar;
    cout << "Number of 50-Dollar bills: ";
    cin >> n50Dollar;
    cout << "Number of 100-Dollar bills: ";
    cin >> n100Dollar;
    cout << "Number of 500-Dollar bills: ";
    cin >> n500Dollar;
    cout << endl;

    // Bill to pay.
    // Assume bill amount is a whole integer multiples of 10
    cout << "Bill Amount : ";
    cin >> bill;
    cout << endl;

    // Fill in the code to calculate payment in terms of number of x-Dollar
    // bills. If not enough money, number of x-Dollar bills in payment should
    // all be 0s. Bill should be settled in exact amount; otherwise, number of
    // x-Dollar bills in payment should all be 0s.

    // define money_array left in pocket
    int bill_remain[5] = {n10Dollar, n20Dollar, n50Dollar, n100Dollar,
                          n500Dollar};
    const int bill_value[5] = {10, 20, 50, 100, 500};
    // do payment, from bigger face value to smaller value.
    for (int i = 4; i >= 0; i--) {
        // enough face value for payment
        if (bill / bill_value[i] <= bill_remain[i]) {
            bill_remain[i] = bill_remain[i] - bill / bill_value[i];
            bill = bill - bill / bill_value[i] * bill_value[i];
        }
        // not enough face value
        else if (bill / bill_value[i] >= bill_remain[i] && bill_remain[i] > 0) {
            bill = bill - bill_remain[i] * bill_value[i];
            bill_remain[i] = 0;
        } else {
            continue;
        }
    }
    //print outcomes
    cout << "Payment:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Number of " << bill_value[i]
             << "-Dollar bills: " << bill_remain[i] << endl;
    }
    cout << "It remains " << bill << " dollar to pay." << endl;
    return 0;
}