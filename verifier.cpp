/***************************************************************
    Implementación externa usada solamente para verificar
    coincidencia de output con el resto de implementaciones
    propias.
    Fuente: https://github.com/Meteorix/pylcs
 ***************************************************************/

#include "solution.h"
#include <vector>
#include <string>

using namespace std;

static string _name = string("Verificador");

static vector<string> utf8_split(const string &str){
    vector<string> split;
    size_t len = str.length();
    size_t left = 0;
    size_t right = 1;

    for (size_t i = 0; i < len; i++){
        if (right >= len || ((str[right] & 0xc0) != 0x80)){
            string s = str.substr(left, right - left);
            split.push_back(s);
            left = right;
        }
        right ++;
    }
    return split;
}

static size_t lcs(const string &str1, const string &str2) {
    if (str1 == "" || str2 == "")
        return 0;
    vector<string> s1 = utf8_split(str1);
    vector<string> s2 = utf8_split(str2);
    size_t m = s1.size();
    size_t n = s2.size();
    vector<vector<size_t>> dp(m + 1, vector<size_t>(n + 1));
    size_t i, j;

    for (i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[m][n];
}

size_t Verifier::operator()(string& str1, string& str2) {
    return str1.length() + str2.length() - 2*lcs(str1, str2);
}

const string& Verifier::name() const {
    return _name;
}