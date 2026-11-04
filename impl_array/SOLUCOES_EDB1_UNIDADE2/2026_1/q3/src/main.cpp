#include <iostream>
#include "../header/Fila.h"

int main()
{
    int num;

    Fila<int> fila(10);
    while (true)
    {
        std::cout << "Digite um numero inteiro positivo para adicionar à fila, zero para remover, ou um número negativo para terminar o programa." << std::endl;
        std::cin >> num;
        if (num < 0)
        {
            std::cout << "Terminando o programa." << std::endl;
            break;
        }
        else if (num == 0)
        {
            try
            {
                fila.desenfileirar();
            }
            catch (const std::underflow_error& e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
        }
        else
        {
            try
            {
                fila.enfileirar(num);
            }
            catch (const std::overflow_error& e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
        }

        std::cout << fila.imprimir() << std::endl;
    }
    return 0;
}
