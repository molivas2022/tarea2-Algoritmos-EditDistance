/***************************************************************
    Programación dinámica bottom-up. Sin optimizaciones
    de espacio.
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <algorithm>

using namespace std;

static string _name = string("Dinámico");

size_t BottomUp::operator()(const string& str1, const string& str2) const {
    /* Constantes */
    const size_t n1 = str1.length();
    const size_t n2 = str2.length();

    /* Matriz de tamaño n1+1 x n2+1 */
    vector<vector<size_t>> dp(n1 + 1, vector<size_t>(n2 + 1));

    /* Ultima fila = [n2, n2 - 1, ..., 1, 0] */
    for (size_t col = 0; col <= n2; col++) {
        dp[n1][col] = n2 - col;
    }

    /* Ultima columna = tranpose([n1, n1 - 1, ..., 1, 0])*/
    for (size_t row = 0; row <= n1; row++) {
        dp[row][n2] = n1 - row;
    }

    /* Recorrer desde la última fila a la primera */
    for (size_t row = n1; row-- > 0;) {
        /* Recorrer desde la última columna a la primera */
        for (size_t col = n2; col-- > 0;) {
            /* Símbolo en común */
            /* No es necesario hacer una operación */
            if (str1[row] == str2[col]) {
                dp[row][col] = dp[row+1][col+1];
                continue;
            }
            /* Símbolos distintos: Decidir entre */
            /*  a) Eliminar el simbolo en str1 */
            /*  b) Agregar el simbolo de str2 a str1 */
            dp[row][col] = min(dp[row+1][col], dp[row][col+1]) + 1;
        }
    }

    /* dp[0][0] <=> eddi(str1, str2) */
    return dp[0][0];
}

const string& BottomUp::name() const {
    return _name;
}