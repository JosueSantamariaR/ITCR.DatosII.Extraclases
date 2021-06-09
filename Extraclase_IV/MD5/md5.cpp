
#include "md5.h"

void md5::add(uint8 *msg) {

}

void md5::add(uint8 *msg, uint32 Len) {
    // Len is the length of the string, and Len*8 identifies the bit length of the binary
    int Msg_len = 8*Len; // original message binary bit length
    uint32 msg_length = Len; // original message length (character)
    uint32 now_len = Len*8;
    now_len += 72;
    uint32 num0 = 0;
    num0 = (512 - now_len % 512) / 8; // Calculate the number of 0s that need to be filled
    msg[msg_length] = 0x80; //fill 1 followed by 7 0 (binary)
    msg_length += 1;

    uint32 i;
    for(i = 0; i < num0; ++i){
        msg[msg_length] = 0;
        msg_length++;
    }
    // fill the 64-bit original string length at the end
    uint8 c1 = (msg_len >> 56) & 0xff;
    uint8 c2 = (msg_len >> 48) & 0xff;
    uint8 c3 = (msg_len >> 40) & 0xff;
    uint8 c4 = (msg_len >> 32) & 0xff;
    uint8 c5 = (msg_len >> 24) & 0xff;
    uint8 c6 = (msg_len >> 16) & 0xff;
    uint8 c7 = (msg_len >> 8) & 0xff;
    uint8 c8 = (msg_len & 0xff);
    msg[msg_length] = c8; msg_length++;
    msg[msg_length] = c7; msg_length++;
    msg[msg_length] = c6; msg_length++;
    msg[msg_length] = c5; msg_length++;
    msg[msg_length] = c4; msg_length++;
    msg[msg_length] = c3; msg_length++;
    msg[msg_length] = c2; msg_length++;
    msg[msg_length] = c1; msg_length++;
    msg_len = msg_length;
}

uint32 md5::get_loop_count() {
    return msg_len * 8 / 512;
}



uint32 md5::F(uint32 X, uint32 Y, uint32 Z) {
    return (X & Y) | ((~X) & Z);
}

uint32 md5::G(uint32 X, uint32 Y, uint32 Z) {
    return (X & Z) | (Y & (~Z));
}

uint32 md5::H(uint32 X, uint32 Y, uint32 Z) {
    return X^Y^Z;
}

uint32 md5::I(uint32 X, uint32 Y, uint32 Z) {
    return Y^(X | (~Z));
}

uint32 md5::circle_left(uint32 number, uint32 count) {
    return (number << count) | (number >> (32 - count));
}


void md5::FF(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t) {
    (*a) += F(*b, *c, *d) + M + t;
    (*a) = circle_left(*a, s);
    (*a) += (*b);
}

void md5::GG(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t) {
    (*a) += G(*b, *c, *d) + M + t;
    (*a) = circle_left(*a, s);
    (*a) += (*b);
}

void md5::HH(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t) {
    (*a) += H(*b, *c, *d) + M + t;
    (*a) = circle_left(*a, s);
    (*a) += (*b);
}

void md5::II(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t) {
    (*a) += I(*b, *c, *d) + M + t;
    (*a) = circle_left(*a, s);
    (*a) += (*b);
}

