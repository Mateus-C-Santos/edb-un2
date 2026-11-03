# Lista duplamente encadeada

## Informações do projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

## Objetivo

Implementar uma lista de strings em C++20. Este projeto e o de lista simplesmente encadeada oferecem as mesmas operações públicas, permitindo comparar os algoritmos e suas complexidades nas duas representações.

O código base contém operações pendentes para implementação pelo aluno. As descrições abaixo representam o **resultado esperado**, não funcionalidades já concluídas.

## Estrutura e operações esperadas

### Representação interna

Cada nó armazena uma string e dois ponteiros, `proximo` e `anterior`. A lista possui duas sentinelas, `cabeca` e `cauda`, que existem mesmo quando não há elementos e não fazem parte do tamanho lógico.

```text
nullptr <- cabeca <-> A <-> B <-> C <-> cauda -> nullptr
```

Na lista vazia, `cabeca->proximo` aponta para `cauda` e `cauda->anterior` aponta para `cabeca`. As sentinelas simplificam inserções e remoções, pois cada nó de dados tem um predecessor e um sucessor. O percurso pode ocorrer nos dois sentidos.

`header/No.h` define `No<T>`. `header/ListaDuplamenteEncadeada.h` define a classe da lista, seus ponteiros e o contador `int quantidade`. Valores repetidos são permitidos nas listas em geral; a inserção ordenada tem um contrato específico.

### Interface pública

```cpp
class ListaDuplamenteEncadeada
{
public:
ListaDuplamenteEncadeada();
    ~ListaDuplamenteEncadeada();

    bool inserirInicio(const std::string& elemento);
    bool inserirFim(const std::string& elemento);
    bool inserirNaPosicao(int posicao, const std::string& elemento);
    bool inserirAntes(const std::string& elemento, const std::string& referencia);
    bool inserirOrdenado(const std::string& elemento);

    std::string removerInicio();
    std::string removerFim();
    std::string removerNaPosicao(int posicao);
    int removerTodos(const std::string& elemento);

    int buscar(const std::string& elemento) const;
    std::optional<std::string> primeiroElemento() const;
    std::optional<std::string> ultimoElemento() const;
    std::optional<std::string> elementoNaPosicao(int posicao) const;

    int tamanho() const;
    bool vazia() const;
    std::string imprimir() const;
    ConsistenciaStatus checarConsistencia() const;
};
```

Todos os parâmetros de elementos são `const std::string&`. Os três métodos de acesso retornam `std::optional<std::string>` com uma cópia do valor; as remoções retornam `std::string`. Assim, o retorno não mantém referências aos nós. As posições começam em **1** e são representadas por `int`, assim como o tamanho.

### Inserções

| Método | Contrato |
|---|---|
| `inserirInicio(elemento)` | Insere antes do primeiro elemento e retorna `true`. |
| `inserirFim(elemento)` | Insere depois do último elemento e retorna `true`. |
| `inserirNaPosicao(posicao, elemento)` | Insere em uma posição de 1 até tamanho + 1; retorna `true`. |
| `inserirAntes(elemento, referencia)` | Insere antes da primeira ocorrência da referência; retorna `false` se ela não existe. |
| `inserirOrdenado(elemento)` | Preserva ordem lexicográfica decrescente; retorna `false` se o elemento já existe. |

Inserções comuns aceitam duplicatas e strings vazias. Uma posição inválida lança `std::out_of_range` e preserva o estado da lista.

A pré-condição de `inserirOrdenado` é uma lista já ordenada em ordem decrescente e sem duplicatas, incluindo a lista vazia. A operação não precisa ordenar uma lista arbitrária. Inserções pelas outras operações podem deixar de preservar essa pré-condição.

### Remoções

| Método | Contrato |
|---|---|
| `removerInicio()` | Remove e retorna o primeiro elemento. |
| `removerFim()` | Remove e retorna o último elemento. |
| `removerNaPosicao(posicao)` | Remove e retorna o elemento da posição indicada. |
| `removerTodos(elemento)` | Remove todas as ocorrências e retorna a quantidade removida. |

Remoções por extremidade ou posição lançam `std::out_of_range` quando o elemento não existe, inclusive em lista vazia. `removerTodos` retorna `0` em lista vazia ou quando o valor não existe.

Toda remoção deve liberar os nós removidos, atualizar o contador e os ponteiros e preservar a ordem relativa dos elementos restantes. Ao remover o último elemento, a lista deve voltar à representação vazia correta. Erros de posição preservam o estado.

### Busca e acesso

