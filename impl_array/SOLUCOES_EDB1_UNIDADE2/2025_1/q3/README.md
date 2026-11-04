# Informacoes do Projeto

- **Instituicao:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

# Fila Implementada com Array

Este projeto implementa uma estrutura de dados do tipo **Fila (Queue)** utilizando um **array alocado dinamicamente com comportamento circular**. A fila segue a politica **FIFO (First-In, First-Out)**, ou seja, o primeiro elemento inserido é o primeiro a ser removido.

A classe é generica e aceita qualquer tipo de dado através do uso de **templates**.

---

## Estrutura de Dados

A fila é composta por:

- **elementos**: ponteiro para um array do tipo `T` (tipo genérico).
- **capacidade**: numero máximo de elementos que a fila pode armazenar.
- **quantidade**: quantidade atual de elementos na fila.
- **inicio**: índice do primeiro elemento.
- **fim**: índice onde o próximo elemento será inserido.

---

## Interface da Classe `Fila<T>`

```cpp
class Fila {
private:
    T* elementos;
    int capacidade;
    int quantidade;
    int inicio;
    int fim;

public:
    Fila(int cap);
    ~Fila();

    int tamanho();
    bool vazia();
    bool cheia();

    void enfileirar(T elemento);
    T desenfileirar();
    T frente();

    std::string imprimir();
};
```

---

## Como Funcionam as Operacoes

✅ **Enfileirar**
- Verifica se a fila está cheia.
- Insere o novo elemento na posicao `fim`.
- Atualiza `fim` com comportamento circular.
- Incrementa `quantidade`.
- Lanca `std::overflow_error` se a fila estiver cheia.

✅ **Desenfileirar**
- Verifica se a fila está vazia.
- Recupera o valor da posicao `inicio`.
- Atualiza `inicio` com comportamento circular.
- Decrementa `quantidade`.
- Lanca `std::underflow_error` se a fila estiver vazia.

✅ **Frente**
- Retorna o elemento na posicao `inicio`.
- Lanca `std::underflow_error` se a fila estiver vazia.

✅ **Imprimir**
- Percorre o array circular da posicao `inicio` ate o total de elementos e monta uma string no formato `{ elem1 elem2 ... }`.

---

## Por Que Usar Array Circular?

✔️ **Aproveitamento total do espaco do array**.  
✔️ **Sem necessidade de mover elementos** ao enfileirar/desenfileirar.  
✔️ **Implementacao eficiente e com tempo constante** para operacoes principais.

---

## Tabela de Complexidades

| Operacao         | Complexidade |
|------------------|--------------|
| Enfileirar       | O(1)         |
| Desenfileirar    | O(1)         |
| Consultar frente | O(1)         |
| Verificar vazio  | O(1)         |
| Verificar cheio  | O(1)         |
| Imprimir         | O(n)         |

---

## 📂 Estrutura de Diretórios

```
.
├── bin/       # Executaveis gerados apos a compilacao
├── doc/       # Documentacao do projeto
├── header/    # Arquivos de cabecalho (.h)
├── lib/       # Bibliotecas externas (ex: doctest.h)
├── src/       # Implementacao das classes (.cpp)
├── test/      # Arquivos de teste (usando doctest)
├── .gitignore # Arquivos/diretorios ignorados pelo Git
├── makefile   # Automacao da compilacao e execucao
└── README.md  # Este arquivo
```

---

## 🛠️ Compilacao e Execucao Usando o Makefile

### 🔧 Comandos Disponiveis:

| Comando            | Descricao                                    |
|---------------------|----------------------------------------------|
| `make` ou `make all` | Compila o programa principal e os testes.   |
| `make run`         | Executa o programa principal (`bin/main`).   |
| `make test`        | Compila apenas os testes.                    |
| `make run-test`    | Executa os testes (`bin/test`).              |
| `make clean`       | Remove arquivos objeto e executaveis.        |

### 📌 Exemplos de Uso:

```bash
# Compilar o projeto
make

# Executar o programa principal
make run

# Compilar e rodar os testes
make run-test

# Limpar arquivos de build
make clean
```
