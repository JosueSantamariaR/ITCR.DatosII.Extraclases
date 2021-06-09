
#include "DeteccionParidad.h"
using namespace std;

// Function to find the parity
//    El bit de "y" localizado más a la derecha contiene el valor de paridad
//    si (y & 1) es 1, entonces la paridad es impar si no es par
bool DeteccionParidad::findParity(int x)
{
    int y = x ^ (x >> 1);
    y = y ^ (y >> 2);
    y = y ^ (y >> 4);
    y = y ^ (y >> 8);
    y = y ^ (y >> 16);

    if (y & 1)
        return 1;
    return 0;
}