#ifndef NO_H
#define NO_H

template <typename T>
class No
{
public:
    T valor;
    No* proximo = nullptr;
    No* anterior = nullptr;

    explicit No(const T& valor) : valor(valor) {}
};

#endif
