//
//  No.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __No__
#define __No__

#include <iostream>

template <typename T>
class No {
public:
    T valor;
    No* proximo;
    No* anterior;

    No() : proximo(nullptr), anterior(nullptr) {}

    No(T val) : valor(val), proximo(nullptr), anterior(nullptr) {}

    No(T val, No* n, No* p) : valor(val), proximo(n), anterior(p) {}
};

#endif