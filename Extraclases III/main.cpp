#include "DetecciónParidad.h"
#include <iostream>

using namespace std;
int main() {

    DetecciónParidad dp;

    (dp.findParity(9) == 0) ? cout << "Even Parity\n" :
    cout << "Odd Parity\n";

    (dp.findParity(13) == 0) ? cout << "Even Parity\n" :
    cout << "Odd Parity\n";


}
