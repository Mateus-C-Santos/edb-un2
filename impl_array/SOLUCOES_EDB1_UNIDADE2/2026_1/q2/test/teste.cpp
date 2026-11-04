#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "ListaDuplamenteEncadeada.h"
#include <doctest.h>
#include <stdexcept>
#include <string>

TEST_CASE("removerIntersecao - Lista this vazia e outra nao vazia deve retornar 0")
{
    ListaDuplamenteEncadeada atual;
    ListaDuplamenteEncadeada outra;

    outra.inserirInicio("C");
    outra.inserirInicio("F");
    outra.inserirInicio("P");
    outra.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{}" );
    REQUIRE( atual.tamanho() == 0 );

    REQUIRE( outra.imprimir() == "{S, P, F, C}" );
    REQUIRE( outra.tamanho() == 4 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.removerIntersecao(outra) == 0 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.imprimir() == "{}" );
    REQUIRE( atual.tamanho() == 0 );

    REQUIRE( outra.imprimir() == "{S, P, F, C}" );
    REQUIRE( outra.tamanho() == 4 );
}

TEST_CASE("removerIntersecao - Lista this nao vazia e outra vazia deve retornar 0")
{
    ListaDuplamenteEncadeada atual;
    ListaDuplamenteEncadeada outra;

    atual.inserirInicio("C");
    atual.inserirInicio("F");
    atual.inserirInicio("P");
    atual.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{}" );
    REQUIRE( outra.tamanho() == 0 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.removerIntersecao(outra) == 0 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{}" );
    REQUIRE( outra.tamanho() == 0 );
}

TEST_CASE("removerIntersecao - Listas nao vazias sem intersecao deve retornar 0")
{
    ListaDuplamenteEncadeada atual;
    ListaDuplamenteEncadeada outra;

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

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.removerIntersecao(outra) == 0 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{A, B, E, D}" );
    REQUIRE( outra.tamanho() == 4 );
}

TEST_CASE("removerIntersecao - Listas nao vazias com intersecao deve remover alguns nos da lista this")
{
    ListaDuplamenteEncadeada atual;
    ListaDuplamenteEncadeada outra;

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

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.removerIntersecao(outra) == 2 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.imprimir() == "{P, F}" );
    REQUIRE( atual.tamanho() == 2 );

    REQUIRE( outra.imprimir() == "{S, A, C, D}" );
    REQUIRE( outra.tamanho() == 4 );
}

TEST_CASE("removerIntersecao - Listas nao vazias com intersecao deve remover todos os nos da lista this")
{
    ListaDuplamenteEncadeada atual;
    ListaDuplamenteEncadeada outra;

    atual.inserirInicio("C");
    atual.inserirInicio("F");
    atual.inserirInicio("P");
    atual.inserirInicio("S");

    outra.inserirInicio("A");
    outra.inserirInicio("C");
    outra.inserirInicio("F");
    outra.inserirInicio("P");
    outra.inserirInicio("S");

    REQUIRE( atual.imprimir() == "{S, P, F, C}" );
    REQUIRE( atual.tamanho() == 4 );

    REQUIRE( outra.imprimir() == "{S, P, F, C, A}" );
    REQUIRE( outra.tamanho() == 5 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.removerIntersecao(outra) == 4 );

    CHECK( atual.checarConsistencia() == StatusDaLista::OK );
    CHECK( outra.checarConsistencia() == StatusDaLista::OK );

    REQUIRE( atual.imprimir() == "{}" );
    REQUIRE( atual.tamanho() == 0 );

    REQUIRE( outra.imprimir() == "{S, P, F, C, A}" );
    REQUIRE( outra.tamanho() == 5 );
}