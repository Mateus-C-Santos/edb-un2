# Soluções comentadas — EDB1 / Estruturas de Dados Básicas — Unidade 2

Este pacote reúne as provas práticas de **2025.1, 2025.2 e 2026.1**, com as implementações inseridas nos arquivos originais e comentários explicando o raciocínio.

## Como abrir e testar

Abra no VS Code a pasta de um período, por exemplo `2026_1`. No terminal, execute:

```bash
make clean all
make clean run-test
```

O primeiro comando compila os programas principais e os testes; o segundo executa os testes automatizados fornecidos com a prova. Também é possível entrar em `q1`, `q2` ou `q3` e executar os comandos do `makefile` daquela questão.

As soluções estão nos arquivos indicados pelos enunciados (`src/Lista.cpp`, `src/ListaDuplamenteEncadeada.cpp` ou `header/Fila.h`). Os `makefiles`, enunciados, cabeçalhos, testes e bibliotecas originais foram preservados. Executáveis, arquivos objeto e logs de compilação foram removidos.

---

# Antes de programar: como raciocinar sobre listas

Em questões de listas encadeadas, faça quatro perguntas antes de escrever código:

1. **Qual nó estou procurando?** Percorro a lista usando um ponteiro `atual`.
2. **Preciso do nó anterior?** Em lista simplesmente encadeada, quase sempre sim, porque é ele que permite retirar ou religar `atual`.
3. **Estou removendo ou apenas movendo?** Remover exige `delete` e atualização da quantidade. Mover exige somente alterar ligações; não se usa `new` nem `delete`.
4. **Quais são os casos especiais?** Lista vazia, primeiro nó, último nó e valor inexistente.

Em uma lista simplesmente encadeada, cada nó só aponta para o próximo. Para remover um nó do meio, o anterior passa a apontar para o próximo do nó removido:

```cpp
anterior->proximo = atual->proximo;
```

Se o nó removido for o primeiro, atualize `primeiro`. Se existir ponteiro `ultimo` e o nó removido for o último, atualize `ultimo`. Quando removemos, salve o próximo nó antes do `delete`.

Em uma lista duplamente encadeada, cada nó tem `anterior` e `proximo`. Para retirar um nó, reconecte seus vizinhos:

```cpp
atual->anterior->proximo = atual->proximo;
atual->proximo->anterior = atual->anterior;
```

As sentinelas `cabeca` e `cauda` são nós especiais que marcam o começo e o fim; elas não são elementos de dados. Para mover um nó ao início, primeiro desconecte-o e depois conecte o mesmo nó logo após `cabeca`.

---

# Prova 2025.1

## Questão 1 — `moverParaInicio`

**Estrutura:** lista duplamente encadeada com sentinelas `cabeca` e `cauda`.

**Como resolver:** comece no primeiro nó real (`cabeca->proximo`) e procure a primeira ocorrência. Se chegar à `cauda`, retorne `false`. Se já estiver no primeiro lugar, retorne `true` sem mexer. Caso esteja no meio ou no fim, desconecte-o dos vizinhos e conecte-o imediatamente depois de `cabeca`.

**Detalhe importante:** o enunciado manda mover o nó existente. Não crie outro nó nem apague o encontrado. A quantidade de nós não muda.

**Complexidade:** Θ(n), por causa da busca linear; as alterações dos ponteiros são Θ(1).

## Questão 2 — `removerTodos`

**Estrutura:** lista simplesmente encadeada com ponteiros `primeiro` e `ultimo`.

**Divergência no material:** o texto do enunciado fala em `int val`, mas o cabeçalho (`Lista.h`) e os testes entregues declaram e usam `removerTodos(const std::string&)`. A solução mantém a assinatura do código-base para ser compatível com os testes da prova.

**Como resolver:** percorra a lista com `atual` e `anterior`. Quando o valor não for o procurado, avance os dois ponteiros. Quando for, retire `atual` da cadeia, libere-o com `delete`, diminua `quantidade` e aumente o contador. Quando remove, não avance `anterior`, pois o próximo nó ainda precisa ser examinado.

**Casos especiais:** ao remover o primeiro nó, atualize `primeiro`; ao remover o último, atualize `ultimo`. Se todos forem removidos, ambos ficam `nullptr`.

**Complexidade:** Θ(n), pois cada nó é visitado uma vez.

## Questão 3 — `Fila<T>` com array circular

A fila segue **FIFO**: o primeiro elemento inserido é o primeiro removido.

- `inicio`: índice do primeiro elemento válido.
- `fim`: índice da próxima posição livre para inserção.
- `quantidade`: número de elementos armazenados.
- `capacidade`: tamanho máximo do array.

