#include "Lista.h"
#include <sstream>
#include <stdexcept>
#define __CHECK_INTEGRIDADE__ 1

bool Lista::removerUltimaOcorrencia(const std::string& s)
{
    No* atual = this->primeiro;
    No* anterior = nullptr;

    // Guardamos o endereço da última ocorrência encontrada e seu anterior.
    No* ultimaOcorrencia = nullptr;
    No* anteriorDaUltima = nullptr;

    // O percurso completo é necessário para saber qual ocorrência é a última.
    while (atual != nullptr)
    {
        if (atual->valor == s)
        {
            ultimaOcorrencia = atual;
            anteriorDaUltima = anterior;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    // Nenhum nó tinha o valor procurado.
    if (ultimaOcorrencia == nullptr)
    {
        return false;
    }

    // Retiramos o nó da cadeia, tratando separadamente o primeiro nó.
    if (anteriorDaUltima == nullptr)
    {
        this->primeiro = ultimaOcorrencia->proximo;
    }
    else
    {
        anteriorDaUltima->proximo = ultimaOcorrencia->proximo;
    }

    delete ultimaOcorrencia;
    --this->quantidade;
    return true;
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

    while(aux != nullptr)
    {
        auto tmp = aux;
        aux = aux->proximo;
        delete tmp;
    }

    this->primeiro = nullptr;
    this->quantidade = 0;
}

bool Lista::inserirInicio(const std::string& elemento)
{
    No* novo = new No(elemento);
    novo->proximo = primeiro;
    primeiro = novo;
    ++quantidade;
    return true;
}

std::string Lista::imprimir() const
{
    std::ostringstream oss;
    oss << "{";
    No* atual = primeiro;
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