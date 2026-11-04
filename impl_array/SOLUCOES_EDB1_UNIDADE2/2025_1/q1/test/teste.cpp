#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"
#include "../header/Lista.h"

Lista criarLista() {
    Lista lista;
    lista.inserirInicio("A");
    lista.inserirInicio("B");
    lista.inserirInicio("C");
    lista.inserirInicio("D");
    return lista;
}

TEST_CASE("Move o primeiro nó para o início") {
    Lista lista = criarLista();
    REQUIRE(lista.imprimir() == "D<->C<->B<->A");
    CHECK(lista.moverParaInicio("D") == true);
    CHECK(lista.imprimir() == "D<->C<->B<->A");
}

TEST_CASE("Move o último nó para o início") {
    Lista lista = criarLista();
    REQUIRE(lista.imprimir() == "D<->C<->B<->A");
    CHECK(lista.moverParaInicio("A") == true);
    CHECK(lista.imprimir() == "A<->D<->C<->B");
}

TEST_CASE("Move nó do meio para o início") {
    Lista lista = criarLista();
    REQUIRE(lista.imprimir() == "D<->C<->B<->A");
    CHECK(lista.moverParaInicio("C") == true);
    CHECK(lista.imprimir() == "C<->D<->B<->A");
}

TEST_CASE("Tenta mover nó inexistente para o início") {
    Lista lista = criarLista();
    REQUIRE(lista.imprimir() == "D<->C<->B<->A");
    CHECK(lista.moverParaInicio("X") == false);
    CHECK(lista.imprimir() == "D<->C<->B<->A");
}
