#include<iostream>
#include<vector>
#include<string>

using namespace std;


class sha1 {
public:
    sha1();

    void printX();

    int S(unsigned int x, int n);

    void append(string m);

    void setW(vector<int> m, int n);

    int ft(int t);

    int Kt(int t);

    void shaRun(string text);

};

