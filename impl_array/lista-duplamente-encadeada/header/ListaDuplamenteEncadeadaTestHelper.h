#ifndef LISTADUPLAMENTEENCADEADATESTHELPER_H
#define LISTADUPLAMENTEENCADEADATESTHELPER_H

#include "ListaDuplamenteEncadeada.h"
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <vector>

class ListaDuplamenteEncadeadaTestHelper
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

    static int quantidade(const ListaDuplamenteEncadeada& lista) { return lista.quantidade; }

    // Verificação independente: não chama nenhuma operação pública da lista.
    static bool consistente(const ListaDuplamenteEncadeada& lista)
    {
        if (lista.cabeca == nullptr || lista.cauda == nullptr || lista.cabeca == lista.cauda ||
            lista.quantidade < 0 || lista.cabeca->anterior != nullptr || lista.cauda->proximo != nullptr)
            return false;
        std::unordered_set<const No<std::string>*> visitados;
        auto anterior = lista.cabeca;
        auto atual = lista.cabeca->proximo;
        while (atual != lista.cauda)
        {
            if (atual == nullptr || atual == lista.cabeca || !visitados.insert(atual).second ||
                atual->anterior != anterior) return false;
            anterior = atual;
            atual = atual->proximo;
        }
        if (lista.cauda->anterior != anterior || visitados.size() != static_cast<std::size_t>(lista.quantidade))
            return false;
        std::unordered_set<const No<std::string>*> reversos;
        auto seguinte = lista.cauda;
        atual = lista.cauda->anterior;
        while (atual != lista.cabeca)
        {
            if (atual == nullptr || atual == lista.cauda || !reversos.insert(atual).second ||
                atual->proximo != seguinte) return false;
            seguinte = atual;
            atual = atual->anterior;
        }
        return lista.cabeca->proximo == seguinte && visitados == reversos;
    }

    static void preencherLista(ListaDuplamenteEncadeada& lista, std::initializer_list<std::string> dados)
    {
        exigirConsistencia(lista);
        if (dados.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::length_error("Quantidade excede o limite de int.");
        std::vector<std::unique_ptr<No<std::string>>> novos;
        for (const auto& valor : dados) novos.push_back(std::make_unique<No<std::string>>(valor));
        auto atual = lista.cabeca->proximo;
        while (atual != lista.cauda)
        {
            auto seguinte = atual->proximo;
            delete atual;
            atual = seguinte;
        }
        auto anterior = lista.cabeca;
        for (auto& no : novos)
        {
            no->anterior = anterior;
            anterior->proximo = no.get();
            anterior = no.release();
        }
        anterior->proximo = lista.cauda;
        lista.cauda->anterior = anterior;
        lista.quantidade = static_cast<int>(dados.size());
    }

    static std::vector<std::string> elementos(const ListaDuplamenteEncadeada& lista)
    {
        exigirConsistencia(lista);
        std::vector<std::string> valores;
        for (auto atual = lista.cabeca->proximo; atual != lista.cauda; atual = atual->proximo)
            valores.push_back(atual->valor);
        return valores;
    }

    static std::vector<std::string> elementosReversos(const ListaDuplamenteEncadeada& lista)
    {
        exigirConsistencia(lista);
        std::vector<std::string> valores;
        for (auto atual = lista.cauda->anterior; atual != lista.cabeca; atual = atual->anterior)
            valores.push_back(atual->valor);
        return valores;
    }

    static bool mesmosElementos(const ListaDuplamenteEncadeada& lista, std::initializer_list<std::string> esperados)
    {
        const auto valores = elementos(lista);
        return std::equal(valores.begin(), valores.end(), esperados.begin(), esperados.end());
    }

    static AlteracaoTemporaria<int> alterarQuantidadeTemporariamente(ListaDuplamenteEncadeada& lista, int quantidade)
    {
        return AlteracaoTemporaria<int>(lista.quantidade, quantidade);
    }

    // Posição zero no destino significa nullptr; posições de elementos começam em 1.
    static AlteracaoTemporaria<No<std::string>*> alterarProximoTemporariamente(
        ListaDuplamenteEncadeada& lista, int origem, int destino)
    {
        auto no = noNaPosicao(lista, origem);
        auto novo = destino == 0 ? nullptr : noNaPosicao(lista, destino);
        return AlteracaoTemporaria<No<std::string>*>(no->proximo, novo);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarExtremidadeInicialTemporariamente(
        ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cabeca->proximo, nullptr);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarExtremidadeFinalTemporariamente(
        ListaDuplamenteEncadeada& lista, int posicao)
    {
        auto novo = posicao == 0 ? nullptr : noNaPosicao(lista, posicao);
        return AlteracaoTemporaria<No<std::string>*>(lista.cauda->anterior, novo);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarAnteriorTemporariamente(
        ListaDuplamenteEncadeada& lista, int origem, int destino)
    {
        auto no = noNaPosicao(lista, origem);
        auto novo = destino == 0 ? nullptr : noNaPosicao(lista, destino);
        return AlteracaoTemporaria<No<std::string>*>(no->anterior, novo);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarCabecaTemporariamente(ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cabeca, nullptr);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarCaudaTemporariamente(ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cauda, nullptr);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarAnteriorCabecaTemporariamente(ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cabeca->anterior, lista.cabeca);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarProximoCaudaTemporariamente(ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cauda->proximo, lista.cauda);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarAnteriorCabecaTemporariamente(
        ListaDuplamenteEncadeada& lista, No<std::string>* destino)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cabeca->anterior, destino);
    }

    static AlteracaoTemporaria<No<std::string>*> alterarProximoCaudaTemporariamente(
        ListaDuplamenteEncadeada& lista, No<std::string>* destino)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cauda->proximo, destino);
    }

    static AlteracaoTemporaria<No<std::string>*> coincidirSentinelasTemporariamente(ListaDuplamenteEncadeada& lista)
    {
        return AlteracaoTemporaria<No<std::string>*>(lista.cauda, lista.cabeca);
    }

private:
    static void exigirConsistencia(const ListaDuplamenteEncadeada& lista)
    {
        if (!consistente(lista)) throw std::logic_error("Estado interno da lista inconsistente.");
    }

    static No<std::string>* noNaPosicao(const ListaDuplamenteEncadeada& lista, int posicao)
    {
        exigirConsistencia(lista);
        if (posicao < 1 || posicao > lista.quantidade) throw std::out_of_range("Posição inválida no helper.");
        auto atual = lista.cabeca->proximo;
        for (int i = 1; i < posicao; ++i) atual = atual->proximo;
        return atual;
    }
};

#endif
