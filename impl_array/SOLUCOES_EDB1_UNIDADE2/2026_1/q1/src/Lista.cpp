#include "../header/Lista.h"
#include <sstream>
#include <stdexcept>
#define __CHECK_INTEGRIDADE__ 1

int Lista::contarIntersecao(const Lista &outra) const
{
    int total = 0;

    // Para cada elemento desta lista, procuramos o mesmo valor na outra.
    // Dois percursos aninhados produzem a complexidade Θ(n * m) solicitada.
    for (No* atual = this->primeiro; atual != nullptr; atual = atual->proximo)
    {
        for (No* candidato = outra.primeiro;
             candidato != nullptr;
             candidato = candidato->proximo)
        {
            if (atual->valor == candidato->valor)
            {
                ++total;
                break; // cada valor da lista atual deve ser contado uma única vez
            }
        }
    }

    // Não alteramos nenhuma das listas e não criamos estruturas auxiliares.
    return total;
}

/**
 *
 * !!!!! PERIGO !!!!!
 * NÃO MODIFIQUE O CÓDIGO ABAIXO
 * !!!!! PERIGO !!!!!
 */

Lista::Lista()
{
    this->quantidade = 0;
    this->primeiro = nullptr;
}

Lista::~Lista()
{
    auto aux = this->primeiro;

    while (aux != nullptr)
    {
        auto tmp = aux;
        aux = aux->proximo;
        delete tmp;
    }

    this->primeiro = nullptr;
    this->quantidade = 0;
}

bool Lista::inserirInicio(const std::string &elemento)
{
    No *novo = new No(elemento);
    novo->proximo = primeiro;
    primeiro = novo;
    ++quantidade;
    return true;
}

std::string Lista::imprimir() const
{
    std::ostringstream oss;
    oss << "{";
    No *atual = primeiro;
    while (atual != nullptr)
    {
        oss << atual->valor;
        if (atual->proximo != nullptr)
            oss << ", ";
        atual = atual->proximo;
    }
    oss << "}";
    return oss.str();
}

unsigned long Lista::tamanho() const
{
    return this->quantidade;
}

Lista::No::No(std::string valor)
{
    this->valor = valor;
    this->proximo = nullptr;
}

Lista::No::~No()
{
}