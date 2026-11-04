#include <iostream>
#include <string>
#include "Lista.h"

int main() 
{
  std::string str;

  Lista l;
  while (true) 
  {
    std::cout << "Digite uma palavra para adicionar ao início da Lista" << std::endl;
    std::cin >> str;
    const std::string s = str;
    l.inserirInicio(s);
    l.imprimir();
  }
  return 0;
}
