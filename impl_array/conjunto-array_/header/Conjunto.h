#ifndef CONJUNTO_H
#define CONJUNTO_H

class Conjunto 
{
    friend class ConjuntoTestHelper;

    public:
        Conjunto(const int capacidade);
        ~Conjunto();
        bool inserir(int elemento);
        bool remover(int elemento);
        bool contem(int elemento) const;
        int tamanho() const;
        void imprimir() const;
   
    private:
        int *elementos;
        int capacidade;
        int quantidade;
};

#endif
