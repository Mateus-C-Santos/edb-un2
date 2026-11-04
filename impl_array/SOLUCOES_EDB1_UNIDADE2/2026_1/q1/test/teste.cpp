#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Lista.h"
#include <doctest.h>
#include <stdexcept>
#include <string>

TEST_CASE("contarIntersecao - Lista this vazia deve retornar 0") 
{
    Lista atual;
    Lista outra;

    outra.inserirInicio("C");
    outra.inserirInicio("F");
    outra.inserirInicio("P");
    outra.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{}" );
    REQUIRE( atual.tamanho() == 0 );

    REQUIRE( outra.imprimir() == "{S, P, F, C}" );
    REQUIRE( outra.tamanho() == 4 );

    REQUIRE( atual.contarIntersecao(outra) == 0 );
}

TEST_CASE("contarIntersecao - Lista outra vazia deve retornar 0") 
{
    Lista atual;
    Lista outra;

    atual.inserirInicio("C");
    atual.inserirInicio("F");
    atual.inserirInicio("P");
    atual.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{}" );
    REQUIRE( outra.tamanho() == 0 );

    REQUIRE( atual.contarIntersecao(outra) == 0 );
}

TEST_CASE("contarIntersecao - Listas nao vazias sem intersecao deve retornar 0") 
{
    Lista atual;
    Lista outra;

    atual.inserirInicio("C");
    atual.inserirInicio("F");
    atual.inserirInicio("P");
    atual.inserirInicio("S");

    outra.inserirInicio("D");
    outra.inserirInicio("E");
    outra.inserirInicio("B");
    outra.inserirInicio("A");

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{A, B, E, D}" );
    REQUIRE( outra.tamanho() == 4 );

    REQUIRE( atual.contarIntersecao(outra) == 0 );
}

TEST_CASE("contarIntersecao - Listas nao vazias com intersecao sem elementos repetidos deve retornar quantidade de elementos em comum") 
{
    Lista atual;
    Lista outra;

    atual.inserirInicio("C");
    atual.inserirInicio("F");
    atual.inserirInicio("P");
    atual.inserirInicio("S");

    outra.inserirInicio("D");
    outra.inserirInicio("C");
    outra.inserirInicio("A");
    outra.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{S, A, C, D}" );
    REQUIRE( outra.tamanho() == 4 );

    REQUIRE( atual.contarIntersecao(outra) == 2 );
}