/***************************************************************
    Programación dinámica bottom-up que implementa
    optimizaciones de espacio.
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <algorithm>

using namespace std;

static string _name = string("Optimizado");

size_t BottomUpOptimized::operator()(const string& str1, const string& str2) const {
    /* El algoritmo a continuación es O(str1.length()) en espacio */
    /* Así que hacemos lo siguiente para conseguir O(min(str1.length(), str2.length())) */
    if (str1.length() > str2.length()) {
        return (*this)(str2, str1);
    }

    /* Constantes */
    const size_t n1 = str1.length();
    const size_t n2 = str2.length();

    /* 
    Sea la matriz dinámica de tamaño n1+1 x n2+1.
    Limitamos a guardar a lo más dos filas.
    */
    vector<size_t> pre_row(n2 + 1);
    vector<size_t> row(n2 + 1);

    /* Ultima fila = [n2, n2 - 1, ..., 1, 0] */
    for (size_t col = 0; col <= n2; col++) {
        pre_row[col] = n2 - col;
    }
    /* Caso borde: n1 = 0 */
    row = pre_row;

    /* Recorrer desde la última fila a la primera */
    for (size_t i = n1; i-- > 0;) {
        /* Ultima columna = tranpose([n1, n1 - 1, ..., 1, 0])*/
        row[n2] = n1 - i;
        /* Recorrer desde la última columna a la primera */
        for (size_t j = n2; j-- > 0;) {
            /* Símbolo en común */
            /* No es necesario hacer una operación */
            if (str1[i] == str2[j]) {
                row[j] = pre_row[j+1];
                continue;
            }
            /* Símbolos distintos: Decidir entre */
            /*  a) Eliminar el simbolo en str1 */
            /*  b) Agregar el simbolo de str2 a str1 */
            row[j] = min(pre_row[j], row[j+1]) + 1;
        }
        /* Siguiente iteración */
        pre_row = row;
    }

    /* row[0] <=> dp[0][0] <=> eddi(str1, str2) */
    return row[0];
}

const string& BottomUpOptimized::name() const {
    return _name;
}

/* Destructor */
BottomUpOptimized::~BottomUpOptimized() {}