#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaDuplamenteEncadeada.h"
#include <stdexcept> 

TEST_CASE("buscar_e_mover - busca sem sucesso em lista vazia") 
{
    ListaDuplamenteEncadeada lista;

    REQUIRE(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
    REQUIRE_FALSE(lista.buscar_e_mover("X"));
}

TEST_CASE("buscar_e_mover - busca sem sucesso em lista não-vazia") 
{
    ListaDuplamenteEncadeada lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");

    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    REQUIRE_FALSE(lista.buscar_e_mover("X"));
}

TEST_CASE("buscar_e_mover - busca com sucesso, movendo um nó do meio da lista para o início") 
{
    ListaDuplamenteEncadeada lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");

    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    REQUIRE(lista.buscar_e_mover("F") == true);
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{F, S, P, C}");
    REQUIRE(lista.checarConsistencia() == OK);
}

TEST_CASE("buscar_e_mover - busca com sucesso, movendo o primeiro nó da lista para o início") 
{
    ListaDuplamenteEncadeada lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");

    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    REQUIRE(lista.buscar_e_mover("S") == true);
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    REQUIRE(lista.checarConsistencia() == OK);
}

TEST_CASE("buscar_e_mover - busca com sucesso, movendo o último nó da lista para o início") 
{
    ListaDuplamenteEncadeada lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");

    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{S, P, F, C}");
    REQUIRE(lista.buscar_e_mover("C") == true);
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "{C, S, P, F}");
    REQUIRE(lista.checarConsistencia() == OK);
}