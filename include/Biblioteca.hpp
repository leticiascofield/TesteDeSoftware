#include <iostream>
#include <vector>
#include <string>
#include "Livro.hpp"

#ifndef BILBIOTECA_H
#define BIBLIOTECA_H

class Biblioteca{
    private:
        std::vector<Livro> livros;
        void setUpBiblioteca();

    public:
        Biblioteca(std::vector<Livro> livros);

        void adicionarLivro(Livro l);
        void removerLivro(Livro l);
        bool procurarLivro(Livro l);
};

#endif