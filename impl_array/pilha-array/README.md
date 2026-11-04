# Pilha implementada com array

## Informações do projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

## Objetivo

Implementar uma pilha genérica com capacidade fixa e política LIFO: o último elemento inserido é o primeiro removido.

Este projeto é uma atividade de Estruturas de Dados em C++20. O código base contém operações pendentes para implementação pelo aluno.

## Estrutura e operações esperadas

Este projeto implementa uma estrutura de dados do tipo **Pilha (Stack)** utilizando um **array alocado dinamicamente**. A pilha segue a politica **LIFO (Last-In, First-Out)**, ou seja, o ultimo elemento inserido é o primeiro a ser removido.

A classe é generica e aceita qualquer tipo de dado através do uso de **templates**.

### Estrutura de Dados

A pilha é composta por:

- **elementos**: ponteiro para um array do tipo `T` (tipo generico).
- **capacidade**: numero maximo de elementos que a pilha pode armazenar.
- **quantidade**: quantidade atual de elementos na pilha.

### Interface da Classe `Pilha<T>`

```cpp
class Pilha {
private:
    T* elementos;
    int capacidade;
    int quantidade;

public:
    Pilha(int cap);
    ~Pilha();

    int tamanho() const;
    bool vazia() const;
    bool cheia() const;

    void empilhar(T elemento);
    void desempilhar();
    std::optional<T> topo() const;

    std::string imprimir() const;
};
```

### Como Funcionam as Operacoes

✅ **Empilhar**
- Verifica se a pilha está cheia.
- Insere o novo elemento na posição `quantidade`.
- Incrementa `quantidade`.
- Lança `std::overflow_error` se a pilha estiver cheia.

✅ **Desempilhar**
- Verifica se a pilha está vazia.
- Decrementa `quantidade`.
- Lança `std::underflow_error` se a pilha estiver vazia.

✅ **Topo**
- Retorna uma cópia do elemento na posição `quantidade - 1` em `std::optional<T>`.
- Retorna `std::nullopt` se a pilha estiver vazia, sem lançar exceção por ausência de elemento.

✅ **Imprimir**
- Percorre o array do primeiro ao último elemento inserido e monta uma string no formato `{ elem1 elem2 ... }`.

### Por Que Usar Array?

✔️ **Acesso direto aos elementos** por índice.
✔️ **Implementação simples e eficiente** para pilhas de tamanho fixo.
✔️ **Baixo overhead** de memória (sem ponteiros extras).

## Atividade de implementação

Implemente as operações pendentes em `header/Pilha.h`, respeitando a interface pública e os contratos descritos acima. Os testes em `test/` definem os cenários que a implementação deve atender.

Métodos pendentes: `empilhar`, `desempilhar`, `topo`.

No código base, os acessos já retornam `std::nullopt` quando a estrutura está vazia. Para estruturas com elementos, os acessos continuam pendentes; assim como as demais operações pendentes, lançam `std::runtime_error("Método ainda não implementado.")`. Substitua essa exceção pela implementação de cada operação. As descrições deste README representam o **resultado esperado da implementação do aluno**, não funcionalidades já concluídas.

Os métodos auxiliares já implementados servem de apoio à atividade. Preserve suas interfaces e mantenha os testes fornecidos como referência. É esperado que os testes das operações pendentes falhem com essa mensagem antes da implementação.

## Complexidades esperadas

| Operacao         | Complexidade |
|------------------|--------------|
| Empilhar         | O(1)         |
| Desempilhar      | O(1)         |
| Consultar topo   | O(1)         |
| Verificar vazio  | O(1)         |
| Verificar cheio  | O(1)         |
| Imprimir         | O(n)         |

## Estrutura de diretórios

```text
.
├── .vscode/   # Configuração portátil de execução no VS Code
├── bin/       # Executáveis e objetos gerados; objetos em bin/obj/
├── header/    # Interfaces e implementações de templates (.h)
├── lib/       # Biblioteca de testes doctest
├── src/       # Programa de exemplo e implementações (.cpp)
├── test/      # Testes automatizados
├── .gitignore # Arquivos locais e gerados ignorados pelo Git
├── makefile   # Compilação, execução e limpeza
└── README.md  # Orientações da atividade
```

As classes com templates são implementadas em `header/`. As demais implementações ficam em `src/`, quando aplicável. Os objetos do programa são gerados em `bin/obj/src/`; os objetos dos testes, em `bin/obj/test/`. Quando existem implementações `.cpp` compartilhadas pelos testes, seus objetos ficam em `bin/obj/test-src/`.

## Pré-requisitos

- GNU Make.
- Compilador C++ com suporte a C++20 e aos sanitizadores AddressSanitizer e UndefinedBehaviorSanitizer.
- Terminal com comandos `mkdir`, `find` e `rm`, como em Linux, macOS ou um ambiente compatível no Windows.

O doctest já está incluído em `lib/doctest.h`. O Makefile usa `g++` por padrão; para escolher outro compilador, use, por exemplo, `make CXX=clang++`.

A compilação habilita avisos, símbolos de depuração e sanitizadores para ajudar a detectar erros de memória e comportamento indefinido.

## Compilação e execução

| Comando | Descrição |
|---|---|
| `make` ou `make all` | Compila o programa principal e os testes funcionais. |
| `make run` | Compila, se necessário, e executa o programa principal (`bin/main`). |
| `make test` | Compila os testes funcionais, sem executá-los. |
| `make run-test` | Compila, se necessário, e executa os testes funcionais. |
| `make clean` | Remove os arquivos gerados, preservando `bin/` e seu `.gitkeep`. |

```bash
make
make run
make run-test
make run-test ARGS="--list-test-cases"
make clean
```

`ARGS` permite passar argumentos ao programa ou ao doctest. A execução do programa de exemplo também pode lançar a exceção de implementação pendente ao chamar uma operação ainda não concluída.

## Testes

Os testes usam doctest e são reunidos em um único executável, `bin/test`. `make test` apenas compila; `make run-test` compila, se necessário, e executa a suíte funcional.

Para selecionar um caso durante a implementação, use os filtros do doctest:

```bash
make run-test ARGS='--test-case="nome do caso"'
```

Substitua `nome do caso` por um nome listado por `make run-test ARGS="--list-test-cases"`. Um teste pode depender de outras operações para preparar a estrutura; consulte seu código antes de escolher a ordem de implementação.
