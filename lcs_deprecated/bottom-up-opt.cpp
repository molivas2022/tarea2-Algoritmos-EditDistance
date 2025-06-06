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
    /* Usamos DP para determinar LCS */

    /* 
    Sea la matriz dinámica de tamaño n1+1 x n2+1.
    Limitamos a guardar a lo más dos filas.
    */
    vector<size_t> row(str2.length() + 1);
    row[str2.length()] = 0;                         /* fuera de indice <=> str1 = "" */
    vector<size_t> pre_row(str2.length() + 1, 0);

    /* Recorrer desde la última fila a la primera */
    for (size_t i = str1.length(); i-- > 0;) {
        /* Recorrer desde la última columna a la primera */
        for (size_t j = str2.length(); j-- > 0;) {
            /* Nuevo símbolo en común */
            if (str1[i] == str2[j]) {
                row[j] = pre_row[j+1] + 1;
                continue;
            }
            /* Decisión */
            row[j] = max(pre_row[j], row[j+1]);
        }
        /* Siguiente iteración */
        pre_row = row;
    }

    /* row[0] <=> dp[0][0] <=> LCS(str1, str2) */
    return str1.length() + str2.length() - 2*row[0];
}

const string& BottomUpOptimized::name() const {
    return _name;
}