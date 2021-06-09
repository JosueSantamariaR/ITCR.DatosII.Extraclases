#include <iostream>

#include "DeteccionParidad.h"
#include "Hamming.h"
#include <iostream>

using namespace std;
int main() {

    DeteccionParidad dp;
    Hamming hg;
    (dp.findParity(9) == 0) ? cout << "Even Parity\n" :
    cout << "Odd Parity\n";

    (dp.findParity(13) == 0) ? cout << "Even Parity\n" :
    cout << "Odd Parity\n";

    vector<int> msgBit = { 0, 1, 0, 1 };

    // Function Call
    hg.findHammingCode(msgBit);

    return 0;

}
