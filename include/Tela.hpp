#ifndef TELA_H
#define TELA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "Biblioteca.hpp"

class Tela{
    public:
        void limparTela();
        void pausarTela();

        void telaInicial(Biblioteca& biblioteca);
        void telaFuncionalidadesFuncionario(Biblioteca& biblioteca);
        void telaFuncionalidadesCliente(Biblioteca& biblioteca, Usuario& u);

};

#endif