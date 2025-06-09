/***************************************************************
    Método recursivo directo sin Memoización.
 ***************************************************************/
#include "solution.h"

using namespace std;

static string _name = string("Recursivo");

size_t eddi_recursive(const string &str1, const string &str2, size_t i, size_t j)
{
    size_t n = str1.size();
    size_t m = str2.size();

    // caso en que str1 es string vacio (muchas inserciones)
    if (i == n)
    {
        return m - j;
    }

    // caso en que str2 es string vacio (muchas eliminaciones)
    if (j == m)
    {
        return n - i;
    }

    // los caracteres son iguales (no se hace nada y se pasa al siguiente)
    if (str1[i] == str2[j])
    {
        return eddi_recursive(str1, str2, i + 1, j + 1);
    }

    // los caracteres son distintos (hacemos recursión y vemos cual es el menor)
    return 1 + min(eddi_recursive(str1, str2, i, j + 1), eddi_recursive(str1, str2, i + 1, j));
}

size_t TopDown::operator()(const string &str1, const string &str2) const
{
    size_t solution = eddi_recursive(str1, str2, 0, 0);

    return solution;
}

const string &TopDown::name() const
{
    return _name;
}

/* Destructor */
TopDown::~TopDown() {}