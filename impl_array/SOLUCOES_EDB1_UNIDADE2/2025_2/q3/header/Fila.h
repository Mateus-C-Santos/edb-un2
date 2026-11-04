//
//  Fila.h ​
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Fila__
#define __Fila__
#define __CHECK_INTEGRIDADE__ 1
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdexcept>
template <typename T>
class Fila
{
private:
    T* elementos;
    int capacidade;
    int quantidade;
    int inicio;
    int fim;
    
public:
    // Não altere ​
    Fila(int cap)
    {
        this->quantidade = 0;
        this->inicio = 0;
        this->fim = 0;
        this->capacidade = cap;
        this->elementos = new T[this->capacidade];
    }
    // Não altere ​
    ~Fila()
    {
        delete [] this->elementos;
    }
    
    int tamanho()
    {
        return this->quantidade;
    }

    // ​Leia o enunciado com atenção antes de implementar este método. 
    // Retorna o primeiro elemento sem alterar a fila.
    T frente()
    {
        if (this->vazia())
        {
            throw std::underflow_error("Nao e possivel acessar a frente de uma fila vazia.");
        }
        return this->elementos[this->inicio];
    }

    // Insere no fim lógico; o módulo faz o índice circular pelo array.
    void enfileirar(T elemento)
    {
        if (this->cheia())
        {
            throw std::overflow_error("Nao e possivel inserir em uma fila cheia.");
        }
        this->elementos[this->fim] = elemento;
        this->fim = (this->fim + 1) % this->capacidade;
        ++this->quantidade;
    }

    // Remove e retorna o elemento do início lógico.
    T desenfileirar()
    {
        if (this->vazia())
        {
            throw std::underflow_error("Nao e possivel remover de uma fila vazia.");
        }
        T elementoRemovido = this->elementos[this->inicio];
        this->inicio = (this->inicio + 1) % this->capacidade;
        --this->quantidade;
        return elementoRemovido;
    }

    bool cheia()
    {
        return this->quantidade == this->capacidade;
    }

    bool vazia()
    {
        return this->quantidade == 0;
    }

    std::string imprimir()
    {
        std::stringstream r; r << "{ "; for (int a = this->inicio, b = 0; b < this->quantidade; ++b, a = (a + 1) % this->capacidade) r << this->elementos[a] << " ";r << "}";return r.str();       
    }
};

#endif