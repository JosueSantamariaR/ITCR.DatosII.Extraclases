//
// Created by garroakion on 9/6/21.
//

#include "sha1.h"

#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<int> X;//8*64=512, each subscript stores 8 bits
int W[80];//32 bits as a group
int A, B, C, D, E;
int A1, B1, C1, D1, E1; // buffer register, produce the final result
int Turn; // number of encrypted packets

void sha1::printX() {//output the filled text
    for (int i = 0; i < X.size(); i++) {
        printf("%02x", X[i]);
        if ((i + 1) % 4 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}

int sha1::S(unsigned int x, int n) {//cycle left shift
    return x >> (32 - n) | (x << n);
}

void sha1::append(string m) {//text fill processing
    Turn = (m.size() + 8) / 64 + 1;
    X.resize(Turn * 64);
    int i = 0;
    for (; i < m.size(); i++) {
        X[i] = m[i];
    }
    X[i++] = 0x80;
    while (i < X.size() - 8) {
        X[i] = 0;
        i++;
    }
    long long int a = m.size() * 8;
    for (i = X.size() - 1; i >= X.size() - 8; i--) {
        X[i] = a % 256;
        a /= 256;
    }
}

void sha1::setW(vector<int> m, int n) {//W array generation
    n *= 64;
    for (int i = 0; i < 16; i++) {
        W[i] = (m[n + 4 * i] << 24) + (m[n + 4 * i + 1] << 16)
               + (m[n + 4 * i + 2] << 8) + m[n + 4 * i + 3];
    }
    for (int i = 16; i < 80; i++) {
        W[i] = S(W[i - 16] ^ W[i - 14] ^ W[i - 8] ^ W[i - 3], 1);
    }
}

int sha1::ft(int t) {//ft(B,C,D) function
    if (t < 20)
        return (B & C) | ((~B) & D);
    else if (t < 40)
        return B ^ C ^ D;
    else if (t < 60)
        return (B & C) | (B & D) | (C & D);
    else
        return B ^ C ^ D;
}

int sha1::Kt(int t) {//constant K
    if (t < 20)
        return 0x5a827999;
    else if (t < 40)
        return 0x6ed9eba1;
    else if (t < 60)
        return 0x8f1bbcdc;
    else
        return 0xca62c1d6;
}

void sha1::shaRun(string text) {
    A1 = A = 0x67452301;
    B1 = B = 0xefcdab89;
    C1 = C = 0x98badcfe;
    D1 = D = 0x10325476;
    E1 = E = 0xc3d2e1f0;
    append(text);
    printX();
    for (int i = 0; i < Turn; i++) {
        setW(X, i);
        for (int t = 0; t < 80; t++) {
            int temp = E + ft(t) + S(A, 5) + W[t] + Kt(t);
            E = D;
            D = C;
            C = S(B, 30);
            B = A;
            A = temp;
        }
        A1 = A = A + A1;
        B1 = B = B + B1;
        C1 = C = C + C1;
        D1 = D = D + D1;
        E1 = E = E + E1;
    }
    printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);
}

sha1::sha1() {

}
