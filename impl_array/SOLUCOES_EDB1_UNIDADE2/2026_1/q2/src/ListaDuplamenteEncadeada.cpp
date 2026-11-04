#include "../header/ListaDuplamenteEncadeada.h"
#include <sstream>
#include <stdexcept>
#define __CHECK_INTEGRIDADE__ 1

int ListaDuplamenteEncadeada::removerIntersecao(const ListaDuplamenteEncadeada& outra)
{
    // Se qualquer lista estiver vazia, não há nada a remover.
    if (this->vazia() || outra.vazia())
    {
        return 0;
    }

    int removidos = 0;
    No<std::string>* atual = this->cabeca->proximo;

    while (atual != this->cauda)
    {
        bool encontrou = false;

        // Procuramos o valor do nó atual na lista recebida como parâmetro.
        for (No<std::string>* busca = outra.cabeca->proximo;
             busca != outra.cauda;
             busca = busca->proximo)
        {
            if (atual->valor == busca->valor)
            {
                encontrou = true;
                break;
            }
        }

        if (encontrou)
        {
            // Guardamos o próximo, pois o nó atual será liberado.
            No<std::string>* proximo = atual->proximo;

            // Reconectamos o anterior ao próximo, removendo atual da cadeia.
            atual->anterior->proximo = atual->proximo;
            atual->proximo->anterior = atual->anterior;

            delete atual; // libera a memória do nó removido
            --this->quantidade;
            ++removidos;

            atual = proximo;
        }
        else
        {
            atual = atual->proximo;
        }
    }

    // A lista 'outra' foi usada somente para consulta e permanece intacta.
    return removidos;
}













/**
 * 
 * !!!!! PERIGO !!!!! 
 * NÃO MODIFIQUE O CÓDIGO ABAIXO 
 * !!!!! PERIGO !!!!! 
 */

ListaDuplamenteEncadeada::ListaDuplamenteEncadeada() {
    this->cabeca = new No<std::string>("CABECA_NAO_DEVE_SER_ACESSADA");
    this->cauda = new No<std::string>("CAUDA_NAO_DEVE_SER_ACESSADA");
    
    this->cabeca->proximo = this->cauda;
    this->cabeca->anterior = nullptr;

    this->cauda->proximo = nullptr;
    this->cauda->anterior = this->cabeca;

    this->quantidade = 0;
}

ListaDuplamenteEncadeada::~ListaDuplamenteEncadeada() {
    auto aux = this->cabeca->proximo;
    while (aux != this->cauda) {
        auto tmp = aux;
        aux = aux->proximo;
        delete tmp;
    }

    delete this->cabeca;
    delete this->cauda;

	this->cabeca = nullptr;
	this->cauda = nullptr;
	this->quantidade = 0;
}

int ListaDuplamenteEncadeada::tamanho() const {
    return this->quantidade;
}

bool ListaDuplamenteEncadeada::vazia() const {
    return this->quantidade == 0;
}

bool ListaDuplamenteEncadeada::inserirInicio(std::string s) {
    auto novo = new No(s);
    
    novo->anterior = cabeca;
    novo->proximo = cabeca->proximo;

    novo->proximo->anterior = novo;
    novo->anterior->proximo = novo;

    ++quantidade;
    return true;
}

std::string ListaDuplamenteEncadeada::imprimir() const {
    std::stringstream resultado;
    No<std::string>* n = this->cabeca->proximo;

    if (n == this->cauda) {
        return "{}";
    } else {
        resultado << "{";
        resultado << n->valor;
        n = n->proximo;
    }

    for (; n != this->cauda; n = n->proximo) {
        resultado << ", " << n->valor;
    }

    resultado << "}";

    return resultado.str();
}

StatusDaLista ListaDuplamenteEncadeada::checarConsistencia() const {
    if (this->cabeca == nullptr) {
        return CABECA_NULA;
    } else if (this->cabeca->proximo == nullptr) {
        return CABECA_PROXIMO_NULO;
    } else if (this->cabeca->proximo->anterior != this->cabeca) {
        return ENCADEAMENTO_INCORRETO;
    } else if (this->cabeca->anterior != nullptr) {
        return CABECA_ANTERIOR;
    }

    if (this->cauda == nullptr) {
        return CAUDA_NULA;
    } else if (this->cauda->anterior == nullptr) {
        return CAUDA_ANTERIOR_NULO;
    } else if (this->cauda->anterior->proximo != this->cauda) {
        return ENCADEAMENTO_INCORRETO;
    } else if (this->cauda->proximo != nullptr) {
        return CAUDA_PROXIMO;
    }

    if (this->vazia()) {
        if (this->cabeca->proximo != this->cauda) {
            return CABECA_CAUDA;
        }
        if (this->cabeca != this->cauda->anterior) {
            return CABECA_CAUDA;
        }
    } else {
		int contagem = 0;
        for (No<std::string>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo) {
			if (i->proximo == nullptr || i->anterior == nullptr) {
				return ENCADEAMENTO_INCORRETO;
			}
            if (i->proximo->anterior != i) {
                return ENCADEAMENTO_INCORRETO;
            }
            if (i->anterior->proximo != i) {
                return ENCADEAMENTO_INCORRETO;
            }
			contagem++;
        }

		if (contagem != this->quantidade) {
            return QUANTIDADE_DIFERENTE; 
        }
    }

    return OK;
}
