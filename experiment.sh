#!/bin/bash

# Generamos archivos de ejecución
make clean
make all

# Archivo CSV de salida
OUTPUT_CSV="results.csv"

# Inicializa CSV si no existe
if [ ! -f "$OUTPUT_CSV" ]; then
    echo "run, name, edit distance, time(ms), memory_KB, file1, file2" > "$OUTPUT_CSV"
fi

# Lista de combinaciones manuales
combinaciones=(
    # top-down con memo

    "2 files/test1.txt files/test1.txt"
    "2 files/test1.txt files/test2.txt"
    "2 files/test1.txt files/test3.txt"
    "2 files/test1.txt files/test4.txt"
    "2 files/test1.txt files/test5.txt"

    "2 files/test2.txt files/test1.txt"
    "2 files/test2.txt files/test2.txt"
    "2 files/test2.txt files/test3.txt"
    "2 files/test2.txt files/test4.txt"
    "2 files/test2.txt files/test5.txt"

    "2 files/test3.txt files/test1.txt"
    "2 files/test3.txt files/test2.txt"
    "2 files/test3.txt files/test3.txt"
    "2 files/test3.txt files/test4.txt"
    "2 files/test3.txt files/test5.txt"

    "2 files/test4.txt files/test1.txt"
    "2 files/test4.txt files/test2.txt"
    "2 files/test4.txt files/test3.txt"
    "2 files/test4.txt files/test4.txt"
    "2 files/test4.txt files/test5.txt"

    "2 files/test5.txt files/test1.txt"
    "2 files/test5.txt files/test2.txt"
    "2 files/test5.txt files/test3.txt"
    "2 files/test5.txt files/test4.txt"
    "2 files/test5.txt files/test5.txt"

    # bottom-up

    "3 files/test1.txt files/test1.txt"
    "3 files/test1.txt files/test2.txt"
    "3 files/test1.txt files/test3.txt"
    "3 files/test1.txt files/test4.txt"
    "3 files/test1.txt files/test5.txt"

    "3 files/test2.txt files/test1.txt"
    "3 files/test2.txt files/test2.txt"
    "3 files/test2.txt files/test3.txt"
    "3 files/test2.txt files/test4.txt"
    "3 files/test2.txt files/test5.txt"

    "3 files/test3.txt files/test1.txt"
    "3 files/test3.txt files/test2.txt"
    "3 files/test3.txt files/test3.txt"
    "3 files/test3.txt files/test4.txt"
    "3 files/test3.txt files/test5.txt"

    "3 files/test4.txt files/test1.txt"
    "3 files/test4.txt files/test2.txt"
    "3 files/test4.txt files/test3.txt"
    "3 files/test4.txt files/test4.txt"
    "3 files/test4.txt files/test5.txt"

    "3 files/test5.txt files/test1.txt"
    "3 files/test5.txt files/test2.txt"
    "3 files/test5.txt files/test3.txt"
    "3 files/test5.txt files/test4.txt"
    "3 files/test5.txt files/test5.txt"

    # bottom-up optimized

    "4 files/test1.txt files/test1.txt"
    "4 files/test1.txt files/test2.txt"
    "4 files/test1.txt files/test3.txt"
    "4 files/test1.txt files/test4.txt"
    "4 files/test1.txt files/test5.txt"

    "4 files/test2.txt files/test1.txt"
    "4 files/test2.txt files/test2.txt"
    "4 files/test2.txt files/test3.txt"
    "4 files/test2.txt files/test4.txt"
    "4 files/test2.txt files/test5.txt"

    "4 files/test3.txt files/test1.txt"
    "4 files/test3.txt files/test2.txt"
    "4 files/test3.txt files/test3.txt"
    "4 files/test3.txt files/test4.txt"
    "4 files/test3.txt files/test5.txt"

    "4 files/test4.txt files/test1.txt"
    "4 files/test4.txt files/test2.txt"
    "4 files/test4.txt files/test3.txt"
    "4 files/test4.txt files/test4.txt"
    "4 files/test4.txt files/test5.txt"

    "4 files/test5.txt files/test1.txt"
    "4 files/test5.txt files/test2.txt"
    "4 files/test5.txt files/test3.txt"
    "4 files/test5.txt files/test4.txt"
    "4 files/test5.txt files/test5.txt"

)

# Loop sobre cada caso de prueba
for linea in "${combinaciones[@]}"; do
    read -r param1 input1 input2 <<< "$linea"

    for i in {1..30}; do
        # Archivos temporales para salida y memoria
        OUTPUT_TMP=$(mktemp)
        MEMORY_TMP=$(mktemp)

        # Ejecutar programa con time, separando stdout y stderr
        command /usr/bin/time -f "%M" -o "$MEMORY_TMP" ./performance_test "$param1" "$input1" "$input2" > "$OUTPUT_TMP"

        # salida del programa
        PROGRAM_OUTPUT=$(tr '\n' ' ' < "$OUTPUT_TMP" | tr -d '\r')

        # Leer uso de memoria en KB
        MEMORY_KB=$(cat "$MEMORY_TMP")

        # Escribir línea en CSV
        echo "$i, $PROGRAM_OUTPUT, $MEMORY_KB, $input1, $input2" >> "$OUTPUT_CSV"

        # Limpiar temporales
        rm -f "$OUTPUT_TMP" "$MEMORY_TMP"
    done
done
