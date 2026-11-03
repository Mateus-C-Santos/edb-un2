#include "ListaSimplesmenteEncadeada.h"
#include <sstream>
#include <stdexcept>

namespace
{
// Detecta ciclo na lista usando dois ponteiros:
// lento avança uma posição e rápido avança duas.
// Se eles se encontrarem, existe um ciclo.
template <typename Proximo>
bool temCiclo(const No<std::string>* inicio, Proximo proximo)
{
    auto lento = inicio;
    auto rapido = inicio;

    while (rapido != nullptr && proximo(rapido) != nullptr)
    {
        lento = proximo(lento);
        rapido = proximo(proximo(rapido));
        if (lento == rapido)
            return true;
    }
    return false;
}
}

// Inicialmente a lista não possui nós.
// primeiro e ultimo ficam nullptr e quantidade começa em zero.
ListaSimplesmenteEncadeada::ListaSimplesmenteEncadeada()
    : primeiro(nullptr), ultimo(nullptr), quantidade(0) {}

// Destrutor: percorre a lista e libera cada nó para não deixar memória ocupada.
ListaSimplesmenteEncadeada::~ListaSimplesmenteEncadeada()
{
    auto atual = primeiro;
    while (atual != nullptr)
    {
        auto seguinte = atual->proximo; // Guarda o próximo antes de apagar o atual.
        delete atual;
        atual = seguinte;
    }
}

// Insere um elemento antes do primeiro nó.
bool ListaSimplesmenteEncadeada::inserirInicio(const std::string& elemento)
{
    auto novo = new No<std::string>(elemento); // Cria o nó dinamicamente.
    novo->proximo = primeiro;                 // Novo nó aponta para o antigo primeiro.
    primeiro = novo;                          // Agora ele é o primeiro.

    // Se a lista estava vazia, o novo nó também é o último.
    if (ultimo == nullptr)
        ultimo = novo;

    ++quantidade;
    return true;
}

// Insere um elemento depois do último nó. O ponteiro ultimo torna isso O(1).
bool ListaSimplesmenteEncadeada::inserirFim(const std::string& elemento)
{
    auto novo = new No<std::string>(elemento);

    if (ultimo == nullptr) // Lista vazia: primeiro e ultimo recebem o novo nó.
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo; // Antigo último aponta para o novo.
        ultimo = novo;          // Atualiza o ponteiro do último.
    }

    ++quantidade;
    return true;
}

// Insere na posição informada. As posições começam em 1.
bool ListaSimplesmenteEncadeada::inserirNaPosicao(int posicao, const std::string& elemento)
{
    // Para inserir, são válidas as posições de 1 até quantidade + 1.
    if (posicao < 1 || posicao > quantidade + 1)
        throw std::out_of_range("Posição inválida para inserção.");

    if (posicao == 1)
        return inserirInicio(elemento);

    if (posicao == quantidade + 1)
        return inserirFim(elemento);

    // Para inserir no meio, encontramos o nó ANTERIOR à posição desejada.
    auto anterior = primeiro;
    for (int i = 1; i < posicao - 1; ++i)
        anterior = anterior->proximo;

    auto novo = new No<std::string>(elemento);
    novo->proximo = anterior->proximo; // Novo aponta para quem vinha depois do anterior.
    anterior->proximo = novo;          // Anterior passa a apontar para o novo.
    ++quantidade;
    return true;
}

// Insere elemento antes da primeira ocorrência de referencia.
// Se referencia não existir, não modifica a lista e retorna false.
bool ListaSimplesmenteEncadeada::inserirAntes(const std::string& elemento, const std::string& referencia)
{
    if (primeiro == nullptr)
        return false;

    if (primeiro->valor == referencia)
        return inserirInicio(elemento);

    auto anterior = primeiro;
    auto atual = primeiro->proximo;

    while (atual != nullptr && atual->valor != referencia)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr)
        return false; // Percorreu tudo e não encontrou a referência.

    auto novo = new No<std::string>(elemento);
    novo->proximo = atual;
    anterior->proximo = novo;
    ++quantidade;
    return true;
}

// Insere mantendo ordem lexicográfica DECRESCENTE (Z ... A).
// A lista já deve estar ordenada e não pode conter o elemento repetido.
bool ListaSimplesmenteEncadeada::inserirOrdenado(const std::string& elemento)
{
    if (buscar(elemento) != -1)
        return false; // Não permite duplicatas nesta operação.

    // Se estiver vazia ou o elemento deve ficar antes do primeiro.
    if (primeiro == nullptr || elemento > primeiro->valor)
        return inserirInicio(elemento);

    // Se deve ficar depois do último.
    if (elemento < ultimo->valor)
        return inserirFim(elemento);

    // Procura o ponto em que o próximo valor seria menor que o novo.
    auto anterior = primeiro;
    auto atual = primeiro->proximo;
    while (atual != nullptr && atual->valor > elemento)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    auto novo = new No<std::string>(elemento);
    novo->proximo = atual;
    anterior->proximo = novo;
    ++quantidade;
    return true;
}

// Remove o primeiro nó e devolve seu valor.
std::string ListaSimplesmenteEncadeada::removerInicio()
{
    if (primeiro == nullptr)
        throw std::out_of_range("Lista vazia.");

    auto removido = primeiro;
    std::string valor = removido->valor; // Copia o valor antes de liberar o nó.
    primeiro = primeiro->proximo;       // O segundo nó passa a ser o primeiro.
    --quantidade;

    if (primeiro == nullptr) // A lista ficou vazia.
        ultimo = nullptr;

    delete removido;
    return valor;
}

