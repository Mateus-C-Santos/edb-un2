#include <iostream>
#include "ListaDuplamenteEncadeada.h"

int main()
{
    ListaDuplamenteEncadeada l;

    l.inserirInicio("SPFC!");

    std::cout << "Tamanho " << l.tamanho() << std::endl;
    std::cout << "Conteúdo: " << l.imprimir() << std::endl;

    return 0;
}