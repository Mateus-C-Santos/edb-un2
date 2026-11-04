# IMD0029 - EDB1 - 2026.1 - Unidade 2  
## Prof. Eiji Adachi

---

## 📝 **LEIA ANTES DE COMEÇAR**

- Atividade individual sem consulta a pessoas ou materiais (impresso ou eletrônico).
- O valor de cada questão está indicado no enunciado.
- Mantenha celulares e outros eletrônicos desligados durante a prova.
- Desvios éticos resultarão em nota zero nesta unidade.
- Você recebeu diretórios para cada questão, cada um contendo um código base, um arquivo `makefile` e um teste executável, que pode ser executado com `make run-test`.  
  - ⚠️ **Importante:** O teste não garante a corretude completa da implementação.
- **Não altere a assinatura das funções fornecidas.** Você pode criar funções auxiliares, mas a assinatura principal deve ser mantida.

---

## 📌 **Critérios de Correção**

Serão avaliados os seguintes pontos:

- Conformidade com as **assinaturas de função** e estrutura de diretórios.
- **Compilação limpa**, sem erros ou *warnings*.
- **Correta execução dos programas** com os resultados esperados.
- **Complexidade** conforme especificado no enunciado.
- **Qualidade do código**: organização, indentação, nomes adequados, modularização, etc.

---

## 📦 **Entregável**

- Use a mesma estrutura de diretórios recebida, com os arquivos de solução em cada pasta de questão.
- O diretório raiz deve conter seu nome em letras maiúsculas no formato `PRIMEIRO_NOME_SOBRENOME`. Exemplo:

```text
JOAO_SILVA
├── lib
├── q1
├── q2
├── q3
└── makefile
```

- Compacte tudo em um `.zip` com o mesmo nome: `PRIMEIRO_NOME_SOBRENOME.zip`.
- ❌ Não inclua arquivos `.o` ou executáveis, mas mantenha os arquivos `makefile`. Para limpar o projeto, basta executar `make clean` na raiz do projeto, que ele automaticamente invocará o `make clean` no diretório de cada questão.
- Entregue via SIGAA até o horário estabelecido. Atrasos só serão aceitos com justificativa válida (ex.: instabilidade no SIGAA).

---

<div style="page-break-after: always;"/>

## **Questão 1 - Valor: 2.0**

Implemente o método abaixo na classe `Lista`, que representa uma **lista simplesmente encadeada**:

```cpp
int Lista::contarIntersecao(const Lista& outra) const;
```

---

### 🔧 Comportamento esperado

O método deve contar quantos elementos da lista atual (`this`) também aparecem na lista recebida como parâmetro (`outra`). Em outras palavras, o método deve retornar a quantidade de elementos que pertencem simultaneamente às duas listas.

Considere que:

- Cada lista não possui elementos repetidos.
- As listas não devem ser modificadas.
- Se uma das listas estiver vazia, o método deve retornar `0`.
- ⏱️ Complexidade de tempo esperada: **Θ(n · m)**, em que:
  - `n` é o tamanho da lista atual;
  - `m` é o tamanho da lista recebida como parâmetro.
- ❌ Não usar estruturas auxiliares como `stack`, `array`, `vector`, `set`, `map`, etc.

---

### 📌 Exemplo de uso

| Lista `this` | Lista `outra` | Valor retornado |
|---|---|---:|
| `{}` | `{S, P, F, C}` | `0` |
| `{S, P, F, C}` | `{}` | `0` |
| `{S, P, F, C}` | `{A, B, E, D}` | `0` |
| `{S, P, F, C}` | `{S, A, C, D}` | `2` |

---

### 📁 Onde implementar?

📄 Arquivo:

```text
q1/src/Lista.cpp
```

---

<div style="page-break-after: always;"/>

## **Questão 2 - Valor: 2.0**

Implemente o método abaixo na classe `ListaDuplamenteEncadeada`, que representa uma **lista duplamente encadeada com sentinelas cabeça e cauda**:

```cpp
int ListaDuplamenteEncadeada::removerIntersecao(const ListaDuplamenteEncadeada& outra);
```

---

### 🔧 Comportamento esperado

O método deve remover da lista atual (`this`) os nós cujos valores também aparecem na lista recebida como parâmetro (`outra`) e retornar a quantidade de nós removidos da lista atual.

Considere que:
* Cada lista não possui elementos repetidos.
* A lista atual (`this`) pode ser modificada.
* A lista recebida como parâmetro (`outra`) não deve ser modificada.
* Se a lista atual (`this`) estiver vazia, o método deve retornar 0.
* Se a lista `outra` estiver vazia, o método deve retornar 0 e a lista atual deve permanecer inalterada.
* ⏱️ Complexidade de tempo esperada: **Θ(n · m)**, em que:
    * n é o tamanho da lista atual;
    * m é o tamanho da lista recebida como parâmetro.
- Os nós removidos devem ser corretamente liberados da memória usando `delete`.
- ❌ Não usar estruturas auxiliares como `stack`, `array`, `vector`, `set`, `map`, etc.

---

### 📌 Exemplo de uso

| Lista `this` antes | Lista `outra` | Lista `this` após | Valor retornado |
|---|---|---|---:|
| `{}` | `{S, P, F, C}` | `{}` | `0` |
| `{S, P, F, C}` | `{}` | `{S, P, F, C}` | `0` |
| `{S, P, F, C}` | `{A, B, E, D}` | `{S, P, F, C}` | `0` |
| `{S, P, F, C}` | `{S, A, C, D}` | `{P, F}` | `2` |
| `{S, P, F, C}` | `{S, P, F, C, A}` | `{}` | `4` |

---

### 📁 Onde implementar?

📄 Arquivo:

```text
q2/src/ListaDuplamenteEncadeada.cpp
```

---

<div style="page-break-after: always;"/>

## **Questão 3 - Valor: 2.0**

Implemente os métodos abaixo na classe `Fila<T>`, que representa uma **fila genérica implementada com array**:

```cpp
T frente(); // Retorna o primeiro elemento da fila (sem removê-lo)
void enfileirar(T elem);  // Insere um elemento no final da fila
T desenfileirar();  // Remove e retorna o primeiro elemento da fila
```

---

### 🔧 Comportamento esperado

- A fila deve seguir a estratégia **FIFO (First-In, First-Out)**.
- A implementação deve utilizar array circular.
- Tentativas de enfileirar elementos na fila cheia devem lançar uma exceção do tipo `std::overflow_error`.
- Tentativas de desenfileirar elementos na fila vazia devem lançar uma exceção do tipo `std::underflow_error`.
- Tentativas de acessar o elemento da frente de uma fila vazia devem lançar uma exceção do tipo `std::underflow_error`.
- Chamadas ao método `frente()` não removem elementos e, portanto, não alteram o estado da fila.
- ❌ Não usar estruturas prontas da STL para implementar a fila, como `std::queue`, `std::deque` ou `std::vector`.
- ⏱️ Complexidade de tempo esperada para todas as operações: **Θ(1)**.

---

### 📌 Exemplo de uso

```cpp
Fila<int> f(4);
f.enfileirar(10);
f.enfileirar(20);
f.enfileirar(30);
f.desenfileirar(); // remove 10
f.enfileirar(40);
f.enfileirar(50);
```

Estado final da fila:

```text
{ 20 30 40 50 }
```

---

### 📁 Onde implementar?

📄 Arquivo:

```text
q3/header/Fila.h
```