- `buscar(elemento)`: retorna a posição da primeira ocorrência, ou `-1` se não existir, inclusive na lista vazia.
- `primeiroElemento()` e `ultimoElemento()`: retornam o valor da extremidade em um `std::optional<std::string>`, ou `std::nullopt` em lista vazia, sem lançar exceção por ausência de elemento.
- `elementoNaPosicao(posicao)`: retorna o valor na posição de 1 até tamanho em um `std::optional<std::string>`; uma posição inválida retorna `std::nullopt`, sem lançar exceção por índice inválido.
- Um elemento cujo valor é a string vazia retorna um optional preenchido com `""`; isso é diferente de `std::nullopt`.
- Consultas não alteram os nós, seus valores ou a quantidade.

### Auxiliares fornecidos

O construtor estabelece uma lista vazia válida. O destrutor libera todos os nós alocados incluindo as sentinelas. `tamanho`, `vazia`, `primeiroElemento`, `ultimoElemento`, `imprimir` e `checarConsistencia` já estão implementados.

`imprimir` retorna uma string no formato `{A, B, C}`; a lista vazia é representada por `{}`. O formato é igual nos dois projetos.

### Invariantes e detecção de ciclos

`checarConsistencia() const` retorna o enum `ConsistenciaStatus`, definido em `header/ConsistenciaStatus.h` e igual nos dois projetos. Uma lista válida retorna `ConsistenciaStatus::OK`.

- `cabeca` e `cauda` existem e são sentinelas distintas.
- `cabeca->anterior` e `cauda->proximo` são `nullptr`.
- O percurso por `proximo` chega à cauda; o percurso por `anterior` chega à cabeça.
- Para cada ligação, os ponteiros dos dois sentidos são recíprocos.
- Não existem ciclos em nenhum dos sentidos, inclusive envolvendo sentinelas.
- O contador é não negativo e coincide com a quantidade de nós de dados nos dois percursos.
- Se não há nós de dados, as sentinelas apontam diretamente uma para a outra.

A detecção usa o algoritmo de Floyd, com dois ponteiros que avançam em velocidades diferentes. Essa checagem acontece antes da contagem dos nós, independe do contador e evita laços infinitos durante o diagnóstico. São verificados tanto os ponteiros `proximo` quanto os ponteiros `anterior`. O método tem custo O(n) em tempo e O(1) em memória auxiliar.

| Status | Significado |
|---|---|
| `OK` | As invariantes da representação estão satisfeitas. |
| `CICLO_DETECTADO` | Existe repetição de nós em um percurso de ponteiros. |
| `QUANTIDADE_INCORRETA` | O contador é negativo ou difere do número de nós. |
| `EXTREMIDADE_INCORRETA` | Os ponteiros de extremidade não correspondem à sequência da lista simples. |
| `SENTINELA_INCORRETA` | As sentinelas da lista dupla estão ausentes, coincidem ou têm ligações externas inválidas. |
| `ENCADEAMENTO_INCORRETO` | Na lista dupla, os encadeamentos não são recíprocos ou não chegam à sentinela esperada. |

Alguns códigos são específicos de uma representação. Se houver várias inconsistências, o método retorna o primeiro diagnóstico segundo sua ordem de verificação; não tenta enumerar todos os erros. Ciclos são verificados antes da reciprocidade e da contagem, após verificar a existência das sentinelas na dupla.

A checagem estrutural pressupõe ponteiros nulos ou que apontem para nós vivos; acessos a memória já liberada são diagnosticados pelos sanitizadores. Ela não é chamada automaticamente por cada operação: os testes a utilizam após a operação para verificar as invariantes sem alterar a complexidade esperada dos métodos.

## Atividade de implementação

Implemente em `src/ListaDuplamenteEncadeada.cpp`:

- `inserirInicio`, `inserirFim`, `inserirNaPosicao`, `inserirAntes` e `inserirOrdenado`.
- `removerInicio`, `removerFim`, `removerNaPosicao` e `removerTodos`.
- `buscar` e `elementoNaPosicao`.

Esses métodos lançam `std::runtime_error("Método ainda não implementado.")` no código base. Substitua a exceção pela implementação conforme os contratos. Construtor, destrutor e auxiliares já fornecidos devem ser preservados.

É possível implementar os grupos de inserção, remoção e busca em qualquer ordem: os testes preparam os nós diretamente pelo helper. Métodos de um mesmo grupo podem compartilhar lógica; os testes de cada método montam sua própria situação inicial.

## Complexidades esperadas

