/***************************************************************
    Programación dinámica top-down que usa Memoización para
    las llamadas recursivas.
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <limits>

using namespace std;

// Se considerara UNCOMPUTED (valor más alto de size_t) como la marca de que no ha sido visitado
// OJO: puede dar problemas para textos muy largos
const size_t UNCOMPUTED = numeric_limits<size_t>::max();

static string _name = string("Memoización");

size_t eddi_memo(const string &str1, const string &str2, size_t i, size_t j, vector<vector<size_t>> &memo)
{
    size_t n = str1.size();
    size_t m = str2.size();

    // Si ya fue calculado las operaciones se saca directamente de la matriz
    if (memo[i][j] != UNCOMPUTED)
        return memo[i][j];

    // str1 es el string vacio (muchos inserts)
    if (i == n)
    {
        memo[i][j] = m - j;

        return memo[i][j];
    }

    // str2 es el string vacio (muchas eliminaciones)
    if (j == m)
    {
        memo[i][j] = n - i;

        return memo[i][j];
    }

    // Caracteres iguales, solo avanza en strings, no suma a las operaciones
    if (str1[i] == str2[j])
    {
        memo[i][j] = eddi_memo(str1, str2, i + 1, j + 1, memo);

        return memo[i][j];
    }

    // minimo entre insert y delete
    memo[i][j] = 1 + min(eddi_memo(str1, str2, i, j + 1, memo), eddi_memo(str1, str2, i + 1, j, memo));

    return memo[i][j];
}

size_t TopDownMemoization::operator()(const string &str1, const string &str2) const
{
    size_t n = str1.size();
    size_t m = str2.size();

    // Matriz de tamaño (n+1) x (m+1)
    vector<vector<size_t>> memo(n + 1, vector<size_t>(m + 1, UNCOMPUTED));

    return eddi_memo(str1, str2, 0, 0, memo);
}

const string &TopDownMemoization::name() const
{
    return _name;
}