Para inserir, escreva em `elementos[fim]` e avance `fim` usando `(fim + 1) % capacidade`. Para remover, copie `elementos[inicio]` e avance `inicio` usando `(inicio + 1) % capacidade`. O operador `%` faz o índice voltar a zero quando chega ao fim do array.

`frente()` só consulta `elementos[inicio]` e não altera a fila. Inserir em fila cheia lança `std::overflow_error`; consultar/remover fila vazia lança `std::underflow_error`.

**Complexidade:** Θ(1) para `frente`, `enfileirar` e `desenfileirar`.

---

# Prova 2025.2

## Questão 1 — `removerUltimaOcorrencia`

**Estrutura:** lista simplesmente encadeada com apenas o ponteiro para o primeiro nó.

**Como resolver:** não pare na primeira ocorrência, pois o pedido é remover a última. Percorra a lista inteira e, sempre que encontrar o valor, guarde o endereço do nó e também o endereço do nó anterior. Ao terminar, você terá guardado a última ocorrência. Retire-a da cadeia e use `delete`.

**Caso especial:** se a última ocorrência for o primeiro nó, o ponteiro anterior será `nullptr`; nesse caso, atualize `primeiro`.

**Complexidade:** Θ(n), com uma única passagem.

## Questão 2 — `buscar_e_mover`

**Estrutura:** lista duplamente encadeada com sentinelas.

**Como resolver:** procure a primeira ocorrência. Se não encontrar, retorne `false`; se já estiver no início, retorne `true`. Caso contrário, desconecte o nó dos vizinhos e reconecte o mesmo nó logo depois de `cabeca`.

**Detalhe importante:** é movimentação, não remoção. Não use `new` ou `delete`, e não altere `quantidade`.

**Complexidade:** Θ(n), pela busca linear.

## Questão 3 — `Fila<T>` com array circular

Use os mesmos três índices/contadores da explicação da questão 3 de 2025.1. `inicio` indica a frente, `fim` indica onde inserir, e ambos avançam com o operador `%`. A implementação também trata as exceções de fila cheia e vazia exigidas pelos testes deste período.

---

# Prova 2026.1

## Questão 1 — `contarIntersecao`

**Estrutura:** duas listas simplesmente encadeadas, sem elementos repetidos.

**Como resolver:** para cada nó da lista atual, percorra a outra lista procurando o mesmo valor. Quando encontrar, some 1 e interrompa a busca interna com `break`, para contar cada elemento da lista atual no máximo uma vez.

**Detalhe importante:** não altere nenhuma lista e não use estrutura auxiliar. Os dois percursos aninhados resultam na complexidade Θ(n · m), conforme pedido.

## Questão 2 — `removerIntersecao`

**Estrutura:** duas listas duplamente encadeadas com sentinelas.

**Como resolver:** para cada nó da lista atual, procure seu valor na lista `outra`. Se encontrar, salve o próximo nó, reconecte os vizinhos do nó atual, libere-o com `delete`, atualize `quantidade` e incremente o contador. Se não encontrar, avance normalmente.

**Detalhes importantes:** salve `atual->proximo` antes do `delete`, pois não se deve acessar o nó depois de liberá-lo. A lista `outra` é apenas consultada e permanece intacta.

**Complexidade:** Θ(n · m), pois cada elemento da lista atual pode exigir percorrer a outra lista.

## Questão 3 — `Fila<T>` com array circular

A lógica é a mesma das filas anteriores. Também foi acrescentado o método auxiliar `imprimir()`, porque o `main.cpp` fornecido nesta prova chama esse método, embora ele não existisse no `Fila.h` original. As três operações pedidas no enunciado mantêm suas assinaturas.

---

# Resumo das complexidades

| Operação | Complexidade |
|---|---:|
| Mover um nó encontrado para o início | Θ(n) |
| Remover todos os nós com determinado valor | Θ(n) |
| Remover a última ocorrência | Θ(n) |
| Buscar e mover para o início | Θ(n) |
| Contar interseção entre duas listas | Θ(n · m) |
| Remover interseção entre duas listas | Θ(n · m) |
| `frente()` na fila circular | Θ(1) |
| `enfileirar()` na fila circular | Θ(1) |
| `desenfileirar()` na fila circular | Θ(1) |

## Dica para estudar

Leia os comentários do código e tente reescrever cada função sem olhar. Depois execute `make clean run-test`. Ao corrigir erros, confira principalmente: lista vazia, primeiro nó, último nó, valor inexistente, fila cheia, fila vazia e o retorno do índice circular ao começo do array.
