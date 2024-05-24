#include <iostream>
#include <string>
#include <cstdlib>
#include "Biblioteca.hpp"
#include "Usuario.hpp"
#include "Tela.hpp"


int main (){
    Tela tela;
    Biblioteca biblioteca;

    tela.telaInicial(biblioteca);

    return 0;
}