| Operação | Complexidade |
|---|---|
| Inserir no início ou fim | O(1) |
| Inserir por posição, antes ou ordenado | O(n) |
| Remover no início | O(1) |
| Remover no fim | O(1) |
| Remover por posição | O(n) |
| Remover todas as ocorrências | O(n) |
| Buscar ou acessar por posição | O(n) |
| Acessar primeiro ou último | O(1) |
| Consultar tamanho ou vazio | O(1) |
| Imprimir | O(n) |
| Checar consistência | O(n), com memória auxiliar O(1) |

## Estrutura de diretórios

```text
.
├── .vscode/   # Configuração portátil de execução no VS Code
├── bin/       # Executáveis e objetos gerados; objetos em bin/obj/
├── header/    # No.h, ConsistenciaStatus.h, interface da lista e helper
├── lib/       # Biblioteca de testes doctest
├── src/       # Implementação da lista e programa de exemplo
├── test/      # Cinco suítes independentes com doctest
├── .gitignore # Arquivos locais e gerados ignorados pelo Git
├── makefile   # Compilação, execução e limpeza
└── README.md  # Orientações da atividade
```

Objetos do programa ficam em `bin/obj/src/`, objetos das suítes em `bin/obj/test/` e a implementação compartilhada pelos testes em `bin/obj/test-src/`.

## Pré-requisitos

- GNU Make.
- Compilador com suporte a C++20, AddressSanitizer e UndefinedBehaviorSanitizer.
- Terminal com `mkdir`, `find` e `rm`, como em Linux, macOS ou um ambiente compatível no Windows.

O doctest já está incluído em `lib/doctest.h`. O compilador padrão é `g++`; para trocar, use, por exemplo, `make CXX=clang++`. A compilação habilita avisos, símbolos de depuração e sanitizadores.

## Compilação e execução

| Comando | Descrição |
|---|---|
| `make` ou `make all` | Compila o programa principal e todas as suítes. |
| `make run` | Compila, se necessário, e executa `bin/main`. |
| `make test` | Compila todas as suítes sem executá-las. |
| `make run-test` | Executa todas as suítes; interrompe se uma falhar. |
| `make clean` | Remove os arquivos gerados, preservando `bin/` e `.gitkeep`. |

```bash
make
make run-test-construtor-tamanho
make run-test-consistencia
make run-test-inserir
make run-test-remover
make run-test-buscar
make clean
```

O programa de exemplo captura exceções e mostra a mensagem ao tentar uma inserção ainda pendente. `ARGS` permite passar argumentos ao programa ou ao doctest.

## Testes

| Arquivo | Comando | Conteúdo |
|---|---|---|
| `TesteConstrutorTamanho.cpp` | `make run-test-construtor-tamanho` | Estado vazio e auxiliares fornecidos. |
| `TesteConsistencia.cpp` | `make run-test-consistencia` | Invariantes, contagem incorreta e ciclos. |
| `TesteInserir.cpp` | `make run-test-inserir` | Todas as formas de inserção, incluindo antes e ordenada. |
| `TesteRemover.cpp` | `make run-test-remover` | Todas as formas de remoção, incluindo todas as ocorrências. |
| `TesteBuscar.cpp` | `make run-test-buscar` | Busca por valor e acesso aos elementos. |

Cada suíte possui um executável próprio `bin/test-...` e compartilha a implementação da lista. Os dois primeiros grupos devem passar no código base; os testes das operações pendentes devem falhar até sua implementação.

### Helpers e independência dos testes

`ListaDuplamenteEncadeadaTestHelper` é uma classe amiga da lista. `preencherLista` aloca e encadeia os nós diretamente, sem chamar as inserções do aluno. `elementos`, `elementosReversos` e `quantidade` permitem verificar os resultados sem depender da busca ou da impressão.

O helper possui uma verificação independente de consistência, baseada em conjuntos de nós visitados. Ela detecta ciclos e valida as invariantes sem chamar `checarConsistencia()`. Assim, os testes também podem detectar erros no próprio verificador da lista. A verificação do helper usa O(n) em memória; isso não altera o contrato O(1) de memória auxiliar de `checarConsistencia`.

Os casos de ciclos e outras corrupções usam alterações temporárias dos atributos, que restauram os valores originais ao terminar o escopo, inclusive quando uma asserção interrompe o teste. Isso permite testar o diagnóstico e destruir a lista normalmente, sem deixar ciclos para o destrutor percorrer.

Os testes conferem a sequência exata, a quantidade e os encadeamentos após cada operação. Erros de posição, referências ausentes e duplicatas rejeitadas devem preservar o estado.

```bash
make run-test-remover ARGS="--list-test-cases"
make run-test-remover ARGS='--test-case="nome do caso"'
```

Os mesmos filtros funcionam nas demais suítes.
