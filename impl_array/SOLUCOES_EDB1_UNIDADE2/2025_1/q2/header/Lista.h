#ifndef LISTA_H
#define LISTA_H

#include <string>

class Lista 
{
    public:
        Lista();
        ~Lista();
        bool inserirInicio(const std::string& elemento);

        int removerTodos(const std::string&);

        const std::string& primeiroElemento() const;
        const std::string& ultimoElemento() const;

        unsigned long tamanho() const;
        std::string imprimir() const;
   
    private:
        class No
        {
        public:
            ~No(){

            }
            
            No( std::string valor ){
                this->valor = valor;
                this->proximo = nullptr;
            }

            std::string valor;

            No* proximo;
        };

        No* primeiro;
        No* ultimo;
        unsigned long quantidade;
};

#endif