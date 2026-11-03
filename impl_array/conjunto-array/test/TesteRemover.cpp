#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conjunto.h"
#include "ConjuntoTestHelper.h"

TEST_CASE("Conjunto - Remover de conjunto vazio retorna false")
{
    Conjunto conjunto(3);
    CHECK_FALSE(conjunto.remover(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Remover preserva os demais elementos")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    SUBCASE("Primeiro elemento")
    {
        CHECK(conjunto.remover(10));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {20, 30}));
    }
    SUBCASE("Elemento intermediário")
    {
        CHECK(conjunto.remover(20));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 30}));
    }
    SUBCASE("Último elemento")
    {
        CHECK(conjunto.remover(30));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 20}));
    }
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Remover elemento ausente não altera o estado")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    const auto antes = ConjuntoTestHelper::elementosAtivos(conjunto);

    CHECK_FALSE(conjunto.remover(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto) == antes);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Remover o único elemento deixa o conjunto vazio")
{
    Conjunto conjunto(1);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10});

    CHECK(conjunto.remover(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto).empty());
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 1);
}

TEST_CASE("Conjunto - Remover aceita zero e números negativos")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {-7, 0, 10});
    SUBCASE("Zero")
    {
        CHECK(conjunto.remover(0));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {-7, 10}));
    }
    SUBCASE("Negativo")
    {
        CHECK(conjunto.remover(-7));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {0, 10}));
    }
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Remover sucessivamente todos os elementos")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    CHECK(conjunto.remover(20));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 30}));
    CHECK(conjunto.remover(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 1);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {30}));
    CHECK(conjunto.remover(30));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto).empty());
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Remover ignora posições fora da quantidade ativa")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20});
    ConjuntoTestHelper::setElementoNaPosicao(conjunto, 2, 999);
    ConjuntoTestHelper::setElementoNaPosicao(conjunto, 3, 999);

    CHECK_FALSE(conjunto.remover(999));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 20}));
    CHECK(ConjuntoTestHelper::getElementoNaPosicao(conjunto, 2) == 999);
    CHECK(ConjuntoTestHelper::getElementoNaPosicao(conjunto, 3) == 999);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Remover com capacidade zero retorna false")
{
    Conjunto conjunto(0);
    CHECK_FALSE(conjunto.remover(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 0);
}
