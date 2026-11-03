#include "ListaDuplamenteEncadeada.h"
#include <sstream>
#include <stdexcept>
#include <memory>

namespace
{
// Floyd: O(n) em tempo e O(1) em memória, sem usar o contador da lista.
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
        {
            return true;
        }
    }
    return false;
}

// ============================================================================
//  FUNÇÕES AUXILIARES (escritas por mim para não repetir código)
// ============================================================================
//
// Quase todas as operações da lista se resumem a DUAS ideias:
//
//   1) LIGAR um nó novo entre dois vizinhos       -> ligarEntre()
//   2) DESLIGAR um nó que já está na lista        -> desligar()
//
// Se essas duas funções estiverem certas, todos os métodos de inserir e de
// remover viram só "encontre os vizinhos certos e chame a auxiliar".
//
// Elas ficam dentro do namespace anônimo (como o temCiclo acima): isso as
// torna "privadas" deste arquivo, sem precisar mexer no ListaDuplamenteEncadeada.h.
//
// Obs.: elas NÃO mexem no contador `quantidade` (ele é um atributo privado da
// lista). Quem chama é que faz ++quantidade ou --quantidade.

using NoString = No<std::string>;

// Cria um nó com `valor` e o encaixa entre `anterior` e `seguinte`.
//
// PRÉ-CONDIÇÃO: `anterior` e `seguinte` já são vizinhos na lista, ou seja,
//               anterior->proximo == seguinte e seguinte->anterior == anterior.
//
//   ANTES:   anterior <-> seguinte
//   DEPOIS:  anterior <-> novo <-> seguinte
//
// Precisamos acertar QUATRO ponteiros (dois do nó novo e um de cada vizinho).
NoString* ligarEntre(NoString* anterior, NoString* seguinte, const std::string& valor)
{
    // Alocamos PRIMEIRO. Se o `new` falhar (lança std::bad_alloc), nada da lista
    // foi alterado ainda -> a lista continua válida. Isso se chama "segurança
    // contra exceções": nunca deixe a lista pela metade.
    NoString* novo = new NoString(valor);

    // Passo 1 e 2: configurar o nó novo (ele ainda não é visto por ninguém,
    // então não há risco de deixar a lista inconsistente).
    novo->anterior = anterior;
    novo->proximo = seguinte;

    // Passo 3 e 4: agora "apresentamos" o nó novo aos vizinhos.
    // A ORDEM importa pouco aqui, mas o que NÃO pode faltar é nenhum dos 4 passos:
    // se esquecer um, o percurso para frente e o para trás deixam de combinar
    // (é exatamente o que o checarConsistencia() chama de ENCADEAMENTO_INCORRETO).
    anterior->proximo = novo;
    seguinte->anterior = novo;

    return novo;
}

// Tira `no` da lista, libera a memória dele e devolve o valor que ele guardava.
//
//   ANTES:   anterior <-> no <-> seguinte
//   DEPOIS:  anterior <-> seguinte         (e `no` deixa de existir)
//
// PRÉ-CONDIÇÃO: `no` é um nó de DADOS (nunca a cabeça nem a cauda).
//
// Veja a vantagem da lista DUPLAMENTE encadeada: o próprio nó sabe quem é o
// anterior (no->anterior). Na lista simples a gente precisaria percorrer a
// lista toda procurando o anterior. Aqui é O(1).
//
// Veja também a vantagem das SENTINELAS: `no->anterior` e `no->proximo` NUNCA
// são nullptr para um nó de dados (no pior caso são a cabeça/cauda). Por isso
// não existe "caso especial" para remover o primeiro, o último ou o único.
std::string desligar(NoString* no)
{
    // Guardamos o valor ANTES do delete, porque depois dele `no` não existe mais.
    std::string valor = no->valor;

    // Os vizinhos passam a apontar um para o outro, "pulando" o nó removido.
    no->anterior->proximo = no->proximo;
    no->proximo->anterior = no->anterior;

    // Só agora liberamos a memória (sem isso teríamos vazamento de memória).
    delete no;
    return valor;
}

