#include "Hamming.h"


vector<int> Hamming::initHamming(vector<int> completeMessageBits, int m, int r) {


    /// Vector utilizado para guardar el hamming code.
    vector<int> hammingSave(r + m);


    /// Encuentra las posiciones de los bits redundantes y las asigna como -1.
    /// Los bits redundantes se obtienen por medio de la potencia de 2.

    for (int i = 0; i < r; ++i) {
        hammingSave[pow(2, i) - 1] = -1;
    }




    /// Agrega al hammingSave los valores del mensaje que se ingresa, en las posiciones que son
    /// diferentes a las posiciones de los bits redundantes, esto para ir construyendo
    /// el hamming code completo.
    int j = 0;
    for (int i = 0; i < (r + m); i++) {
        if (hammingSave[i] != -1) {
            hammingSave[i] = completeMessageBits[j];
            j++;
        }
    }


    for (int i = 0; i < (r + m); i++) {

        /// Compara no es un bit redundante y continua
        if (hammingSave[i] != -1) {
            continue;
        }


        int x = log2(i + 1);
        int one_count = 0;


        /// Busca los bits del mensaje que contienen uno para definir una paridad
        for (int j = i + 2;j <= (r + m); ++j) {

            if (j & (1 << x)) {
                if (hammingSave[j - 1] == 1) {
                    one_count++;
                }
            }
        }

        /// Generando el hammingcode para paridad par
        if (one_count % 2 == 0) {
            hammingSave[i] = 0;
        } else {
            hammingSave[i] = 1;
        }
    }

    ///Retorna el hamming code generado

    return hammingSave;
}


void Hamming::findHammingCode(vector<int> &msgBit) {

    /// Se inicializa la longitud del mensaje.
    int m = msgBit.size();

    /// Se inicializa la cantidad de bits redundantes.
    int r = 1;

    /// Encuentra el numero de bits redundantes
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }

    vector<int> ans = initHamming(msgBit, m, r);

    cout << "Mensaje ingresado: ";
    for (int i = 0; i < msgBit.size(); i++)
        cout << msgBit[i] << " ";

    cout << endl;

    cout << "Mensaje con hamming: ";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";

}