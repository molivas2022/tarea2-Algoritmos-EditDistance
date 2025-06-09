/***************************************************************
    Pequeño script para visualizar output de
    distintos métodos para los casos de prueba
 ***************************************************************/

#include "solution.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

vector<string> test_cases = {"computer", "compiler", "hash", "terminal"};

/* Corresponde a un sólo test */
pair<bool, size_t> test(const std::vector<Solution*>& solutions, const Solution& verifier,
          const string& str1, const string& str2) {

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

    return make_pair(success, ground_truth);
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
    std::vector<std::vector<size_t>> distance_matrix(test_cases.size(), vector<size_t>(test_cases.size()));
    size_t success_count = 0;
    size_t failure_count = 0;
    for (size_t i = 0; i < test_cases.size(); i++) {
        for (size_t j = 0; j < test_cases.size(); j++) {
            auto _test = test(solutions, *verifier, test_cases[i], test_cases[j]);
            if (_test.first) success_count++;
            else failure_count++;
            distance_matrix[i][j] = _test.second;
        }
    }
    cout << endl << "Tasa de éxito: " << success_count << "\\" << success_count + failure_count << endl;
    cout << endl << "Matriz de distancia: " << endl;
    for (auto row: distance_matrix) {
        for (auto col: row) {
            cout << col << '\t';
        }
        cout << endl;
    }

    /* Liberar memoria */
    for (auto solution: solutions) {
        delete solution;
    }
    delete verifier;

    /* Bye-bye */
    return 0;
}
