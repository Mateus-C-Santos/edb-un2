#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaDuplamenteEncadeada.h"
#include "ListaDuplamenteEncadeadaTestHelper.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using Lista = ListaDuplamenteEncadeada;
using Helper = ListaDuplamenteEncadeadaTestHelper;

// Verifica o estado pelo helper, sem depender das operações pendentes.
static void verificarEstado(const Lista& lista, std::initializer_list<std::string> esperados)
{
    REQUIRE(Helper::consistente(lista));
    CHECK(lista.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(Helper::quantidade(lista) == static_cast<int>(esperados.size()));
    CHECK(Helper::mesmosElementos(lista, esperados));
    std::vector<std::string> reversos(esperados);
    std::reverse(reversos.begin(), reversos.end());
    CHECK(Helper::elementosReversos(lista) == reversos);
}

TEST_CASE("Inserir início - lista vazia e sucessivas inserções")
{
    Lista lista;
    CHECK(lista.inserirInicio("P"));
    verificarEstado(lista, {"P"});
    CHECK(lista.inserirInicio("S"));
    verificarEstado(lista, {"S", "P"});
}

TEST_CASE("Inserir início - preserva a sequência preparada")
{
    Lista lista;
    Helper::preencherLista(lista, {"P", "F"});
    CHECK(lista.inserirInicio("S"));
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Inserir fim - lista vazia e sucessivas inserções")
{
    Lista lista;
    CHECK(lista.inserirFim("S"));
    verificarEstado(lista, {"S"});
    CHECK(lista.inserirFim("P"));
    verificarEstado(lista, {"S", "P"});
}

TEST_CASE("Inserir fim - preserva a sequência preparada")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P"});
    CHECK(lista.inserirFim("F"));
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Inserir posição - primeira posição em lista vazia")
{
    Lista lista;
    CHECK(lista.inserirNaPosicao(1, "S"));
    verificarEstado(lista, {"S"});
}

TEST_CASE("Inserir posição - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Início")
    {
        CHECK(lista.inserirNaPosicao(1, "C"));
        verificarEstado(lista, {"C", "S", "P", "F"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.inserirNaPosicao(2, "C"));
        verificarEstado(lista, {"S", "C", "P", "F"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.inserirNaPosicao(4, "C"));
        verificarEstado(lista, {"S", "P", "F", "C"});
    }
}

TEST_CASE("Inserir posição - índices inválidos preservam a lista")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        for (int posicao : {-1, 0, 2})
        {
            CAPTURE(posicao);
            CHECK_THROWS_AS(lista.inserirNaPosicao(posicao, "C"), std::out_of_range);
            verificarEstado(lista, {});
        }
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"S", "P"});
        for (int posicao : {-1, 0, 4})
        {
            CAPTURE(posicao);
            CHECK_THROWS_AS(lista.inserirNaPosicao(posicao, "C"), std::out_of_range);
            verificarEstado(lista, {"S", "P"});
        }
    }
}

TEST_CASE("Inserir antes - referência ausente preserva o estado")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        CHECK_FALSE(lista.inserirAntes("C", "F"));
        verificarEstado(lista, {});
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"S", "P"});
        CHECK_FALSE(lista.inserirAntes("C", "F"));
        verificarEstado(lista, {"S", "P"});
    }
}

TEST_CASE("Inserir antes - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Primeiro")
    {
        CHECK(lista.inserirAntes("C", "S"));
        verificarEstado(lista, {"C", "S", "P", "F"});
    }
    SUBCASE("Intermediário")
    {
        CHECK(lista.inserirAntes("C", "P"));
        verificarEstado(lista, {"S", "C", "P", "F"});
    }
    SUBCASE("Último")
    {
        CHECK(lista.inserirAntes("C", "F"));
        verificarEstado(lista, {"S", "P", "C", "F"});
    }
}

TEST_CASE("Inserir antes - usa a primeira ocorrência da referência")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "P", "F"});
    CHECK(lista.inserirAntes("C", "P"));
    verificarEstado(lista, {"S", "C", "P", "P", "F"});
}

TEST_CASE("Inserir ordenado - lista vazia")
{
    Lista lista;
    CHECK(lista.inserirOrdenado("P"));
    verificarEstado(lista, {"P"});
}

TEST_CASE("Inserir ordenado - mantém ordem decrescente")
{
    Lista lista;
    SUBCASE("Início")
    {
        Helper::preencherLista(lista, {"P", "F", "C"});
        CHECK(lista.inserirOrdenado("S"));
        verificarEstado(lista, {"S", "P", "F", "C"});
    }
    SUBCASE("Meio")
    {
        Helper::preencherLista(lista, {"S", "F", "C"});
        CHECK(lista.inserirOrdenado("P"));
        verificarEstado(lista, {"S", "P", "F", "C"});
    }
    SUBCASE("Fim")
    {
        Helper::preencherLista(lista, {"S", "P", "F"});
        CHECK(lista.inserirOrdenado("C"));
        verificarEstado(lista, {"S", "P", "F", "C"});
    }
}

TEST_CASE("Inserir ordenado - rejeita duplicatas sem alterar a lista")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F", "C"});
    for (const std::string elemento : {"S", "P", "F", "C"})
    {
        CAPTURE(elemento);
        CHECK_FALSE(lista.inserirOrdenado(elemento));
        verificarEstado(lista, {"S", "P", "F", "C"});
    }
}

TEST_CASE("Inserções comuns - aceitam repetição e valores distintos")
{
    Lista lista;
    Helper::preencherLista(lista, {"S"});
    SUBCASE("Início")
    {
        CHECK(lista.inserirInicio("S"));
        verificarEstado(lista, {"S", "S"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.inserirFim("C"));
        verificarEstado(lista, {"S", "C"});
    }
    SUBCASE("Posição")
    {
        CHECK(lista.inserirNaPosicao(2, "S"));
        verificarEstado(lista, {"S", "S"});
    }
    SUBCASE("Antes")
    {
        CHECK(lista.inserirAntes("S", "S"));
        verificarEstado(lista, {"S", "S"});
    }
}
