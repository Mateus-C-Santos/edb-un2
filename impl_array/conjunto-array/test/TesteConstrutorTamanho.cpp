#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conjunto.h"
#include "ConjuntoTestHelper.h"

TEST_CASE("Conjunto - Construtor estabelece capacidade e estado vazio")
{
    for (const int capacidade : {0, 1, 5})
    {
        CAPTURE(capacidade);
        Conjunto conjunto(capacidade);
        CHECK(ConjuntoTestHelper::capacidade(conjunto) == capacidade);
        CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
        CHECK(conjunto.tamanho() == 0);
        CHECK(ConjuntoTestHelper::elementosAtivos(conjunto).empty());

        // Escritas dentro da capacidade também são verificadas pelos sanitizadores.
        if (capacidade > 0)
        {
            ConjuntoTestHelper::setElementoNaPosicao(conjunto, 0, 10);
            ConjuntoTestHelper::setElementoNaPosicao(conjunto, capacidade - 1, 20);
            CHECK(ConjuntoTestHelper::getElementoNaPosicao(conjunto, capacidade - 1) == 20);
        }
    }
}

TEST_CASE("Conjunto - Construtor rejeita capacidade negativa")
{
    CHECK_THROWS_AS(Conjunto(-1), std::invalid_argument);
}

TEST_CASE("Conjunto - Tamanho reflete a quantidade interna")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30, 40});
    const auto& leitura = conjunto;

    for (const int quantidade : {0, 1, 2, 3, 4})
    {
        CAPTURE(quantidade);
        ConjuntoTestHelper::setQuantidade(conjunto, quantidade);
        CHECK(leitura.tamanho() == quantidade);
        CHECK(ConjuntoTestHelper::quantidade(conjunto) == quantidade);
        CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
    }
}
