// -----------------------------------------------------------------------------
// Fila.h
// Implementacao de uma FILA usando um array circular.
//
// Uma fila segue a regra FIFO (First In, First Out):
// o PRIMEIRO elemento que entra e o PRIMEIRO que sai.
// Exemplo: enfileirar 10, 20 e 30 -> desenfileirar remove primeiro o 10.
// -----------------------------------------------------------------------------

#ifndef FILA_H
#define FILA_H

#include <optional>   // std::optional e std::nullopt
#include <sstream>    // std::stringstream, usado para montar a impressao
#include <stdexcept>  // Excecoes para fila cheia ou vazia
#include <string>

template <typename T>
class Fila
{
private:
    T* elementos;       // Array que armazena os elementos da fila.
    int capacidade;     // Numero maximo de elementos que cabem no array.
    int quantidade;     // Numero atual de elementos na fila.
    int inicio;         // Indice do elemento mais antigo (proximo a sair).
    int fim;            // Indice da proxima posicao livre (proxima entrada).

public:
    // Cria uma fila vazia. Inicio e fim comecam na primeira posicao do array.
    Fila(int cap)
        : elementos(nullptr), capacidade(cap), quantidade(0), inicio(0), fim(0)
    {
        if (cap <= 0)
        {
            throw std::invalid_argument("A capacidade da fila deve ser positiva.");
        }

        // Reserva o array que sera reutilizado de forma circular.
        elementos = new T[capacidade];
    }

    // Libera a memoria alocada no construtor.
    ~Fila()
    {
        delete[] elementos;
    }

    // Retorna o numero de elementos atualmente armazenados.
    int tamanho()
    {
        return quantidade;
    }

    // Consulta o primeiro elemento da fila, sem remove-lo.
    // Se a fila estiver vazia, retorna std::nullopt.
    std::optional<T> frente()
    {
        if (vazia())
        {
            return std::nullopt;
        }

        // inicio aponta para o elemento que entrou primeiro e ainda nao saiu.
        return elementos[inicio];
    }

    // Adiciona um elemento no FINAL da fila.
    void enfileirar(T elemento)
    {
        if (cheia())
        {
            throw std::overflow_error("Erro: fila cheia.");
        }

        // Guarda o novo elemento na posicao indicada por fim.
        elementos[fim] = elemento;

        // Avanca fim. O operador % faz o indice voltar para zero quando
        // chega ao final do array: isso e o comportamento de array circular.
        fim = (fim + 1) % capacidade;

        // A fila passou a ter mais um elemento.
        ++quantidade;
    }

    // Remove e RETORNA o elemento que esta no INICIO da fila.
    T desenfileirar()
    {
        if (vazia())
        {
            throw std::underflow_error("Erro: fila vazia.");
        }

        // Primeiro guardamos o valor, pois o indice inicio sera avancado.
        T elementoRemovido = elementos[inicio];

        // O proximo elemento passa a ser o inicio da fila.
        // O modulo permite voltar ao indice zero ao chegar ao fim do array.
        inicio = (inicio + 1) % capacidade;

        // Agora ha um elemento a menos na fila.
        --quantidade;

        // Retorna o valor que foi retirado.
        return elementoRemovido;
    }

    // Verifica se todos os espacos do array estao ocupados.
    bool cheia()
    {
        return quantidade == capacidade;
    }

    // Verifica se nao ha nenhum elemento armazenado.
    bool vazia()
    {
        return quantidade == 0;
    }

    // Imprime os elementos do mais antigo para o mais recente.
    std::string imprimir()
    {
        std::stringstream resultado;
        resultado << "{ ";

        // Nao podemos percorrer simplesmente de 0 ate quantidade - 1,
        // pois os elementos podem estar espalhados depois de uma volta.
        // Comecamos em inicio e percorremos exatamente quantidade posicoes.
        int indice = inicio;
        for (int contador = 0; contador < quantidade; ++contador)
        {
            resultado << elementos[indice] << " ";

            // Avanca circularmente para a proxima posicao.
            indice = (indice + 1) % capacidade;
        }

        resultado << "}";
        return resultado.str();
    }
};

#endif // FILA_H
