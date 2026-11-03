#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaSimplesmenteEncadeada.h"
#include "ListaSimplesmenteEncadeadaTestHelper.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using Lista = ListaSimplesmenteEncadeada;
using Helper = ListaSimplesmenteEncadeadaTestHelper;

// Verifica o estado pelo helper, sem depender das operações pendentes.
static void verificarEstado(const Lista& lista, std::initializer_list<std::string> esperados)
{
    REQUIRE(lista.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(Helper::quantidade(lista) == static_cast<int>(esperados.size()));
    CHECK(Helper::mesmosElementos(lista, esperados));
    std::vector<std::string> reversos(esperados);
    std::reverse(reversos.begin(), reversos.end());
    CHECK(Helper::elementosReversos(lista) == reversos);
}

TEST_CASE("Remover - lista vazia lança out_of_range")
{
    Lista lista;
    SUBCASE("Início") { CHECK_THROWS_AS(lista.removerInicio(), std::out_of_range); }
    SUBCASE("Fim") { CHECK_THROWS_AS(lista.removerFim(), std::out_of_range); }
    SUBCASE("Posição") { CHECK_THROWS_AS(lista.removerNaPosicao(1), std::out_of_range); }
    verificarEstado(lista, {});
}

TEST_CASE("Remover - único elemento atualiza as extremidades")
{
    Lista lista;
    Helper::preencherLista(lista, {"S"});
    SUBCASE("Início") { CHECK(lista.removerInicio() == "S"); }
    SUBCASE("Fim") { CHECK(lista.removerFim() == "S"); }
    SUBCASE("Posição") { CHECK(lista.removerNaPosicao(1) == "S"); }
    verificarEstado(lista, {});
}

TEST_CASE("Remover início - preserva a sequência restante")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    CHECK(lista.removerInicio() == "S");
    verificarEstado(lista, {"P", "F"});
}

TEST_CASE("Remover fim - preserva a sequência restante")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    CHECK(lista.removerFim() == "F");
    verificarEstado(lista, {"S", "P"});
}

TEST_CASE("Remover posição - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Início")
    {
        CHECK(lista.removerNaPosicao(1) == "S");
        verificarEstado(lista, {"P", "F"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.removerNaPosicao(2) == "P");
        verificarEstado(lista, {"S", "F"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerNaPosicao(3) == "F");
        verificarEstado(lista, {"S", "P"});
    }
}

TEST_CASE("Remover posição - índices inválidos preservam o estado")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P"});
    for (int posicao : {-1, 0, 3, 4})
    {
        CAPTURE(posicao);
        CHECK_THROWS_AS(lista.removerNaPosicao(posicao), std::out_of_range);
        verificarEstado(lista, {"S", "P"});
    }
}

TEST_CASE("Remover - sucessivas remoções até esvaziar")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Somente início")
    {
        CHECK(lista.removerInicio() == "S"); verificarEstado(lista, {"P", "F"});
        CHECK(lista.removerInicio() == "P"); verificarEstado(lista, {"F"});
        CHECK(lista.removerInicio() == "F"); verificarEstado(lista, {});
    }
    SUBCASE("Somente fim")
    {
        CHECK(lista.removerFim() == "F"); verificarEstado(lista, {"S", "P"});
        CHECK(lista.removerFim() == "P"); verificarEstado(lista, {"S"});
        CHECK(lista.removerFim() == "S"); verificarEstado(lista, {});
    }
    SUBCASE("Somente posição")
    {
        CHECK(lista.removerNaPosicao(2) == "P"); verificarEstado(lista, {"S", "F"});
        CHECK(lista.removerNaPosicao(2) == "F"); verificarEstado(lista, {"S"});
        CHECK(lista.removerNaPosicao(1) == "S"); verificarEstado(lista, {});
    }
}

TEST_CASE("Remover todos - vazia e elemento ausente retornam zero")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        CHECK(lista.removerTodos("C") == 0);
        verificarEstado(lista, {});
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"S", "P", "S"});
        CHECK(lista.removerTodos("C") == 0);
        verificarEstado(lista, {"S", "P", "S"});
    }
}

TEST_CASE("Remover todos - ocorrências consecutivas no início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "S", "P", "P", "F", "F"});
    SUBCASE("Início")
    {
        CHECK(lista.removerTodos("S") == 2);
        verificarEstado(lista, {"P", "P", "F", "F"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.removerTodos("P") == 2);
        verificarEstado(lista, {"S", "S", "F", "F"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerTodos("F") == 2);
        verificarEstado(lista, {"S", "S", "P", "P"});
    }
}

TEST_CASE("Remover todos - ocorrências separadas em todas as posições")
{
    Lista lista;
    Helper::preencherLista(lista, {"C", "S", "C", "P", "C"});
    CHECK(lista.removerTodos("C") == 3);
    verificarEstado(lista, {"S", "P"});
}

TEST_CASE("Remover todos - todas as ocorrências e único elemento")
{
    Lista lista;
    SUBCASE("Único")
    {
        Helper::preencherLista(lista, {"S"});
        CHECK(lista.removerTodos("S") == 1);
    }
    SUBCASE("Vários")
    {
        Helper::preencherLista(lista, {"S", "S", "S"});
        CHECK(lista.removerTodos("S") == 3);
    }
    verificarEstado(lista, {});
}

TEST_CASE("Remover - remove o valor C")
{
    Lista lista;
    Helper::preencherLista(lista, {"C", "S", "C"});
    SUBCASE("Início")
    {
        CHECK(lista.removerInicio() == "C");
        verificarEstado(lista, {"S", "C"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerFim() == "C");
        verificarEstado(lista, {"C", "S"});
    }
    SUBCASE("Posição")
    {
        CHECK(lista.removerNaPosicao(1) == "C");
        verificarEstado(lista, {"S", "C"});
    }
    SUBCASE("Todos")
    {
        CHECK(lista.removerTodos("C") == 2);
        verificarEstado(lista, {"S"});
    }
}
