#include "ListaSimplesmenteEncadeada.h"
#include <iostream>
#include <stdexcept>

int main()
{
    ListaSimplesmenteEncadeada lista;
    std::cout << "Lista: " << lista.imprimir() << "\nTamanho: " << lista.tamanho() << '\n';
    std::cout << "Digite uma palavra para inserir no início (fim da entrada para sair).\n";
    std::string elemento;
    while (std::cin >> elemento)
    {
        try
        {
            lista.inserirInicio(elemento);
            std::cout << lista.imprimir() << '\n';
        }
        catch (const std::exception& erro)
        {
            std::cout << "Erro: " << erro.what() << '\n';
        }
    }
}
