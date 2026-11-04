#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Pilha.h"
#include <string>

TEST_CASE("Tamanho inicial da pilha deve ser zero") {
    Pilha<int> pilha(10);
    CHECK(pilha.tamanho() == 0);
}

TEST_CASE("Empilhar elementos até a capacidade máxima") {
    Pilha<int> pilha(3);

    pilha.empilhar(10);
    pilha.empilhar(20);
    pilha.empilhar(30);

    CHECK(pilha.tamanho() == 3);
    CHECK(pilha.topo() == 30);
}

TEST_CASE("Empilhar além da capacidade deve lançar exceção") {
    Pilha<int> pilha(2);

    pilha.empilhar(1);
    pilha.empilhar(2);

    CHECK_THROWS_AS(pilha.empilhar(3), std::overflow_error);
}

TEST_CASE("Desempilhar retorna elementos na ordem inversa") {
    Pilha<int> pilha(3);

    pilha.empilhar(5);
    pilha.empilhar(10);
    pilha.empilhar(15);

    CHECK(pilha.topo() == 15);
    pilha.desempilhar();

    CHECK(pilha.topo() == 10);
    pilha.desempilhar();

    CHECK(pilha.topo() == 5);
    pilha.desempilhar();
    
    CHECK(pilha.tamanho() == 0);
}

TEST_CASE("Desempilhar de pilha vazia deve lançar exceção") {
    Pilha<int> pilha(2);
    CHECK_THROWS_AS(pilha.desempilhar(), std::underflow_error);
}

TEST_CASE("Topo da pilha após operações de empilhar/desempilhar") {
    Pilha<std::string> pilha(5);

    pilha.empilhar("S");
    CHECK(pilha.topo() == "S");

    pilha.empilhar("P");
    CHECK(pilha.topo() == "P");

    pilha.desempilhar();
    CHECK(pilha.topo() == "S");
}

TEST_CASE("Topo de pilha vazia retorna nullopt") {
    Pilha<double> pilha(2);
    CHECK(pilha.topo() == std::nullopt);
}

TEST_CASE("Impressão da pilha deve refletir os elementos empilhados") {
    Pilha<int> pilha(4);
    pilha.empilhar(1);
    pilha.empilhar(2);
    pilha.empilhar(3);
    
    auto resultado = pilha.imprimir();

    CHECK(resultado == "{ 1 2 3 }");
}

TEST_CASE("Testando com diferentes tipos de dados (double, string)") {
    Pilha<double> pilhaDouble(2);
    pilhaDouble.empilhar(3.14);
    REQUIRE(pilhaDouble.topo().has_value());
    CHECK(*pilhaDouble.topo() == doctest::Approx(3.14));

    Pilha<std::string> pilhaStr(2);
    pilhaStr.empilhar("F");
    pilhaStr.empilhar("C");
    CHECK(pilhaStr.topo() == "C");
}