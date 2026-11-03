#include <stdexcept>
#include <iostream>
#include "Conjunto.h"

// CONSTRUTOR
// Recebe a capacidade máxima do conjunto.
// Inicializa o conjunto vazio e prepara o array.
Conjunto::Conjunto(const int capacidade)
    : elementos(nullptr), capacidade(capacidade), quantidade(0)
{
    // Impede que seja criada uma capacidade negativa.
    if (capacidade < 0)
    {
        throw std::invalid_argument("A capacidade não pode ser negativa.");
    }

    // Aloca dinamicamente um array de inteiros.
    // O tamanho do array será igual à capacidade recebida.
    this->elementos = new int[capacidade];
}


// DESTRUTOR
// Libera a memória que foi reservada pelo construtor.
// O delete[] é utilizado porque estamos liberando um array.
Conjunto::~Conjunto()
{
    delete[] this->elementos;
}


// MÉTODO CONTEM
// Verifica se determinado elemento já existe no conjunto.
// Retorna true se encontrar e false se não encontrar.
bool Conjunto::contem(int elemento) const
{
    // Percorre somente as posições que possuem elementos.
    // Começa em 0 e continua enquanto i for menor que quantidade.
    for (int i = 0; i < quantidade; i++)
    {
        // Compara o elemento procurado com o valor
        // armazenado na posição atual do array.
        if (elementos[i] == elemento)
        {
            // Encontrou o elemento.
            // Retorna true e encerra a função.
            return true;
        }
    }

    // Se chegou até aqui, significa que percorreu o array
    // inteiro sem encontrar o elemento.
    return false;
}


// MÉTODO INSERIR
// Adiciona um novo elemento ao conjunto.
// Não permite números repetidos nem inserções acima da capacidade.
bool Conjunto::inserir(int elemento)
{
    // Primeiro verifica se o elemento já existe.
    // Um conjunto não pode possuir elementos repetidos.
    if (contem(elemento))
    {
        // Se já existir, não realiza a inserção.
        return false;
    }

    // Verifica se o conjunto já está cheio.
    // Se quantidade for igual à capacidade, não existe espaço.
    if (quantidade >= capacidade)
    {
        return false;
    }

    // Insere o elemento na próxima posição disponível.
    // Exemplo: se quantidade for 3, insere na posição 3.
    elementos[quantidade] = elemento;

    // Aumenta a quantidade de elementos armazenados.
    // Isso acontece porque acabamos de inserir um número.
    quantidade++;

    // Retorna true porque a inserção foi realizada.
    return true;
}


// MÉTODO REMOVER
// Remove um elemento do conjunto.
// Se encontrar o elemento, reorganiza o array para não deixar
// espaços vazios entre os elementos armazenados.
bool Conjunto::remover(int elemento)
{
    // Inicializa a posição com -1.
    // Utilizamos -1 para indicar que ainda não encontramos
    // o elemento que queremos remover.
    int posicao = -1;

    // Percorre todas as posições ocupadas do array.
    for (int i = 0; i < quantidade; i++)
    {
        // Verifica se o elemento da posição atual
        // é igual ao elemento que queremos remover.
        if (elementos[i] == elemento)
        {
            // Guarda o índice onde o elemento foi encontrado.
            posicao = i;

            // Interrompe o laço porque já encontramos o elemento.
            break;
        }
    }

    // Se posição continuar valendo -1,
    // significa que o elemento não existe no conjunto.
    if (posicao == -1)
    {
        return false;
    }

    // Desloca todos os elementos seguintes uma posição
    // para a esquerda, ocupando o espaço do elemento removido.
    //
    // Exemplo:
    // Antes: 10, 20, 30, 40
    // Removendo 20:
    // Depois: 10, 30, 40
    //
    // O 30 ocupa a posição do 20.
    // O 40 ocupa a posição do 30.
    for (int i = posicao; i < quantidade - 1; i++)
    {
        // Copia o próximo elemento para a posição atual.
        elementos[i] = elementos[i + 1];
    }

    // Diminui a quantidade porque um elemento foi removido.
    quantidade--;

    // Retorna true porque a remoção foi realizada.
    return true;
}


// MÉTODO TAMANHO
// Retorna quantos elementos existem atualmente no conjunto.
// Atenção: retorna a quantidade atual, não a capacidade máxima.
int Conjunto::tamanho() const
{
    return this->quantidade;
}


// MÉTODO IMPRIMIR
// Mostra todos os elementos armazenados no conjunto.
void Conjunto::imprimir() const
{
    // Imprime a abertura das chaves.
    std::cout << "{ ";

    // Percorre todas as posições que possuem elementos.
    for(int i = 0; i < quantidade; ++i)
    {
        // Imprime o elemento da posição atual.
        std::cout << this->elementos[i] << " ";
    }

    // Imprime o fechamento das chaves e pula uma linha.
    std::cout << "}" << std::endl;
}
