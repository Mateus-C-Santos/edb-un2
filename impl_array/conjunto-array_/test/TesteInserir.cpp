#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conjunto.h"
#include "ConjuntoTestHelper.h"

TEST_CASE("Conjunto - Inserir em conjunto vazio")
{
    Conjunto conjunto(3);
    CHECK(conjunto.inserir(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 1);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10}));
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Inserir preserva os elementos existentes")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20});

    CHECK(conjunto.inserir(30));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 20, 30}));
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Inserir duplicata não altera o estado")
{
    Conjunto conjunto(4);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    const auto antes = ConjuntoTestHelper::elementosAtivos(conjunto);
    int duplicado = 10;
    SUBCASE("Primeiro elemento") { duplicado = 10; }
    SUBCASE("Elemento intermediário") { duplicado = 20; }
    SUBCASE("Último elemento") { duplicado = 30; }

    CHECK_FALSE(conjunto.inserir(duplicado));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto) == antes);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 4);
}

TEST_CASE("Conjunto - Inserir ocupa a última vaga")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20});

    CHECK(conjunto.inserir(30));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 20, 30}));
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Inserir em conjunto cheio não altera o estado")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10, 20, 30});
    const auto antes = ConjuntoTestHelper::elementosAtivos(conjunto);
    int elemento = 40;
    SUBCASE("Elemento novo") { elemento = 40; }
    SUBCASE("Elemento duplicado") { elemento = 20; }

    CHECK_FALSE(conjunto.inserir(elemento));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 3);
    CHECK(ConjuntoTestHelper::elementosAtivos(conjunto) == antes);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Inserir aceita zero e números negativos")
{
    Conjunto conjunto(3);
    ConjuntoTestHelper::preencherConjunto(conjunto, {10});
    SUBCASE("Zero")
    {
        CHECK(conjunto.inserir(0));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, 0}));
    }
    SUBCASE("Negativo")
    {
        CHECK(conjunto.inserir(-7));
        CHECK(ConjuntoTestHelper::mesmosElementos(conjunto, {10, -7}));
    }
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 2);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 3);
}

TEST_CASE("Conjunto - Inserir com capacidade zero retorna false")
{
    Conjunto conjunto(0);
    CHECK_FALSE(conjunto.inserir(10));
    CHECK(ConjuntoTestHelper::quantidade(conjunto) == 0);
    CHECK(ConjuntoTestHelper::capacidade(conjunto) == 0);
}
