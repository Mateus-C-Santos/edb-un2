#define __CHECK_INTEGRIDADE__ 1 
#include "../header/Lista.h"
#include <sstream> // para implementar o método imprimir ​​
#include <stdexcept>
#include <vector>

bool Lista::moverParaInicio(std::string str)
{
    // 1. Procuramos a primeira ocorrência, começando no primeiro nó real.
    No<std::string>* atual = this->cabeca->proximo;

    while (atual != this->cauda && atual->valor != str)
    {
        atual = atual->proximo;
    }

    // Chegamos à sentinela cauda: o valor não existe na lista.
    if (atual == this->cauda)
    {
        return false;
    }

    // Se já é o primeiro nó, a busca teve sucesso e nada precisa mudar.
    if (atual == this->cabeca->proximo)
    {
        return true;
    }

    // 2. Desencadeamos o nó da posição atual.
    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;

    // 3. Reencadeamos o MESMO nó logo depois da sentinela cabeça.
    atual->anterior = this->cabeca;
    atual->proximo = this->cabeca->proximo;
    this->cabeca->proximo->anterior = atual;
    this->cabeca->proximo = atual;

    // Não houve new, delete nem alteração da quantidade de nós.
    return true;
}












// Não alterar o código abaixo
Lista::Lista(){this->cabeca=new No<std::string>("CABECA_NAO_DEVE_SER_ACESSADA");this->cauda=new No<std::string>("CAUDA_NAO_DEVE_SER_ACESSADA");this->cabeca->proximo=this->cauda;this->cabeca->anterior=nullptr;this->cauda->proximo=nullptr;this->cauda->anterior=this->cabeca;this->quantidade=0;}

Lista::~Lista(){auto a=this->cabeca->proximo;while(a!=this->cauda){auto t=a;a=a->proximo;delete t;}delete this->cabeca;delete this->cauda;this->cabeca=nullptr;this->cauda=nullptr;this->quantidade=0;}

const std::string Lista::primeiroElemento() const{if(this->quantidade==0)throw std::out_of_range("Lista vazia");return this->cabeca->proximo->valor;}

const std::string Lista::ultimoElemento() const{if(this->quantidade==0)throw std::out_of_range("Lista vazia");return this->cauda->anterior->valor;}

int Lista::tamanho() const{return this->quantidade;}

bool Lista::vazia() const{return this->quantidade==0;}

bool Lista::inserirInicio(std::string x){auto n=new No<std::string>(x);n->anterior=this->cabeca;n->proximo=this->cabeca->proximo;n->anterior->proximo=n;n->proximo->anterior=n;this->quantidade++;return true;}

std::string Lista::imprimir() const {std::stringstream r;auto x=this->cabeca->proximo;if(x==this->cauda)return"{}";else{r<<x->valor;x=x->proximo;}for(;x!=this->cauda;x=x->proximo)r<<"<->"<<x->valor;return r.str();}

StatusDaLista Lista::checarConsistencia() const{if(this->cabeca==nullptr)return CABECA_NULA;else if(this->cabeca->proximo==nullptr)return CABECA_PROXIMO_NULO;else if(this->cabeca->proximo->anterior!=this->cabeca)return ENCADEAMENTO_INCORRETO;else if(this->cabeca->anterior!=nullptr)return CABECA_ANTERIOR;if(this->cauda==nullptr)return CAUDA_NULA;else if(this->cauda->anterior==nullptr)return CAUDA_ANTERIOR_NULO;else if(this->cauda->anterior->proximo!=this->cauda)return ENCADEAMENTO_INCORRETO;else if(this->cauda->proximo!=nullptr)return CAUDA_PROXIMO;if(this->quantidade==0){if(this->cabeca->proximo!=this->cauda)return CABECA_CAUDA;if(this->cabeca!=this->cauda->anterior)return CABECA_CAUDA;}else{int x=0;for(auto i=this->cabeca->proximo;i!=this->cauda;i=i->proximo){if(i->proximo==nullptr||i->anterior==nullptr)return ENCADEAMENTO_INCORRETO;if(i->proximo->anterior!=i)return ENCADEAMENTO_INCORRETO;if(i->anterior->proximo!=i)return ENCADEAMENTO_INCORRETO;x++;}if(x!=this->quantidade)return QUANTIDADE_DIFERENTE;}return OK;}