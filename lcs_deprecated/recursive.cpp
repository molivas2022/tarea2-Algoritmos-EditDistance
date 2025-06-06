/***************************************************************
    Método recursivo directo sin Memoización.
    Reduce el problema a buscar LCS.
 ***************************************************************/

#include "solution.h"
#include <algorithm>

using namespace std;

static string _name = string("Recursivo");

static size_t lcs(const string& str1, const string& str2, size_t i1, size_t i2) {
    /* Caso base */
    if (i1 == str1.length() || i2 == str2.length()) {
        return 0;
    }
    /* Nuevo símbolo en común */
    if (str1[i1] == str2[i2]) {
        return 1 + lcs(str1, str2, i1 + 1, i2 + 1);
    }
    /* Decisión */
    return max(lcs(str1, str2, i1 + 1, i2), lcs(str1, str2, i1, i2 + 1));
}

size_t TopDown::operator()(const string& str1, const string& str2) const {
    return str1.length() + str2.length() - 2*lcs(str1, str2, 0, 0);
}

const string& TopDown::name() const {
    return _name;
}