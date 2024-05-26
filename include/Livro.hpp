#ifndef LIVRO_H
#define LIVRO_H

#include <string>
#include <iomanip>
#include <sstream>

class Livro{
    private:
        std::string nome;
        int quantidade;
        int quantidadeDisponivel;

    public:
    Livro(std::string nome, int quantidade);
        Livro(std::string nome, int quantidade, int quantidadeDisponivel);
        std::string getNome() const;
        int getQuantidade() const;
        int getQuantidadeDisponivel() const;
        bool operator==(const Livro& l) const;
        bool operator<(const Livro& l) const;

};

#endif