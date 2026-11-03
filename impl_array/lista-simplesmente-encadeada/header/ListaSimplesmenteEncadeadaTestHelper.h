#ifndef LISTASIMPLESMENTEENCADEADATESTHELPER_H
#define LISTASIMPLESMENTEENCADEADATESTHELPER_H

#include "ListaSimplesmenteEncadeada.h"
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

class ListaSimplesmenteEncadeadaTestHelper
{
public:
    // A restauração ocorre mesmo se um REQUIRE interromper o caso de teste.
    template <typename T>
    class AlteracaoTemporaria
    {
    public:
        AlteracaoTemporaria(T& atributo, T novoValor)
            : atributo(atributo), original(atributo)
        {
            atributo = novoValor;
        }
        ~AlteracaoTemporaria() { atributo = original; }
        AlteracaoTemporaria(const AlteracaoTemporaria&) = delete;
        AlteracaoTemporaria& operator=(const AlteracaoTemporaria&) = delete;
    private:
        T& atributo;
        T original;
    };

    static int quantidade(const ListaSimplesmenteEncadeada& lista) { return lista.quantidade; }

    static void preencherLista(ListaSimplesmenteEncadeada& lista, std::initializer_list<std::string> dados)
    {
        exigirConsistencia(lista);
        if (dados.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("Quantidade excede o limite de int.");
        std::vector<std::unique_ptr<No<std::string>>> novos;
        for (const auto& valor : dados) novos.push_back(std::make_unique<No<std::string>>(valor));
        auto atual = lista.primeiro;
        while (atual != nullptr)
        {
            auto seguinte = atual->proximo;
            delete atual;
            atual = seguinte;
        }
        lista.primeiro = nullptr;
        lista.ultimo = nullptr;
        for (auto& no : novos)
        {
            if (lista.ultimo != nullptr) lista.ultimo->proximo = no.get();
            else lista.primeiro = no.get();
            lista.ultimo = no.release();
        }
        lista.quantidade = static_cast<int>(dados.size());
    }

    static std::vector<std::string> elementos(const ListaSimplesmenteEncadeada& lista)
    {
        exigirConsistencia(lista);
        std::vector<std::string> valores;
        for (auto atual = lista.primeiro; atual != nullptr; atual = atual->proximo)
            valores.push_back(atual->valor);
        return valores;
    }

    static std::vector<std::string> elementosReversos(const ListaSimplesmenteEncadeada& lista)
    {
        auto valores = elementos(lista);
        std::reverse(valores.begin(), valores.end());
        return valores;
    }

    static bool mesmosElementos(const ListaSimplesmenteEncadeada& lista, std::initializer_list<std::string> esperados)
    {
        const auto valores = elementos(lista);
        return std::equal(valores.begin(), valores.end(), esperados.begin(), esperados.end());
    }

    static AlteracaoTemporaria<int> alterarQuantidadeTemporariamente(ListaSimplesmenteEncadeada& lista, int quantidade)
    {
        return AlteracaoTemporaria<int>(lista.quantidade, quantidade);
    }

    // Posição zero no destino significa nullptr; posições de elementos começam em 1.
    static AlteracaoTemporaria<No<std::string>*> alterarProximoTemporariamente(
        ListaSimplesmenteEncadeada& lista, int origem, int destino)
    {
        auto no = noNaPosicao(lista, origem);
        auto novo = destino == 0 ? nullptr : noNaPosicao(lista, destino);
        return AlteracaoTemporaria<No<std::string>*>(no->proximo, novo);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarExtremidadeInicialTemporariamente(
        ListaSimplesmenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.primeiro, nullptr);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarExtremidadeFinalTemporariamente(
        ListaSimplesmenteEncadeada& lista, int posicao)
    {
        auto novo = posicao == 0 ? nullptr : noNaPosicao(lista, posicao);
        return AlteracaoTemporaria<No<std::string>*>(lista.ultimo, novo);
    }

private:
    static void exigirConsistencia(const ListaSimplesmenteEncadeada& lista)
    {
        switch (lista.checarConsistencia())
        {
        case ConsistenciaStatus::OK:
            return;
        case ConsistenciaStatus::CICLO_DETECTADO:
            throw std::logic_error("CICLO_DETECTADO: a lista contém um ciclo.");
        case ConsistenciaStatus::QUANTIDADE_INCORRETA:
            throw std::logic_error("QUANTIDADE_INCORRETA: o contador não corresponde aos nós da lista.");
        case ConsistenciaStatus::EXTREMIDADE_INCORRETA:
            throw std::logic_error("EXTREMIDADE_INCORRETA: primeiro ou último inválido.");
        case ConsistenciaStatus::SENTINELA_INCORRETA:
            throw std::logic_error("SENTINELA_INCORRETA: sentinela inválida.");
        case ConsistenciaStatus::ENCADEAMENTO_INCORRETO:
            throw std::logic_error("ENCADEAMENTO_INCORRETO: ligação inválida entre nós.");
        }
        throw std::logic_error("Status de consistência desconhecido.");
    }

    static No<std::string>* noNaPosicao(const ListaSimplesmenteEncadeada& lista, int posicao)
    {
        exigirConsistencia(lista);
        if (posicao < 1 || posicao > lista.quantidade) throw std::out_of_range("Posição inválida no helper.");
        auto atual = lista.primeiro;
        for (int i = 1; i < posicao; ++i) atual = atual->proximo;
        return atual;
    }
};

#endif
