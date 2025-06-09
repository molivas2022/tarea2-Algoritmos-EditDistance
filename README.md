# Tarea de Algoritmos en C++

## Compilación

Para compilar todos los archivos necesarios, ejecutar:

```bash
make
````

## Ejecutar Casos de Prueba

Para correr las implementaiones sobre los casos de prueba definidos:

```bash
./test_cases
```

## Test de Correctitud (Input Aleatorio)

Para realizar un test de correctitud utilizando entradas generadas aleatoriamente:

```bash
./correctness_test
```

## Test de Rendimiento

Para medir el rendimiento de un algoritmo específico con dos textos de entrada:

```bash
./performance_test [Algoritmo a medir] [Texto 1] [Texto 2]
```

### Medición de Espacio en Memoria

Después de correr un test de rendimiento, se puede medir el uso de memoria con el siguiente comando:

```bash
/usr/bin/time -f "%M" ./performance_test [Algoritmo a medir] [Texto 1] [Texto 2]
```

Donde `%M` indica el uso máximo de memoria en kilobytes.

---

## Requisitos

* C++17 o superior
* `make` instalado
* Unix-like environment (Linux o macOS recomendado)