void md5::one_step(const uint8 *const msg) {
    uint32 M[16];
    uint32 i, j;
    // Change the message into 16 32-bit unsigned numbers
    for(i = 0, j = 0; i < 16 && j < 512; ++i, j += 4)
        M[i] = (uint32)(msg[j]) | (msg[j+1] << 8) | (msg[j+2] << 16) | (msg[j+3] << 24);

    uint32 a, b, c, d;
    a = A;
    b = B;
    c = C;
    d = D;
    FF(&a, &b, &c, &d, M[0], 7, 0xd76aa478);
    FF(&d, &a, &b, &c, M[1], 12, 0xe8c7b756);
    FF(&c, &d, &a, &b, M[2], 17, 0x242070db);
    FF(&b, &c, &d, &a, M[3], 22, 0xc1bdceee);
    FF(&a, &b, &c, &d, M[4], 7, 0xf57c0faf);
    FF(&d, &a, &b, &c, M[5], 12, 0x4787c62a);
    FF(&c, &d, &a, &b, M[6], 17, 0xa8304613);
    FF(&b, &c, &d, &a, M[7], 22, 0xfd469501);
    FF(&a, &b, &c, &d, M[8], 7, 0x698098d8);
    FF(&d, &a, &b, &c, M[9], 12, 0x8b44f7af);
    FF(&c, &d, &a, &b, M[10], 17, 0xffff5bb1);
    FF(&b, &c, &d, &a, M[11], 22, 0x895cd7be);
    FF(&a, &b, &c, &d, M[12], 7, 0x6b901122);
    FF(&d, &a, &b, &c, M[13], 12, 0xfd987193);
    FF(&c, &d, &a, &b, M[14], 17, 0xa679438e);
    FF(&b, &c, &d, &a, M[15], 22, 0x49b40821);

    GG(&a, &b, &c, &d, M[1], 5, 0xf61e2562);
    GG(&d, &a, &b, &c, M[6], 9, 0xc040b340);
    GG(&c, &d, &a, &b, M[11], 14, 0x265e5a51);
    GG(&b, &c, &d, &a, M[0], 20, 0xe9b6c7aa);
    GG(&a, &b, &c, &d, M[5], 5, 0xd62f105d);
    GG(&d, &a, &b, &c, M[10], 9, 0x02441453);
    GG(&c, &d, &a, &b, M[15], 14, 0xd8a1e681);
    GG(&b, &c, &d, &a, M[4], 20, 0xe7d3fbc8);
    GG(&a, &b, &c, &d, M[9], 5, 0x21e1cde6);
    GG(&d, &a, &b, &c, M[14], 9, 0xc33707d6);
    GG(&c, &d, &a, &b, M[3], 14, 0xf4d50d87);
    GG(&b, &c, &d, &a, M[8], 20, 0x455a14ed);
    GG(&a, &b, &c, &d, M[13], 5, 0xa9e3e905);
    GG(&d, &a, &b, &c, M[2], 9, 0xfcefa3f8);
    GG(&c, &d, &a, &b, M[7], 14, 0x676f02d9);
    GG(&b, &c, &d, &a, M[12], 20, 0x8d2a4c8a);

    HH(&a, &b, &c, &d, M[5], 4, 0xfffa3942);
    HH(&d, &a, &b, &c, M[8], 11, 0x8771f681);
    HH(&c, &d, &a, &b, M[11], 16, 0x6d9d6122);
    HH(&b, &c, &d, &a, M[14], 23, 0xfde5380c);
    HH(&a, &b, &c, &d, M[1], 4, 0xa4beea44);
    HH(&d, &a, &b, &c, M[4], 11, 0x4bdecfa9);
    HH(&c, &d, &a, &b, M[7], 16, 0xf6bb4b60);
    HH(&b, &c, &d, &a, M[10], 23, 0xbebfbc70);
    HH(&a, &b, &c, &d,M[13], 4, 0x289b7ec6);
    HH(&d, &a, &b, &c, M[0], 11, 0xeaa127fa);
    HH(&c, &d, &a, &b, M[3], 16, 0xd4ef3085);
    HH(&b, &c, &d, &a, M[6], 23, 0x04881d05);
    HH(&a, &b, &c, &d, M[9], 4, 0xd9d4d039);
    HH(&d, &a, &b, &c, M[12], 11, 0xe6db99e5);
    HH(&c, &d, &a, &b, M[15], 16, 0x1fa27cf8);
    HH(&b, &c, &d, &a, M[2], 23, 0xc4ac5665);

    II(&a, &b, &c, &d, M[0], 6, 0xf4292244);
    II(&d, &a, &b, &c, M[7], 10, 0x432aff97);
    II(&c, &d, &a, &b, M[14], 15, 0xab9423a7);
    II(&b, &c, &d, &a, M[5], 21, 0xfc93a039);
    II(&a, &b, &c, &d, M[12], 6, 0x655b59c3);
    II(&d, &a, &b, &c, M[3], 10, 0x8f0ccc92);
    II(&c, &d, &a, &b, M[10], 15, 0xffeff47d);
    II(&b, &c, &d, &a, M[1], 21, 0x85845dd1);
    II(&a, &b, &c, &d, M[8], 6, 0x6fa87e4f);
    II(&d, &a, &b, &c, M[15], 10, 0xfe2ce6e0);
    II(&c, &d, &a, &b, M[6], 15, 0xa3014314);
    II(&b, &c, &d, &a, M[13], 21, 0x4e0811a1);
    II(&a, &b, &c, &d, M[4], 6, 0xf7537e82);
    II(&d, &a, &b, &c, M[11], 10, 0xbd3af235);
    II(&c, &d, &a, &b, M[2], 15, 0x2ad7d2bb);
    II(&b, &c, &d, &a, M[9], 21, 0xeb86d391);

    A += a;
    B += b;
    C += c;
    D += d;
}

void md5::GetHexStr(unsigned int num_str) {
    std::string hexstr = "";
    char szch[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    unsigned char *tmptr = (unsigned char *)&num_str;
    int len = sizeof(num_str);
    // little endian, reverse print
    for (int i = 0; i < len; i++){
        unsigned char ch = tmptr[i] & 0xF0;
        ch = ch >> 4;
        hexstr.append(1, szch[ch]);
        ch = tmptr[i] & 0x0F;
        hexstr.append(1, szch[ch]);
    }
    cout << hexstr ;
}

void md5::solve(uint8 *msg, uint32 Len) {
    add(msg, Len);
    loop_count = get_loop_count();
    uint32 i;
    for(i = 0; i < loop_count; ++i)
        one_step(msg+64*i);

    GetHexStr(A);
    GetHexStr(B);
    GetHexStr(C);
    GetHexStr(D);
}

md5::md5() {

}