#ifndef LISTA_H
#define LISTA_H

#include <string>

class Lista 
{
    public:
        Lista();
        ~Lista();
        bool inserirInicio(const std::string&);

        bool removerUltimaOcorrencia(const std::string&);

        unsigned long tamanho() const;
        std::string imprimir() const;
   
    private:
        class No
        {
        public:
            ~No();
            
            No( std::string valor );

            std::string valor;

            No* proximo;
        };

        No* primeiro;
        unsigned long quantidade;
};

#endif