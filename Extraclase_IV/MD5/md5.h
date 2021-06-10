

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;


class md5 {
private:
    uint32 A = 0x67452301;
    uint32 B = 0xefcdab89;
    uint32 C = 0x98badcfe;
    uint32 D = 0x10325476;

public:
    const uint32 MAX_MSG_SIZE = 10000;
    uint32 loop_count = 0;
    uint64 msg_len;
    md5();

    void agregar(uint8 *msg);


    void agregar(uint8 *msg, uint32 Len);

    uint32 get_Contador();

    uint32 F(uint32 X, uint32 Y, uint32 Z);

    uint32 G(uint32 X, uint32 Y, uint32 Z);

    uint32 H(uint32 X, uint32 Y, uint32 Z);

    uint32 I(uint32 X, uint32 Y, uint32 Z);

    uint32 circle_left(uint32 number, uint32 count);

    void FF(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t);

    void GG(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t);

    void HH(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t);

    void II(uint32 *a, uint32 *b, uint32 *c, uint32 *d, uint32 M, uint32 s, uint32 t);

    void pasos(const uint8 *const msg);


    void get_Hexa(unsigned int num_str);

    void solucion(uint8 *msg, uint32 Len);


};

