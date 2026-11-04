#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Lista.h"
#include <string>
#include <stdexcept>

TEST_CASE("removerUltimaOcorrencia - Remoção em lista vazia deve retornar false") 
{
    Lista lista;
    REQUIRE( lista.imprimir() == "{}" );
    REQUIRE( lista.tamanho() == 0 );
    REQUIRE_FALSE( lista.removerUltimaOcorrencia("a") );
}

TEST_CASE("removerUltimaOcorrencia - Tentar remover valor que não existe na lista não altera a lista") 
{
    Lista lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");
    REQUIRE( lista.imprimir() == "{S, P, F, C}" );
    REQUIRE( lista.tamanho() == 4 );
    REQUIRE_FALSE( lista.removerUltimaOcorrencia("!") );
}

TEST_CASE("removerUltimaOcorrencia - Remover valor que só ocorre uma vez na lista") 
{
    Lista lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");
    REQUIRE( lista.imprimir() == "{S, P, F, C}" );
    REQUIRE( lista.tamanho() == 4 );
    REQUIRE( lista.removerUltimaOcorrencia("F") );
    REQUIRE( lista.imprimir() == "{S, P, C}" );
    REQUIRE( lista.tamanho() == 3 );
}

TEST_CASE("removerUltimaOcorrencia - Remover valor que só ocorre uma vez na lista, sendo o nó removido o primeiro da lista") 
{
    Lista lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("P");
    lista.inserirInicio("S");
    REQUIRE( lista.imprimir() == "{S, P, F, C}" );
    REQUIRE( lista.tamanho() == 4 );
    REQUIRE( lista.removerUltimaOcorrencia("S") );
    REQUIRE( lista.imprimir() == "{P, F, C}" );
    REQUIRE( lista.tamanho() == 3 );
}

TEST_CASE("removerUltimaOcorrencia - Remover valor que ocorre múltiplas vezes na lista, sendo o nó removido o último da lista") 
{
    Lista lista;
    lista.inserirInicio("S");
    lista.inserirInicio("C");
    lista.inserirInicio("S");
    lista.inserirInicio("F");
    lista.inserirInicio("S");
    lista.inserirInicio("P");
    lista.inserirInicio("S");
    REQUIRE( lista.imprimir() == "{S, P, S, F, S, C, S}" );
    REQUIRE( lista.tamanho() == 7 );
    REQUIRE( lista.removerUltimaOcorrencia("S") );
    REQUIRE( lista.imprimir() == "{S, P, S, F, S, C}" );
    REQUIRE( lista.tamanho() == 6 );
}

TEST_CASE("removerUltimaOcorrencia - Remover valor que ocorre múltiplas vezes na lista, sendo o nó removido um do meio da lista") 
{
    Lista lista;
    lista.inserirInicio("C");
    lista.inserirInicio("F");
    lista.inserirInicio("S");
    lista.inserirInicio("S");
    lista.inserirInicio("S");
    lista.inserirInicio("P");
    lista.inserirInicio("S");
    REQUIRE( lista.imprimir() == "{S, P, S, S, S, F, C}" );
    REQUIRE( lista.tamanho() == 7 );
    REQUIRE( lista.removerUltimaOcorrencia("S") );
    REQUIRE( lista.imprimir() == "{S, P, S, S, F, C}" );
    REQUIRE( lista.tamanho() == 6 );
}
