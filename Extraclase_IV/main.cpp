#include <iostream>
#include "SHA1/sha1.h"
#include "MD5/md5.h"

using namespace std;

int main() {

    cout<<"-----------------------SHA1-------------------------"<<endl;
    string textSHA1;
    sha1 sha;
    cout<<"Digite la palabra:"<<endl;
    cin >> textSHA1;
    sha.shaRun(textSHA1);

    cout<<"-----------------------MD5-------------------------"<<endl;
    md5 md;
    uint8 msg[1000] = "prueba";
    md.solucion(msg, 5);

    return 0;
}
