#include <iostream>
#include "SHA1/sha1.h"
using namespace std;
int main() {

    string text;
    while (true)
    {
        sha1 sha;
        cin >> text;
        sha.shaRun(text);
    }
    return 0;
}