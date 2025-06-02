/***************************************************************
    Pequeño script auxiliar para visualizar output de
    distintos métodos para un mismo input pequeño aleatorio
 ***************************************************************/

#include "solution.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

const string chars = "ABCDE";

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> char_dist(0, chars.size() - 1);
uniform_int_distribution<> length_dist(0, 15);

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

int main() {
    /* Entrada */
    string str1 = random_string(random_length());
    string str2 = random_string(random_length());
    cout << "Entrada:" << endl;
    cout << "\tString 1: \t" << '"' << str1 << '"' << endl;
    cout << "\tString 2: \t" << '"' << str2 << '"' << endl;

    /* Métodos */
    std::vector<Solution*>solutions;
    solutions.push_back(new TopDown());
    solutions.push_back(new TopDownMemoization());
    solutions.push_back(new BottomUp());
    solutions.push_back(new BottomUpOptimized());
    solutions.push_back(new Verifier());

    /* Salida */
    cout << "Salida:" << endl;
    for (auto solution: solutions) {
        cout << "\t" << solution->name() << ": \t" << (*solution)(str1, str2) << endl;
        
    }

    /* Liberar memoria */
    for (auto solution: solutions) {
        delete solution;
    }

    /* Bye-bye */
    return 0;
}
