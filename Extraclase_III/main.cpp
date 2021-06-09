#include <iostream>

#include "DeteccionParidad.h"
#include "Hamming.h"
#include <iostream>

using namespace std;
int main() {

    DeteccionParidad dp;

    cout<<"-------------------DecteccionParidad-----------------------------"<<endl;

    if(dp.findParity(9) == 0){
        cout << "Paridad par"<<endl;
    }else{
        cout << "Paridad impar"<<endl;
    }

    if(dp.findParity(13) == 0){
        cout << "Paridad par"<<endl;
    }else{
        cout << "Paridad impar"<<endl;
    }

    cout<<"----------------------HammingCode-------------------------------"<<endl;

    Hamming hg;
    vector<int> messageBit = { 0, 1, 0, 1 };
    hg.findHammingCode(messageBit);
    cout<<endl;
    cout<<"----------------------------------------------------------------"<<endl;

    return 0;

}
