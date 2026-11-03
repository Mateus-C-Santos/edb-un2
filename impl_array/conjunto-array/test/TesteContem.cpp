#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conjunto.h"
#include "ConjuntoTestHelper.h"

TEST_CASE("Conjunto - Contem em conjunto vazio")
{
    Conjunto conjunto(3);
    CHECK_FALSE(conjunto.contem(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Contem encontra elementos em todas as posições")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {-7, 0, 10});
    const auto antes = ConjuntoTestHelper::elementosAtivos(conjunto);
    const auto& leitura = conjunto;

    for (const int elemento : {-7, 0, 10})
    {
        CAPTURE(elemento);
        CHECK(leitura.contem(elemento));
    }
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto) == antes);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Contem não encontra elemento ausente")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    const auto antes = ConjuntoTestHelper::elementosAtivos(conjunto);

    CHECK_FALSE(conjunto.contem(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto) == antes);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Contem ignora posições fora da quantidade ativa")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20});
    ConjuntoTestHelper::setElementoNaPosicao(conjunto, 2, 999);
    ConjuntoTestHelper::setElementoNaPosicao(conjunto, 3, 999);

    CHECK_FALSE(conjunto.contem(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 20}));
    CHECK(ConjuntoTestHelper::getElementoNaPosicao(conjunto, 2) == 999);
    CHECK(ConjuntoTestHelper::getElementoNaPosicao(conjunto, 3) == 999);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Contem com capacidade zero retorna false")
{
    Conjunto conjunto(0);
    CHECK_FALSE(conjunto.contem(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 0);
}
