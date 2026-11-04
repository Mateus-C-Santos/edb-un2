# IMD0029 - EDB1 - 2025.2 - Unidade 2  
## Prof. Eiji Adachi

---

## 📝 **LEIA ANTES DE COMEÇAR**

- Atividade individual sem consulta a pessoas ou materiais (impresso ou eletrônico).
- O valor de cada questão está indicado no enunciado.
- Mantenha celulares e outros eletrônicos desligados durante a prova.
- Desvios éticos resultarão em nota zero nesta unidade.
- Você recebeu diretórios para cada questão, cada um contendo um código base, um arquivo `makefile` e um teste executável, que pode ser executado com `make run-test`.  
  ⚠️ O teste não garante a corretude completa da implementação.
- **Não altere a assinatura das funções fornecidas.** Você pode criar funções auxiliares, mas a assinatura principal deve ser mantida.

---

### 📌 Critérios de Correção

Serão avaliados os seguintes pontos:

- Conformidade com as **assinaturas de função** e estrutura de diretórios.
- **Compilação limpa**, sem erros ou *warnings*.
- **Correta execução dos programas** com os resultados esperados.
- **Complexidade** conforme especificado no enunciado.
- **Qualidade do código**: organização, indentação, nomes adequados, modularização, etc.

---

### 📦 Entregável

- Use a mesma estrutura de diretórios recebida, com os arquivos de solução em cada pasta de questão.
- O diretório raiz deve conter seu nome em letras maiúsculas no formato `PRIMEIRO_NOME_SOBRENOME`. Exemplo:

```
JOAO_SILVA
├── q1
├── q2
└── q3
```

- Compacte tudo em um `.zip` com o mesmo nome: `PRIMEIRO_NOME_SOBRENOME.zip`.
- ❌ Não inclua arquivos `.o` ou executáveis, mas mantenha os arquivos `makefile`. Para limpar o projeto, basta executar `make clean` na raiz do projeto, que ele automaticamente invocará o `make clean` no diretório de cada questão.
- Entregue via SIGAA até o horário estabelecido. Atrasos só serão aceitos com justificativa válida (ex.: instabilidade no SIGAA).

---

## Questão 1 - Valor: 2.0

Implemente o método abaixo na classe `Lista`, que representa uma **lista simplesmente encadeada com apenas um ponteiro para o primeiro nó** (ou seja, sem ponteiro para o último):

```cpp
bool Lista::removerUltimaOcorrencia(const std::string& s);
```

---

### 🔧 Comportamento esperado

- Recebe uma string `s` como parâmetro e remove um nó da lista cujo valor é igual a `s`. Se a remoção for feita com sucesso, a função retorna `true`; caso contrário, retorna `false`.
- Caso existam mais de um nó com valor igual a `s`, apenas um nó deve ser removido; e o nó a ser removido é o último nó com valor igual a `s`, considerando o percurso do início ao fim da lista. 
- Tentativas de remoção em lista vazia devem retornar `false`.
- ⏱️ Complexidade de tempo: **Θ(n)**
- ❌ Não usar estruturas auxiliares como `stack`, `array`, `vector`, etc.
---

### 📌 Exemplo de uso

Lista original: `{S, S, P, S, F, C}`

| Chamada do método        | Estado esperado após execução       | Retorno |
|--------------------------|--------------------------------------|---------|
| `removerUltimaOcorrencia("S")`   | `{S, S, P, F, C}`        | `true`  |
| `removerUltimaOcorrencia("F")`   | `{S, S, P, S, C}`        | `true`  |
| `removerUltimaOcorrencia("E")`   | `{S, S, P, S, F, C}`        | `false` |
| `removerUltimaOcorrencia("E")`   | `{}`        | `false` |

---

### 📁 Onde implementar?

📄 Arquivo:  
```
q1/src/Lista.cpp
```

---
<div style="page-break-after: always;"/>

## Questão 2 - Valor: 2.0

Implemente o método abaixo na classe `ListaDuplamenteEncadeada`, que representa uma **lista duplamente encadeada com sentinelas cabeça e cauda**:

```cpp
bool ListaDuplamenteEncadeada::buscar_e_mover(const std::string& s);
```

---

### 🔧 Comportamento esperado

- Recebe uma string `s` como parâmetro e realiza uma busca na lista encadeada, retornando `true` caso exista algum nó na lista com valor igual a `s`, ou `false`, caso contrário.
- Caso a busca obtenha sucesso, o nó cujo valor é igual a `s` deve ser movido para o início da lista, isto é, ele deve ser desencadeado de sua posição original e reencadeado após a cabeça (ou seja, passa a ser o primeiro nó da lista de dados).
- Se o nó já estiver na primeira posição, a lista deve permanecer inalterada e retornar `true`, não devendo tentar mover outro nó cujo valor seja também igual a `s`.
- Neste método, não deve ocorrer qualquer operação de alocação ou liberação dinâmica de memória (i.e., não use `new` nem `delete`).
- ⏱️ Complexidade de tempo: **Θ(n)**
- ❌ Não usar estruturas auxiliares como `stack`, `array`, `vector`, etc.
---

### 📌 Exemplo de uso
Lista original: `{S, P, F, S, C}` 

| Chamada do método      | Estado esperado após execução | Retorno |
|----------------------------------------|------------------------|--------------------------------|---------|
| `buscar_e_mover("S");`     | `{S, P, F, S, C}`          | `true`     |
| `buscar_e_mover("F");`     | `{F, S, P, S, C}`          | `true`     |
| `buscar_e_mover("C");`     | `{C, S, P, F, S}`          | `true`     |
| `buscar_e_mover("a");`     | `{S, P, F, S, C}`          | `false`     |
---

### 📁 Onde implementar?

📄 Arquivo:  
```
q2/src/ListaDuplamenteEncadeada.cpp
```

---
<div style="page-break-after: always;"/>

## Questão 3 - Valor: 2.0

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
- Tentativas de enfileirar elementos na fila cheia deve lançar uma exceção do tipo `std::overflow_error`.
- Tentativas de desenfileirar elementos na fila vazia deve lançar uma exceção do tipo `std::underflow_error`.
- Tentativas de acessar o elemento da frente de uma fila vazia deve lançar uma exceção do tipo `std::underflow_error`.
- ⏱️ Complexidade de tempo (todas operações): **Θ(1)**

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
```
{ 20 30 40 50 }
```

---

### 📁 Onde implementar?

📄 Arquivo:
```
q3/header/Fila.h
```