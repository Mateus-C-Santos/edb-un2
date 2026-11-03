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

TEST_CASE("Buscar - lista vazia retorna menos um")
{
    Lista lista;
    CHECK(lista.buscar("C") == -1);
    CHECK(lista.buscar("C") == -1);
    verificarEstado(lista, {});
}

TEST_CASE("Buscar - posições começam em um")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    const auto& leitura = lista;
    CHECK(leitura.buscar("S") == 1);
    CHECK(leitura.buscar("P") == 2);
    CHECK(leitura.buscar("F") == 3);
    CHECK(leitura.buscar("C") == -1);
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Buscar - retorna a primeira ocorrência de um valor repetido")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "P", "S"});
    CHECK(lista.buscar("S") == 1);
    CHECK(lista.buscar("P") == 2);
    verificarEstado(lista, {"S", "P", "P", "S"});
}

TEST_CASE("Buscar - localiza o valor C")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "C", "P"});
    CHECK(lista.buscar("C") == 2);
    verificarEstado(lista, {"S", "C", "P"});
}

TEST_CASE("Acesso - primeiro, último e todas as posições")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    const auto& leitura = lista;
    CHECK(leitura.primeiroElemento() == "S");
    CHECK(leitura.ultimoElemento() == "F");
    CHECK(leitura.elementoNaPosicao(1) == "S");
    CHECK(leitura.elementoNaPosicao(2) == "P");
    CHECK(leitura.elementoNaPosicao(3) == "F");
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Acesso - único elemento")
{
    Lista lista;
    Helper::preencherLista(lista, {"C"});
    CHECK(lista.primeiroElemento() == std::optional<std::string>{"C"});
    CHECK(lista.ultimoElemento() == std::optional<std::string>{"C"});
    CHECK(lista.elementoNaPosicao(1) == std::optional<std::string>{"C"});
    verificarEstado(lista, {"C"});
}

TEST_CASE("Acesso - lista vazia retorna nullopt")
{
    Lista lista;
    CHECK(lista.primeiroElemento() == std::nullopt);
    CHECK(lista.ultimoElemento() == std::nullopt);
    for (int posicao : {-1, 0, 1})
    {
        CAPTURE(posicao);
        CHECK(lista.elementoNaPosicao(posicao) == std::nullopt);
    }
    verificarEstado(lista, {});
}

TEST_CASE("Acesso - posições inválidas retornam nullopt e preservam o estado")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P"});
    for (int posicao : {-1, 0, 3, 4})
    {
        CAPTURE(posicao);
        CHECK(lista.elementoNaPosicao(posicao) == std::nullopt);
        verificarEstado(lista, {"S", "P"});
    }
}