// Remove o último nó. É necessário percorrer para encontrar o penúltimo.
std::string ListaSimplesmenteEncadeada::removerFim()
{
    if (ultimo == nullptr)
        throw std::out_of_range("Lista vazia.");

    if (primeiro == ultimo) // Existe apenas um nó.
        return removerInicio();

    auto anterior = primeiro;
    while (anterior->proximo != ultimo)
        anterior = anterior->proximo;

    auto removido = ultimo;
    std::string valor = removido->valor;
    anterior->proximo = nullptr; // Penúltimo agora será o último.
    ultimo = anterior;
    --quantidade;
    delete removido;
    return valor;
}

// Remove o nó da posição informada (posições começam em 1).
std::string ListaSimplesmenteEncadeada::removerNaPosicao(int posicao)
{
    if (posicao < 1 || posicao > quantidade)
        throw std::out_of_range("Posição inválida para remoção.");

    if (posicao == 1)
        return removerInicio();

    if (posicao == quantidade)
        return removerFim();

    auto anterior = primeiro;
    for (int i = 1; i < posicao - 1; ++i)
        anterior = anterior->proximo;

    auto removido = anterior->proximo;
    std::string valor = removido->valor;
    anterior->proximo = removido->proximo; // Pula o nó que será removido.
    --quantidade;
    delete removido;
    return valor;
}

// Remove todas as ocorrências do elemento e retorna quantas foram removidas.
int ListaSimplesmenteEncadeada::removerTodos(const std::string& elemento)
{
    int removidos = 0;
    No<std::string>* anterior = nullptr;
    auto atual = primeiro;

    while (atual != nullptr)
    {
        if (atual->valor == elemento)
        {
            auto removido = atual;
            atual = atual->proximo; // Guarda o próximo antes de apagar o nó atual.

            if (anterior == nullptr)
                primeiro = atual; // O removido era o primeiro.
            else
                anterior->proximo = atual; // O anterior pula o removido.

            if (removido == ultimo)
                ultimo = anterior; // Atualiza ultimo se removeu o último nó.

            delete removido;
            --quantidade;
            ++removidos;
            // Não avançamos anterior: pode haver outro elemento igual em seguida.
        }
        else
        {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    return removidos;
}

// Retorna a posição da primeira ocorrência ou -1 se não encontrar.
int ListaSimplesmenteEncadeada::buscar(const std::string& elemento) const
{
    int posicao = 1;
    for (auto atual = primeiro; atual != nullptr; atual = atual->proximo)
    {
        if (atual->valor == elemento)
            return posicao;
        ++posicao;
    }
    return -1;
}

// Retorna o elemento da posição ou nullopt se a posição for inválida.
std::optional<std::string> ListaSimplesmenteEncadeada::elementoNaPosicao(int posicao) const
{
    if (posicao < 1 || posicao > quantidade)
        return std::nullopt;

    auto atual = primeiro;
    for (int i = 1; i < posicao; ++i)
        atual = atual->proximo;

    return atual->valor;
}

// Os métodos abaixo já estavam implementados no projeto original.
std::optional<std::string> ListaSimplesmenteEncadeada::primeiroElemento() const
{
    if (quantidade == 0)
        return std::nullopt;
    return primeiro->valor;
}

std::optional<std::string> ListaSimplesmenteEncadeada::ultimoElemento() const
{
    if (quantidade == 0)
        return std::nullopt;
    return ultimo->valor;
}

int ListaSimplesmenteEncadeada::tamanho() const
{
    return quantidade;
}

bool ListaSimplesmenteEncadeada::vazia() const
{
    return quantidade == 0;
}

// Monta uma representação textual, por exemplo: {A, B, C}.
std::string ListaSimplesmenteEncadeada::imprimir() const
{
    std::ostringstream resultado;
    resultado << "{";
    for (auto atual = primeiro; atual != nullptr; atual = atual->proximo)
    {
        if (atual != primeiro)
            resultado << ", ";
        resultado << atual->valor;
    }
    resultado << "}";
    return resultado.str();
}

// Confere se os ponteiros e a quantidade representam corretamente a lista.
ConsistenciaStatus ListaSimplesmenteEncadeada::checarConsistencia() const
{
    if (temCiclo(primeiro, [](auto no) { return no->proximo; }))
        return ConsistenciaStatus::CICLO_DETECTADO;
    if (quantidade < 0)
        return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    if (primeiro == nullptr)
    {
        if (ultimo != nullptr)
            return ConsistenciaStatus::EXTREMIDADE_INCORRETA;
        return quantidade == 0 ? ConsistenciaStatus::OK : ConsistenciaStatus::QUANTIDADE_INCORRETA;
    }
    if (ultimo == nullptr)
        return ConsistenciaStatus::EXTREMIDADE_INCORRETA;

    std::size_t contagem = 0;
    const No<std::string>* ultimoVisitado = nullptr;
    for (auto atual = primeiro; atual != nullptr; atual = atual->proximo)
    {
        ultimoVisitado = atual;
        ++contagem;
    }
    if (ultimoVisitado != ultimo)
        return ConsistenciaStatus::EXTREMIDADE_INCORRETA;
    if (contagem != static_cast<std::size_t>(quantidade))
        return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    return ConsistenciaStatus::OK;
}
