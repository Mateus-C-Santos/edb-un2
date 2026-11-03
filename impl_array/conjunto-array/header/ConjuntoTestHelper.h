#ifndef CONJUNTO_TEST_HELPER_H
#define CONJUNTO_TEST_HELPER_H

#include "Conjunto.h"
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <vector>

// Acesso exclusivo dos testes: prepara estados sem chamar as operações do aluno.
class ConjuntoTestHelper
{
public:
    static int capacidade(const Conjunto& conjunto)
    {
        return conjunto.capacidade;
    }

    static int quantidade(const Conjunto& conjunto)
    {
        return conjunto.quantidade;
    }

    static int getElementoNaPosicao(const Conjunto& conjunto, int posicao)
    {
        validarPosicao(conjunto, posicao);
        return conjunto.elementos[posicao];
    }

    static void setElementoNaPosicao(Conjunto& conjunto, int posicao, int elemento)
    {
        validarPosicao(conjunto, posicao);
        conjunto.elementos[posicao] = elemento;
    }

    static void setQuantidade(Conjunto& conjunto, int quantidade)
    {
        if (quantidade < 0 || quantidade > conjunto.capacidade)
        {
            throw std::out_of_range("Quantidade fora da capacidade do conjunto.");
        }
        conjunto.quantidade = quantidade;
    }

    static void preencherConjunto(Conjunto& conjunto, std::initializer_list<int> dados)
    {
        if (dados.size() > static_cast<std::size_t>(conjunto.capacidade))
        {
            throw std::out_of_range("Elementos excedem a capacidade do conjunto.");
        }
        std::copy(dados.begin(), dados.end(), conjunto.elementos);
        conjunto.quantidade = static_cast<int>(dados.size());
    }

    static std::vector<int> elementosAtivos(const Conjunto& conjunto)
    {
        if (conjunto.quantidade < 0 || conjunto.quantidade > conjunto.capacidade)
        {
            throw std::out_of_range("Quantidade interna inválida.");
        }
        return {conjunto.elementos, conjunto.elementos + conjunto.quantidade};
    }

    // Compara também a multiplicidade: elementos duplicados não passam despercebidos.
    static bool mesmosElementos(const Conjunto& conjunto, std::initializer_list<int> esperados)
    {
        const auto atuais = elementosAtivos(conjunto);
        return std::is_permutation(atuais.begin(), atuais.end(), esperados.begin(), esperados.end());
    }

private:
    static void validarPosicao(const Conjunto& conjunto, int posicao)
    {
        if (posicao < 0 || posicao >= conjunto.capacidade)
        {
            throw std::out_of_range("Posição fora da capacidade do conjunto.");
        }
    }
};

#endif
