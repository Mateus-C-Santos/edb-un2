// -----------------------------------------------------------------------------
// Pilha.h
// Implementacao de uma PILHA usando um array alocado dinamicamente.
//
// Uma pilha segue a regra LIFO (Last In, First Out):
// o ULTIMO elemento que entra e o PRIMEIRO que sai.
// Exemplo: empilhar 10, 20 e 30 -> desempilhar remove primeiro o 30.
// -----------------------------------------------------------------------------

#ifndef PILHA_H
#define PILHA_H

#include <optional>   // std::optional e std::nullopt
#include <sstream>    // std::stringstream, usado para montar a impressao
#include <stdexcept>  // std::overflow_error, std::underflow_error...
#include <string>

template <typename T>
class Pilha
{
private:
    T* elementos;       // Array que guarda os elementos da pilha.
    int capacidade;     // Quantidade maxima de elementos que cabem no array.
    int quantidade;     // Quantos elementos estao efetivamente na pilha.

public:
    // Cria uma pilha vazia com capacidade fixa.
    Pilha(int cap)
        : elementos(nullptr), capacidade(cap), quantidade(0)
    {
        // Uma capacidade zero ou negativa nao permite armazenar elementos.
        if (cap <= 0)
        {
            throw std::invalid_argument("A capacidade da pilha deve ser positiva.");
        }

        // Reserva na memoria um array com 'cap' posicoes.
        elementos = new T[capacidade];
    }

    // Libera a memoria reservada no construtor.
    ~Pilha()
    {
        delete[] elementos;
    }

    // Retorna quantos elementos estao armazenados agora.
    int tamanho() const
    {
        return quantidade;
    }

    // Uma pilha esta vazia quando nao possui nenhum elemento.
    bool vazia() const
    {
        return quantidade == 0;
    }

    // Uma pilha esta cheia quando quantidade alcanca a capacidade.
    bool cheia() const
    {
        return quantidade == capacidade;
    }

    // Consulta o elemento que esta no topo, sem remove-lo.
    // O topo fica sempre na posicao quantidade - 1.
    // Se estiver vazia, retorna std::nullopt (ausencia de valor).
    std::optional<T> topo() const
    {
        if (vazia())
        {
            return std::nullopt;
        }

        return elementos[quantidade - 1];
    }

    // Insere um novo elemento no topo da pilha.
    void empilhar(T elemento)
    {
        // Nao podemos escrever fora do array.
        if (cheia())
        {
            throw std::overflow_error("Erro: pilha cheia.");
        }

        // quantidade tambem indica a proxima posicao livre.
        // Exemplo: se ha 2 elementos, a proxima posicao livre e [2].
        elementos[quantidade] = elemento;

        // Agora existe mais um elemento armazenado.
        ++quantidade;
    }

    // Remove o elemento que esta no topo.
    void desempilhar()
    {
        // Nao existe elemento para remover.
        if (vazia())
        {
            throw std::underflow_error("Erro: pilha vazia.");
        }

        // Basta diminuir a quantidade.
        // O elemento antigo continua fisicamente no array, mas fica fora
        // da parte valida da pilha e sera sobrescrito numa proxima insercao.
        --quantidade;
    }

    // Monta uma string com os elementos na ordem em que foram empilhados.
    std::string imprimir() const
    {
        std::stringstream resultado;
        resultado << "{ ";

        // Os elementos validos ocupam as posicoes de 0 ate quantidade - 1.
        for (int i = 0; i < quantidade; ++i)
        {
            resultado << elementos[i] << " ";
        }

        resultado << "}";
        return resultado.str();
    }
};

#endif // PILHA_H
