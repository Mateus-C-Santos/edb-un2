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
    // Pode alterar, desde que você mantenha a coerência dos valores 
    // inicializados aqui durante as operações
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
    // Consulta a frente sem remover o elemento.
    T frente()
    {
        if (this->vazia())
        {
            throw std::underflow_error("Nao e possivel acessar a frente de uma fila vazia.");
        }
        return this->elementos[this->inicio];
    }

    // Insere no índice fim e avança circularmente para a próxima posição.
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

    // Retira o elemento da frente e avança o índice inicio circularmente.
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

    // Método auxiliar já usado pelo main.cpp fornecido na prova.
    // Percorre os elementos na ordem lógica, respeitando o array circular.
    std::string imprimir()
    {
        std::stringstream resultado;
        resultado << "{ ";

        int indice = this->inicio;
        for (int i = 0; i < this->quantidade; ++i)
        {
            resultado << this->elementos[indice] << " ";
            indice = (indice + 1) % this->capacidade;
        }

        resultado << "}";
        return resultado.str();
    }
};

#endif