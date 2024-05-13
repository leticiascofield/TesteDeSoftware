#ifndef LIVRO_H
#define LIVRO_H

#include <iostream>
#include <string>

class Livro{
    private:
        std::string nome;
        int quantidade;

    public:
        Livro();
        Livro(std::string nome, int quantidade);
        std::string getNome();
        int getQuantidade();

        bool operator==(Livro l) const {
            return this->nome == l.nome;
        }
};

#endif