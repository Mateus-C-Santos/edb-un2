# Conjunto implementado com array

## Informações do projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

## Objetivo

Implementar um conjunto de inteiros com capacidade fixa, sem elementos repetidos.

Este projeto é uma atividade de Estruturas de Dados em C++20. O código base contém operações pendentes para implementação pelo aluno.

## Estrutura e operações esperadas

### Interface e implementação

### Arquivo de Interface (`header/Conjunto.h`)
Define a estrutura da classe `Conjunto` e suas operações públicas:

- `bool inserir(int elemento);`
- `bool remover(int elemento);`
- `bool contem(int elemento) const;`
- `int tamanho() const;`
- `void imprimir() const;`

#### Arquivo de Implementação (`src/Conjunto.cpp`)
Deve conter a lógica completa de manipulação do conjunto e implementação dos métodos. É aqui onde você deve implementar as operações do Conjunto.

### Contratos das operações

- `inserir`: retorna `true` ao inserir um elemento novo; retorna `false` se o elemento já existe ou se o conjunto está cheio.
- `contem`: informa se o elemento está presente.
- `remover`: retorna `true` se removeu o elemento e `false` se ele não existe.
- O construtor deve alocar o array e estabelecer um conjunto vazio com a capacidade recebida.
- Capacidade zero é válida: o conjunto permanece vazio e não admite inserções. Uma capacidade negativa lança `std::invalid_argument`.

## Atividade de implementação

Implemente as operações pendentes em `src/Conjunto.cpp`, respeitando a interface pública e os contratos descritos acima. Os testes em `test/` definem os cenários que a implementação deve atender.

Métodos pendentes: `inserir`, `contem`, `remover`.

No código base, esses métodos lançam `std::runtime_error("Método ainda não implementado.")`. Substitua essa exceção pela implementação de cada operação. As descrições deste README representam o **resultado esperado da implementação do aluno**, não funcionalidades já concluídas.

Os métodos auxiliares já implementados servem de apoio à atividade. Preserve suas interfaces e mantenha os testes fornecidos como referência. É esperado que os testes das operações pendentes falhem com essa mensagem antes da implementação.

O construtor e o destrutor já estão implementados: o construtor aloca o array e inicia a quantidade em zero, e o destrutor libera essa memória. `tamanho` e `imprimir` também estão fornecidos. As operações pendentes podem ser implementadas em qualquer ordem, pois cada suíte prepara e verifica o estado interno pelo helper.

## Complexidades esperadas

| Operação | Complexidade esperada |
|---|---|
| Inserir | O(n) |
| Remover | O(n) |
| Consultar presença | O(n) |
| Consultar tamanho | O(1) |
| Imprimir | O(n) |

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

Os testes usam doctest e são separados em quatro executáveis. `make test` apenas compila todas as suítes; `make run-test` compila, se necessário, e executa os testes funcionais em sequência, interrompendo a execução se uma suíte falhar.

| Arquivo | Comando | Executável |
|---|---|---|
| `test/TesteConstrutorTamanho.cpp` | `make run-test-construtor-tamanho` | `bin/test-construtor-tamanho` |
| `test/TesteInserir.cpp` | `make run-test-inserir` | `bin/test-inserir` |
| `test/TesteContem.cpp` | `make run-test-contem` | `bin/test-contem` |
| `test/TesteRemover.cpp` | `make run-test-remover` | `bin/test-remover` |

Cada comando específico compila, se necessário, e executa apenas sua suíte. Os executáveis compartilham a implementação de `src/Conjunto.cpp`.

### Preparação e verificação pelo helper

`header/ConjuntoTestHelper.h` define a classe amiga (`friend`) `ConjuntoTestHelper`, com acesso aos atributos privados de `Conjunto`. Esse acesso permite preparar o array e a quantidade diretamente e verificar o resultado sem chamar outra operação pendente.

Por exemplo, um teste de remoção prepara `{10, 20, 30}` pelo helper, chama somente `remover(20)` e verifica a quantidade e os elementos restantes diretamente. Ele não depende de `inserir`, `contem` ou `tamanho`. A comparação dos elementos após inserção ou remoção não exige uma ordem específica no array, mas detecta duplicatas e elementos perdidos.

O helper oferece consultas de capacidade, quantidade e elementos, escrita por posição, preenchimento do conjunto e comparação dos elementos ativos. O preenchimento atualiza a quantidade e verifica o limite da capacidade; os dados preparados pelos testes são únicos. Esse helper é apoio aos testes, não parte da interface pública destinada aos usuários do conjunto.

Como construtor, destrutor e tamanho já estão implementados, sua suíte deve passar no código base. As suítes de inserção, consulta e remoção devem apresentar a exceção de implementação pendente até que o aluno implemente a operação correspondente.

Para selecionar um caso durante a implementação, use os filtros do doctest:

```bash
make run-test-remover ARGS='--test-case="nome do caso"'
```

Substitua `nome do caso` por um nome listado por `make run-test-remover ARGS="--list-test-cases"`. Os mesmos filtros podem ser usados nos comandos das demais suítes.
