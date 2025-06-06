/***************************************************************
    Programación dinámica top-down que usa Memoización para
    las llamadas recursivas.
    Reduce el problema a buscar LCS.
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <limits>

using namespace std;

static string _name = string("Memoización");

constexpr size_t EMPTY = numeric_limits<size_t>::max();

static size_t lcs(const string& str1, const string& str2, size_t i1, size_t i2, vector<vector<size_t>>& memo) {
    size_t _return;

    /* Caso base */
    if (i1 == str1.length() || i2 == str2.length()) {
        _return = 0;
    }
    /* Nuevo símbolo en común */
    else if (str1[i1] == str2[i2]) {
        if (memo[i1 + 1][i2 + 1] == EMPTY) {    /* Consulta de memoización */
            _return = 1 + lcs(str1, str2, i1 + 1, i2 + 1, memo);
        }
        _return = 1 + memo[i1 + 1][i2 + 1];
    }
    /* Decisión */
    else {
        size_t _choice1;
        if (memo[i1 + 1][i2] == EMPTY) {    /* Consulta de memoización */
            _choice1 = lcs(str1, str2, i1 + 1, i2, memo);
        }
        else {
            _choice1 = memo[i1 + 1][i2];
        }

        size_t _choice2;
        if (memo[i1][i2 + 1] == EMPTY) {    /* Consulta de memoización */
            _choice2 = lcs(str1, str2, i1, i2 + 1, memo);
        }
        else {
            _choice2 = memo[i1][i2 + 1];
        }
        _return = max(_choice1, _choice2);
    }
    /* Actualización de memoización */
    memo[i1][i2] = _return;
    return _return;
}

size_t TopDownMemoization::operator()(const string& str1, const string& str2) const {
    /* Matriz de tamaño n1+1 x n2+1 */
    vector<vector<size_t>> memo(str1.length() + 1, vector<size_t>(str2.length() + 1, EMPTY));

    return str1.length() + str2.length() - 2*lcs(str1, str2, 0, 0, memo);
}

const string& TopDownMemoization::name() const {
    return _name;
}