// Devolve o nó que está na `posicao` (contando a partir de 1).
//
// PRÉ-CONDIÇÃO: 1 <= posicao <= quantidade + 1.
// Truque: quando posicao == quantidade + 1 ela devolve a própria CAUDA.
// Isso é útil na inserção ("inserir antes da cauda" = inserir no fim).
//
// Custo: O(n), pois anda `posicao - 1` passos a partir do início.
NoString* noNaPosicao(NoString* cabeca, int posicao)
{
    NoString* atual = cabeca->proximo;       // posição 1 (ou a cauda, se vazia)
    for (int i = 1; i < posicao; ++i)        // anda posicao-1 vezes
    {
        atual = atual->proximo;
    }
    return atual;
}
}

ListaDuplamenteEncadeada::ListaDuplamenteEncadeada() : cabeca(nullptr), cauda(nullptr), quantidade(0)
{
    // A posse temporária evita vazamento se a segunda alocação falhar.
    auto novaCabeca = std::make_unique<No<std::string>>("");
    auto novaCauda = std::make_unique<No<std::string>>("");
    novaCabeca->proximo = novaCauda.get();
    novaCauda->anterior = novaCabeca.get();
    cabeca = novaCabeca.release();
    cauda = novaCauda.release();
}

ListaDuplamenteEncadeada::~ListaDuplamenteEncadeada()
{
    auto atual = cabeca;
    while (atual != nullptr)
    {
        auto seguinte = atual->proximo;
        delete atual;
        atual = seguinte;
    }
}

// ============================================================================
//  INSERÇÕES
// ============================================================================

// O(1). Inserir no início = inserir ENTRE a cabeça e o primeiro nó de dados.
// Como a cabeça sempre existe, e cabeca->proximo é o primeiro elemento (ou a
// cauda, se a lista estiver vazia), o MESMO código serve para lista vazia ou não.
bool ListaDuplamenteEncadeada::inserirInicio(const std::string& elemento)
{
    ligarEntre(cabeca, cabeca->proximo, elemento);
    ++quantidade;   // não esqueça: o contador precisa acompanhar a lista!
    return true;
}

// O(1). Inserir no fim = inserir ENTRE o último nó de dados e a cauda.
// cauda->anterior é o último elemento (ou a cabeça, se a lista estiver vazia).
// Na lista simples isso seria O(n) sem ponteiro pro fim; aqui a cauda resolve.
bool ListaDuplamenteEncadeada::inserirFim(const std::string& elemento)
{
    ligarEntre(cauda->anterior, cauda, elemento);
    ++quantidade;
    return true;
}

// O(n). Posições válidas: de 1 até tamanho+1 (tamanho+1 = inserir no fim).
bool ListaDuplamenteEncadeada::inserirNaPosicao(int posicao, const std::string& elemento)
{
    // Validamos ANTES de alterar qualquer coisa. Assim, se a posição for
    // inválida, a lista fica exatamente como estava (o teste exige isso).
    if (posicao < 1 || posicao > quantidade + 1)
    {
        throw std::out_of_range("Posição inválida para inserção.");
    }

    // `seguinte` é o nó que hoje ocupa a posição desejada e que passará a ser
    // o vizinho da direita do nó novo. Se posicao == quantidade+1, `seguinte`
    // é a própria cauda -> inserir no fim funciona sem caso especial.
    NoString* seguinte = noNaPosicao(cabeca, posicao);

    // O vizinho da esquerda a gente descobre de graça: seguinte->anterior.
    ligarEntre(seguinte->anterior, seguinte, elemento);
    ++quantidade;
    return true;
}

// O(n). Insere `elemento` imediatamente antes da PRIMEIRA ocorrência de `referencia`.
bool ListaDuplamenteEncadeada::inserirAntes(const std::string& elemento, const std::string& referencia)
{
    // Percorre só os nós de dados: para ao chegar na cauda (que não é dado!).
    for (NoString* atual = cabeca->proximo; atual != cauda; atual = atual->proximo)
    {
        if (atual->valor == referencia)
        {
            // Achou a primeira ocorrência: insere entre o anterior dela e ela.
            ligarEntre(atual->anterior, atual, elemento);
            ++quantidade;
            return true;
        }
    }
    // Chegou na cauda sem achar a referência: nada é alterado.
    return false;
}

