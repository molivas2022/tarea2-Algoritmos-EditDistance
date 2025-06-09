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
    virtual size_t operator()(const std::string& str1, const std::string& str2) const = 0;
    /* Devuelve un nombre para la implementación */
    virtual const std::string& name() const = 0;
    /* Destructor */
    virtual ~Solution() {};
};

/* Implementa editDistanceRecursive */
class TopDown : public Solution {
public:
    size_t operator()(const std::string& str1, const std::string& str2) const override;
    const std::string& name() const override;
    ~TopDown() override;
};

/* Implementa editDistanceMemo */
class TopDownMemoization : public Solution {
public:
    size_t operator()(const std::string& str1, const std::string& str2) const override;
    const std::string& name() const override;
    ~TopDownMemoization() override;
};

/* Implementa editDistanceDP */
class BottomUp : public Solution {
public:
    size_t operator()(const std::string& str1, const std::string& str2) const override;
    const std::string& name() const override;
    ~BottomUp() override;
};

/* Implementa editDistanceDPOptimized */
class BottomUpOptimized : public Solution {
public:
    size_t operator()(const std::string& str1, const std::string& str2) const override;
    const std::string& name() const override;
    ~BottomUpOptimized() override;
};

/* Implementación externa para verificar correctitud */
class Verifier : public Solution {
    size_t operator()(const std::string& str1, const std::string& str2) const override;
    const std::string& name() const override;
    ~Verifier() override;
};