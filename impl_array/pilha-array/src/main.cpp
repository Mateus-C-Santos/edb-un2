#include <iostream>
#include "Pilha.h"

int main() 
{
  int num;

  Pilha<std::string> pilha(10);
  while (true) 
  {
    std::cout << "Digite um numero inteiro positivo adicionar à pilha, zero para desempilhar, ou um número negativo para terminar o programa." << std::endl;
    std::cin >> num;
    if (num < 0) 
    {
      std::cout << "Terminando o programa." << std::endl;
      break;
    }
    else if(num == 0)
    {
      pilha.desempilhar();
    }
    else
    {
      pilha.empilhar(std::to_string(num));
    }
        
    std:: cout << pilha.imprimir() << std::endl;
  }
  return 0;
}