// O(n). A lista está em ordem DECRESCENTE (ex.: S, P, F, C) e sem duplicatas.
// Queremos achar o ponto certo para o novo elemento manter essa ordem.
//
// Ideia: andar enquanto os nós forem MAIORES que o elemento. Paramos no
// primeiro nó que seja MENOR OU IGUAL (ou na cauda, se não houver).
//
//   lista: S, P, F, C     inserir "H"
//   S > H -> segue | P > H -> segue | F > H? não ("F" < "H") -> PARA aqui
//   Insere antes do F:    S, P, H, F, C
bool ListaDuplamenteEncadeada::inserirOrdenado(const std::string& elemento)
{
    NoString* atual = cabeca->proximo;

    // A condição `atual != cauda` vem primeiro, para nunca comparar com a
    // cauda (o valor dela é "" e não faz parte da lista).
    // O operador > de std::string compara em ordem lexicográfica.
    while (atual != cauda && atual->valor > elemento)
    {
        atual = atual->proximo;
    }

    // Aqui, `atual` é o primeiro nó <= elemento (ou a cauda).
    // Se for IGUAL, o elemento já existe: o contrato manda rejeitar.
    if (atual != cauda && atual->valor == elemento)
    {
        return false;
    }

    // Insere antes de `atual`. Se `atual` for a cauda, vira o novo último;
    // se for o primeiro nó, vira o novo primeiro. Tudo sem caso especial.
    ligarEntre(atual->anterior, atual, elemento);
    ++quantidade;
    return true;
}

// ============================================================================
//  REMOÇÕES
// ============================================================================

// O(1). Remove o primeiro elemento e devolve o valor dele.
std::string ListaDuplamenteEncadeada::removerInicio()
{
    // Lista vazia: não há o que remover. Cuidado! Sem esta checagem
    // removeríamos a CAUDA (cabeca->proximo == cauda) e destruiríamos a lista.
    if (quantidade == 0)
    {
        throw std::out_of_range("Lista vazia: não há elemento para remover.");
    }
    --quantidade;
    return desligar(cabeca->proximo);
}

// O(1). Remove o último elemento e devolve o valor dele.
// Aqui a lista DUPLA brilha: cauda->anterior já é o último nó, e desligar()
// consegue achar o anterior dele sozinho. Na lista simples seria O(n).
std::string ListaDuplamenteEncadeada::removerFim()
{
    if (quantidade == 0)
    {
        throw std::out_of_range("Lista vazia: não há elemento para remover.");
    }
    --quantidade;
    return desligar(cauda->anterior);
}

// O(n). Remove o elemento da posição indicada (1..tamanho).
std::string ListaDuplamenteEncadeada::removerNaPosicao(int posicao)
{
    // Diferente da inserção, aqui o limite é `quantidade` (e não quantidade+1):
    // não dá pra remover "depois do último", pois ali está a cauda.
    // Esta checagem também cobre a lista vazia (quantidade == 0).
    if (posicao < 1 || posicao > quantidade)
    {
        throw std::out_of_range("Posição inválida para remoção.");
    }
    --quantidade;
    return desligar(noNaPosicao(cabeca, posicao));
}

// O(n). Remove TODAS as ocorrências de `elemento` e diz quantas removeu.
int ListaDuplamenteEncadeada::removerTodos(const std::string& elemento)
{
    int removidos = 0;
    NoString* atual = cabeca->proximo;

    while (atual != cauda)
    {
        // ARMADILHA CLÁSSICA: se removermos `atual`, ele é deletado e não
        // podemos mais ler atual->proximo (acesso a memória liberada!).
        // Por isso guardamos o próximo ANTES de remover.
        NoString* seguinte = atual->proximo;

        if (atual->valor == elemento)
        {
            desligar(atual);
            --quantidade;
            ++removidos;
        }
        atual = seguinte;   // continua a partir do que guardamos
    }
    return removidos;       // 0 se a lista é vazia ou o valor não existe
}

