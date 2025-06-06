/***************************************************************
    Programación dinámica bottom-up. Sin optimizaciones
    de espacio.
    Reduce el problema a buscar LCS.
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <algorithm>

using namespace std;

static string _name = string("Dinámico");

size_t BottomUp::operator()(const string& str1, const string& str2) const {
    /* Usamos DP para determinar LCS */

    /* Matriz de tamaño n1+1 x n2+1 */
    vector<vector<size_t>> dp(str1.length() + 1, vector<size_t>(str2.length() + 1, 0));

    /* Recorrer desde la última fila a la primera */
    for (size_t row = str1.length(); row-- > 0;) {
        /* Recorrer desde la última columna a la primera */
        for (size_t col = str2.length(); col-- > 0;) {
            /* Nuevo símbolo en común */
            if (str1[row] == str2[col]) {
                dp[row][col] = dp[row+1][col+1] + 1;
                continue;
            }
            /* Decisión */
            dp[row][col] = max(dp[row+1][col], dp[row][col+1]);
        }
    }

    /* dp[0][0] <=> LCS(str1, str2) */
    return str1.length() + str2.length() - 2*dp[0][0];
}

const string& BottomUp::name() const {
    return _name;
}