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

TEST_CASE("Lista - Construtor estabelece uma lista vazia consistente")
{
    Lista lista;
    verificarEstado(lista, {});
    CHECK(lista.tamanho() == 0);
    CHECK(lista.vazia());
    CHECK(lista.imprimir() == "{}");
    CHECK(lista.primeiroElemento() == std::nullopt);
    CHECK(lista.ultimoElemento() == std::nullopt);
}

TEST_CASE("Lista - Tamanho, impressão e extremidades refletem os dados preparados")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    verificarEstado(lista, {"S", "P", "F"});
    CHECK(lista.tamanho() == 3);
    CHECK_FALSE(lista.vazia());
    CHECK(lista.primeiroElemento() == "S");
    CHECK(lista.ultimoElemento() == "F");
    CHECK(lista.imprimir() == "{S, P, F}");
}

TEST_CASE("Lista - Lista com um elemento")
{
    Lista lista;
    Helper::preencherLista(lista, {"C"});
    verificarEstado(lista, {"C"});
    CHECK(lista.tamanho() == 1);
    CHECK_FALSE(lista.vazia());
    CHECK(lista.primeiroElemento() == std::optional<std::string>{"C"});
    CHECK(lista.ultimoElemento() == std::optional<std::string>{"C"});
}

TEST_CASE("Lista - Helper pode substituir os dados e voltar ao estado vazio")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "S", "P"});
    verificarEstado(lista, {"S", "S", "P"});
    Helper::preencherLista(lista, {"C"});
    verificarEstado(lista, {"C"});
    Helper::preencherLista(lista, {});
    verificarEstado(lista, {});
    CHECK(lista.tamanho() == 0);
    CHECK(lista.vazia());
}
