#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../lib/doctest.h"
#include "Lista.h"
#include <string>
#include <stdexcept>

TEST_CASE("1. Lista vazia") {
    Lista lista;
    CHECK(lista.removerTodos("x") == 0);
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("2. Lista com um único nó igual ao valor") {
    Lista lista;
    lista.inserirInicio("a");
    CHECK(lista.removerTodos("a") == 1);
    CHECK(lista.tamanho() == 0);
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("3. Lista com um único nó diferente do valor") {
    Lista lista;
    lista.inserirInicio("a");
    CHECK(lista.removerTodos("b") == 0);
    CHECK(lista.tamanho() == 1);
    CHECK(lista.primeiroElemento() == "a");
    CHECK(lista.ultimoElemento() == "a");
}

TEST_CASE("4. Todos os elementos são iguais ao valor") {
    Lista lista;
    lista.inserirInicio("x");
    lista.inserirInicio("x");
    lista.inserirInicio("x");
    lista.inserirInicio("x");
    CHECK(lista.removerTodos("x") == 4);
    CHECK(lista.tamanho() == 0);
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("5. Nenhum elemento igual ao valor") {
    Lista lista;
    lista.inserirInicio("d");
    lista.inserirInicio("c");
    lista.inserirInicio("b");
    lista.inserirInicio("a");
    CHECK(lista.removerTodos("z") == 0);
    CHECK(lista.tamanho() == 4);
    CHECK(lista.primeiroElemento() == "a");
    CHECK(lista.ultimoElemento() == "d");
}

TEST_CASE("6. Vários nós com o valor alternados") {
    Lista lista;
    lista.inserirInicio("i");
    lista.inserirInicio("x");
    lista.inserirInicio("h");
    lista.inserirInicio("x");
    lista.inserirInicio("g");
    lista.inserirInicio("x");
    lista.inserirInicio("f");
    CHECK(lista.removerTodos("x") == 3);
    CHECK(lista.tamanho() == 4);
    CHECK(lista.primeiroElemento() == "f");
    CHECK(lista.ultimoElemento() == "i");
}

TEST_CASE("7. Valor no início da lista") {
    Lista lista;
    lista.inserirInicio("d");
    lista.inserirInicio("b");
    lista.inserirInicio("a");
    lista.inserirInicio("x");
    CHECK(lista.removerTodos("x") == 1);
    CHECK(lista.tamanho() == 3);
    CHECK(lista.primeiroElemento() == "a");
    CHECK(lista.ultimoElemento() == "d");
}

TEST_CASE("8. Valor no final da lista") {
    Lista lista;
    lista.inserirInicio("x");
    lista.inserirInicio("c");
    lista.inserirInicio("b");
    lista.inserirInicio("a");
    CHECK(lista.removerTodos("x") == 1);
    CHECK(lista.tamanho() == 3);
    CHECK(lista.primeiroElemento() == "a");
    CHECK(lista.ultimoElemento() == "c");
}

TEST_CASE("9. Valor aparece uma vez no meio") {
    Lista lista;
    lista.inserirInicio("d");
    lista.inserirInicio("x");
    lista.inserirInicio("b");
    lista.inserirInicio("a");
    CHECK(lista.removerTodos("x") == 1);
    CHECK(lista.tamanho() == 3);
    CHECK(lista.primeiroElemento() == "a");
    CHECK(lista.ultimoElemento() == "d");
}
