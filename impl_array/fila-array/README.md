# Fila implementada com array

## Informações do projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

## Objetivo

Implementar uma fila genérica com array circular e política FIFO: o primeiro elemento inserido é o primeiro removido.

Este projeto é uma atividade de Estruturas de Dados em C++20. O código base contém operações pendentes para implementação pelo aluno.

## Estrutura e operações esperadas

Este projeto implementa uma estrutura de dados do tipo **Fila (Queue)** utilizando um **array alocado dinamicamente com comportamento circular**. A fila segue a politica **FIFO (First-In, First-Out)**, ou seja, o primeiro elemento inserido é o primeiro a ser removido.

A classe é generica e aceita qualquer tipo de dado através do uso de **templates**.

### Estrutura de Dados

A fila é composta por:

- **elementos**: ponteiro para um array do tipo `T` (tipo genérico).
- **capacidade**: numero máximo de elementos que a fila pode armazenar.
- **quantidade**: quantidade atual de elementos na fila.
- **inicio**: índice do primeiro elemento.
- **fim**: índice onde o próximo elemento será inserido.

### Interface da Classe `Fila<T>`

```cpp
template <typename T>
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
    std::optional<T> frente();

    std::string imprimir();
};
```

### Como Funcionam as Operacoes

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
- Retorna uma cópia do elemento na posição `inicio` em `std::optional<T>`.
- Retorna `std::nullopt` se a fila estiver vazia, sem lançar exceção por ausência de elemento.

✅ **Imprimir**
- Percorre o array circular da posicao `inicio` ate o total de elementos e monta uma string no formato `{ elem1 elem2 ... }`.

### Por Que Usar Array Circular?

✔️ **Aproveitamento total do espaco do array**.
✔️ **Sem necessidade de mover elementos** ao enfileirar/desenfileirar.
✔️ **Implementacao eficiente e com tempo constante** para operacoes principais.

## Atividade de implementação

Implemente as operações pendentes em `header/Fila.h`, respeitando a interface pública e os contratos descritos acima. Os testes em `test/` definem os cenários que a implementação deve atender.

Métodos pendentes: `enfileirar`, `desenfileirar`, `frente`.

No código base, os acessos já retornam `std::nullopt` quando a estrutura está vazia. Para estruturas com elementos, os acessos continuam pendentes; assim como as demais operações pendentes, lançam `std::runtime_error("Método ainda não implementado.")`. Substitua essa exceção pela implementação de cada operação. As descrições deste README representam o **resultado esperado da implementação do aluno**, não funcionalidades já concluídas.

Os métodos auxiliares já implementados servem de apoio à atividade. Preserve suas interfaces e mantenha os testes fornecidos como referência. É esperado que os testes das operações pendentes falhem com essa mensagem antes da implementação.

## Complexidades esperadas

| Operacao         | Complexidade |
|------------------|--------------|
| Enfileirar       | O(1)         |
| Desenfileirar    | O(1)         |
| Consultar frente | O(1)         |
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
