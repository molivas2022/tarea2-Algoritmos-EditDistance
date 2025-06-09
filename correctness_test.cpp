/***************************************************************
    Pequeño script para visualizar output de
    distintos métodos para un mismo input pequeño aleatorio
 ***************************************************************/

#include "solution.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

const string chars = "abcde";
const size_t string_length = 12;
const size_t number_of_tests = 100;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> char_dist(0, chars.size() - 1);
uniform_int_distribution<> length_dist(0, string_length);

size_t random_length() {
    return length_dist(generator);
}

string random_string(size_t length) {
    string r_str;
    for (size_t i = 0; i < length; ++i) {
        r_str += chars[char_dist(generator)];
    }

    return r_str;
}

/* Corresponde a un sólo test aleatorio */
bool test(const std::vector<Solution*>& solutions, const Solution& verifier) {
    /* Entrada */
    string str1 = random_string(random_length());
    string str2 = random_string(random_length());
    cout << "Entrada:" << endl;
    cout << "\tString 1: \t" << '"' << str1 << '"' << endl;
    cout << "\tString 2: \t" << '"' << str2 << '"' << endl;

    /* Verificación */
    bool success = true;
    auto ground_truth = verifier(str1, str2);

    /* Salida */
    cout << "Salida:" << endl;
    for (auto solution: solutions) {
        auto output = (*solution)(str1, str2);
        cout << "\t" << solution->name() << ": \t" << output << endl;
        if (output != ground_truth) success = false;
    }

    return success;
}

int main() {
    /* Métodos */
    std::vector<Solution*>solutions;
    solutions.push_back(new TopDown());
    solutions.push_back(new TopDownMemoization());
    solutions.push_back(new BottomUp());
    solutions.push_back(new BottomUpOptimized());
    
    Solution* verifier = new Verifier();

    /* Test */
    size_t count = 0;
    for (size_t t = 0; t < number_of_tests; t++) {
        if (test(solutions, *verifier)) {
            count++;
        }
    }
    cout << endl << "Tasa de éxito: " << count << "\\" << number_of_tests << endl;

    /* Liberar memoria */
    for (auto solution: solutions) {
        delete solution;
    }
    delete verifier;

    /* Bye-bye */
    return 0;
}
