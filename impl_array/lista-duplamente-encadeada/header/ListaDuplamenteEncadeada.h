#ifndef LISTADUPLAMENTEENCADEADA_H
#define LISTADUPLAMENTEENCADEADA_H

#include "ConsistenciaStatus.h"
#include "No.h"
#include <string>
#include <optional>

class ListaDuplamenteEncadeada
{
    friend class ListaDuplamenteEncadeadaTestHelper;

public:
    ListaDuplamenteEncadeada();
    ~ListaDuplamenteEncadeada();

    bool inserirInicio(const std::string& elemento);
    bool inserirFim(const std::string& elemento);
    bool inserirNaPosicao(int posicao, const std::string& elemento);
    bool inserirAntes(const std::string& elemento, const std::string& referencia);
    bool inserirOrdenado(const std::string& elemento);

    std::string removerInicio();
    std::string removerFim();
    std::string removerNaPosicao(int posicao);
    int removerTodos(const std::string& elemento);

    int buscar(const std::string& elemento) const;
    std::optional<std::string> primeiroElemento() const;
    std::optional<std::string> ultimoElemento() const;
    std::optional<std::string> elementoNaPosicao(int posicao) const;

    int tamanho() const;
    bool vazia() const;
    std::string imprimir() const;
    ConsistenciaStatus checarConsistencia() const;

private:
    No<std::string>* cabeca;
    No<std::string>* cauda;
    int quantidade;
};

#endif