// ============================================================================
//  BUSCA E ACESSO
// ============================================================================

// O(n). Devolve a posição (a partir de 1) da primeira ocorrência, ou -1.
int ListaDuplamenteEncadeada::buscar(const std::string& elemento) const
{
    int posicao = 1;
    for (NoString* atual = cabeca->proximo; atual != cauda; atual = atual->proximo)
    {
        if (atual->valor == elemento)
        {
            return posicao;   // primeira ocorrência: já podemos parar
        }
        ++posicao;
    }
    return -1;   // também é o resultado para a lista vazia (o for nem roda)
}

// O(n). Devolve uma CÓPIA do valor da posição, ou nullopt se inválida.
// Aqui NÃO se lança exceção (diferente de inserir/remover por posição).
std::optional<std::string> ListaDuplamenteEncadeada::elementoNaPosicao(int posicao) const
{
    if (posicao < 1 || posicao > quantidade)
    {
        return std::nullopt;
    }
    // Um elemento "" (string vazia) é um valor válido e devolve optional("").
    // Isso é diferente de nullopt, que significa "não existe".
    return noNaPosicao(cabeca, posicao)->valor;
}

std::optional<std::string> ListaDuplamenteEncadeada::primeiroElemento() const
{
    if (quantidade == 0)
    {
        return std::nullopt;
    }
    return cabeca->proximo->valor;
}

std::optional<std::string> ListaDuplamenteEncadeada::ultimoElemento() const
{
    if (quantidade == 0)
    {
        return std::nullopt;
    }
    return cauda->anterior->valor;
}

int ListaDuplamenteEncadeada::tamanho() const
{
    return quantidade;
}

bool ListaDuplamenteEncadeada::vazia() const
{
    return quantidade == 0;
}

std::string ListaDuplamenteEncadeada::imprimir() const
{
    std::ostringstream resultado;
    resultado << "{";
    for (auto atual = cabeca->proximo; atual != cauda; atual = atual->proximo)
    {
        if (atual != cabeca->proximo) resultado << ", ";
        resultado << atual->valor;
    }
    resultado << "}";
    return resultado.str();
}

ConsistenciaStatus ListaDuplamenteEncadeada::checarConsistencia() const
{
    if (cabeca == nullptr || cauda == nullptr || cabeca == cauda)
        return ConsistenciaStatus::SENTINELA_INCORRETA;
    // Checar ambos os sentidos antes de qualquer percurso ou validação do contador.
    if (temCiclo(cabeca, [](auto no) { return no->proximo; }) ||
        temCiclo(cauda, [](auto no) { return no->anterior; }))
        return ConsistenciaStatus::CICLO_DETECTADO;
    if (quantidade < 0) return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    if (cabeca->anterior != nullptr || cauda->proximo != nullptr)
        return ConsistenciaStatus::SENTINELA_INCORRETA;

    std::size_t contagem = 0;
    auto anterior = cabeca;
    auto atual = cabeca->proximo;
    while (atual != cauda)
    {
        if (atual == nullptr || atual->anterior != anterior)
            return ConsistenciaStatus::ENCADEAMENTO_INCORRETO;
        ++contagem;
        anterior = atual;
        atual = atual->proximo;
    }
    if (cauda->anterior != anterior) return ConsistenciaStatus::ENCADEAMENTO_INCORRETO;

    std::size_t contagemReversa = 0;
    auto seguinte = cauda;
    atual = cauda->anterior;
    while (atual != cabeca)
    {
        if (atual == nullptr || atual->proximo != seguinte)
            return ConsistenciaStatus::ENCADEAMENTO_INCORRETO;
        ++contagemReversa;
        seguinte = atual;
        atual = atual->anterior;
    }
    if (cabeca->proximo != seguinte || contagem != contagemReversa)
        return ConsistenciaStatus::ENCADEAMENTO_INCORRETO;
    if (contagem != static_cast<std::size_t>(quantidade)) return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    return ConsistenciaStatus::OK;
}
