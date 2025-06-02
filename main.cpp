/***************************************************************
    Programa principal para evaluar los distintos paradigmas.
    Recibe como argumento de ejecución:
    - Un entero indicando que implementación se va a evaluar:
        0 : editDistanceRecursive
        1 : editDistanceMemo
        2 : editDistanceDP
        3 : editDistanceDPOptimized
    - La dirección del archivo 1 a evaluar
    - La dirección del archivo 2 a evaluar
    Imprime el tiempo de ejecucuión [ns] del algoritmo.
 ***************************************************************/

#include "solution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>

using namespace std;

/* Función auxiliar para leer un archivo como string */
string file_to_str(const string& file_path) {
    ifstream file(file_path);
    if (!file) {
        throw runtime_error("Error al leer el archivo: " + file_path);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}


int main(int argc, char* argv[]) {

    /* Argumentos de ejecución */
    if (argc != 4) {
        cerr << "Formato de la entrada no válido" << endl;
        return 1;
    }
    int method = stoi(argv[1]);
    string file_path1 = argv[2];
    string file_path2 = argv[3];
    string str1;
    string str2;

    /* Lectura */
    try {
        str1 = file_to_str(file_path1);
        str2 = file_to_str(file_path2);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    /* Método */
    Solution* solution;
    switch (method) {
        case 0:
            solution = new Verifier();
            break;
        case 1:
            solution = new TopDownMemoization();
            break;
        case 2:
            solution = new BottomUp();
            break;
        case 3:
            solution = new BottomUpOptimized();
            break;
        default:
            cerr << "Argumento no válido" << endl;
            return 1;
    }

    /* Prueba */
    auto start = chrono::high_resolution_clock::now();
    auto output = (*solution)(str1, str2);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> duration = end - start;
    cout << "Salida: " << output << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " ns" << endl;

    /* Liberar memoria */
    delete solution;

    /* Bye-bye */
    return 0;
}