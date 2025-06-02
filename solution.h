/***************************************************************
    Header con la definición de una clase abstracta Solución
    y las definiciones de los distintos métodos a implementar.
 ***************************************************************/

#pragma once

#include <string>

/* Clase abstracta de una solución genérica al problema EditDistanceDeleteInsert(S,T) */
class Solution {
public:
    /* Resuelve una instancia del problema */
    virtual size_t operator()(std::string& str1, std::string& str2) = 0;
    /* Devuelve un nombre para la implementación */
    virtual const std::string& name() const = 0;
};

/* Implementa editDistanceRecursive */
class TopDown : public Solution {
public:
    size_t operator()(std::string& str1, std::string& str2) override;
    const std::string& name() const override;
};

/* Implementa editDistanceMemo */
class TopDownMemoization : public Solution {
public:
    size_t operator()(std::string& str1, std::string& str2) override;
    const std::string& name() const override;
};

/* Implementa editDistanceDP */
class BottomUp : public Solution {
public:
    size_t operator()(std::string& str1, std::string& str2) override;
    const std::string& name() const override;
};

/* Implementa editDistanceDPOptimized */
class BottomUpOptimized : public Solution {
public:
    size_t operator()(std::string& str1, std::string& str2) override;
    const std::string& name() const override;
};

/* Implementación externa para verificar correctitud */
class Verifier : public Solution {
    size_t operator()(std::string& str1, std::string& str2) override;
    const std::string& name() const override;
};