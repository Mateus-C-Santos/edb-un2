//
//  Lista.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Lista__
#define __Lista__

#include "No.h"
#include <string>

typedef enum {
    OK ,
    CABECA_NULA,
    CAUDA_NULA,
    CABECA_ANTERIOR,
    CABECA_PROXIMO_NULO,
    CAUDA_PROXIMO,
    CAUDA_ANTERIOR_NULO,
    CABECA_CAUDA,
    ENCADEAMENTO_INCORRETO,
    QUANTIDADE_DIFERENTE 
} StatusDaLista ;

class Lista {
private:
    No<std::string>* cabeca;
    No<std::string>* cauda;
    int quantidade;
    
public:
    Lista(void);
    ~Lista(void);
    
    bool inserirInicio(std::string);

    bool moverParaInicio(std::string);

    const std::string primeiroElemento() const;
    const std::string ultimoElemento() const;
    
    StatusDaLista checarConsistencia(void) const;
    
    std::string imprimir(void) const;
    
    bool vazia(void) const;
    int tamanho(void) const;
};

#endif 
