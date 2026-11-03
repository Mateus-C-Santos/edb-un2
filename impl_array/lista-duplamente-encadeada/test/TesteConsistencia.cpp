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

TEST_CASE("Consistência - estados válidos, incluindo duplicatas")
{
    Lista lista;
    verificarEstado(lista, {});
    Helper::preencherLista(lista, {"S"});
    verificarEstado(lista, {"S"});
    Helper::preencherLista(lista, {"S", "S", "P"});
    verificarEstado(lista, {"S", "S", "P"});
}

TEST_CASE("Consistência - contador incorreto ou negativo")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P"});
    for (int quantidade : {-1, 0, 1, 3})
    {
        CAPTURE(quantidade);
        {
            auto restaurar = Helper::alterarQuantidadeTemporariamente(lista, quantidade);
            CHECK(lista.checarConsistencia() == ConsistenciaStatus::QUANTIDADE_INCORRETA);
            CHECK_FALSE(Helper::consistente(lista));
        }
        verificarEstado(lista, {"S", "P"});
    }
}

TEST_CASE("Consistência - lista vazia com contador diferente de zero")
{
    Lista lista;
    {
        auto restaurar = Helper::alterarQuantidadeTemporariamente(lista, 1);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::QUANTIDADE_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {});
}

TEST_CASE("Consistência - extremidade final incorreta")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    {
        auto restaurar = Helper::alterarExtremidadeFinalTemporariamente(lista, 1);
        CHECK(lista.checarConsistencia() != ConsistenciaStatus::OK);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - detecta autociclo em proximo")
{
    Lista lista;
    Helper::preencherLista(lista, {"S"});
    {
        auto restaurar = Helper::alterarProximoTemporariamente(lista, 1, 1);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S"});
}

TEST_CASE("Consistência - detecta ciclo com vários nós")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Retorno ao início")
    {
        auto restaurar = Helper::alterarProximoTemporariamente(lista, 3, 1);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    SUBCASE("Ciclo interno")
    {
        auto restaurar = Helper::alterarProximoTemporariamente(lista, 3, 2);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - detecta ciclos somente em anterior")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    SUBCASE("Autociclo")
    {
        auto restaurar = Helper::alterarAnteriorTemporariamente(lista, 1, 1);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    SUBCASE("Ciclo com vários nós")
    {
        auto restaurar = Helper::alterarAnteriorTemporariamente(lista, 1, 3);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - encadeamento anterior não recíproco")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    {
        auto restaurar = Helper::alterarAnteriorTemporariamente(lista, 2, 0);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::ENCADEAMENTO_INCORRETO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - sentinelas ausentes")
{
    Lista lista;
    SUBCASE("Cabeça")
    {
        auto restaurar = Helper::alterarCabecaTemporariamente(lista);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::SENTINELA_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    SUBCASE("Cauda")
    {
        auto restaurar = Helper::alterarCaudaTemporariamente(lista);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::SENTINELA_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {});
}

TEST_CASE("Consistência - detecta ciclos que envolvem sentinelas")
{
    Lista lista;
    SUBCASE("Anterior da cabeça aponta para ela mesma")
    {
        auto restaurar = Helper::alterarAnteriorCabecaTemporariamente(lista);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
    }
    SUBCASE("Próximo da cauda aponta para ela mesma")
    {
        auto restaurar = Helper::alterarProximoCaudaTemporariamente(lista);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
    }
    verificarEstado(lista, {});
}

TEST_CASE("Consistência - cauda precisa ser alcançável")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    {
        auto restaurar = Helper::alterarProximoTemporariamente(lista, 3, 0);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::ENCADEAMENTO_INCORRETO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - primeira ligação não pode ser nula com elementos")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P"});
    {
        auto restaurar = Helper::alterarExtremidadeInicialTemporariamente(lista);
        CHECK(lista.checarConsistencia() != ConsistenciaStatus::OK);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P"});
}

TEST_CASE("Consistência - detecta ciclo mesmo com contador incorreto")
{
    Lista lista;
    Helper::preencherLista(lista, {"S", "P", "F"});
    {
        auto restaurarProximo = Helper::alterarProximoTemporariamente(lista, 3, 1);
        auto restaurarQuantidade = Helper::alterarQuantidadeTemporariamente(lista, 0);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::CICLO_DETECTADO);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {"S", "P", "F"});
}

TEST_CASE("Consistência - sentinelas não podem coincidir")
{
    Lista lista;
    {
        auto restaurar = Helper::coincidirSentinelasTemporariamente(lista);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::SENTINELA_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {});
}

TEST_CASE("Consistência - sentinelas não podem ter ligações externas mesmo sem ciclos")
{
    Lista lista;
    No<std::string> externo("C");
    SUBCASE("Anterior da cabeça")
    {
        auto restaurar = Helper::alterarAnteriorCabecaTemporariamente(lista, &externo);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::SENTINELA_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    SUBCASE("Próximo da cauda")
    {
        auto restaurar = Helper::alterarProximoCaudaTemporariamente(lista, &externo);
        CHECK(lista.checarConsistencia() == ConsistenciaStatus::SENTINELA_INCORRETA);
        CHECK_FALSE(Helper::consistente(lista));
    }
    verificarEstado(lista, {});
}
