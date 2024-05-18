#ifndef LIVRO_H
#define LIVRO_H

#include <string>
#include <iomanip>
#include <sstream>

class Livro{
    private:
        std::string nome;
        int quantidade;

    public:
        Livro();
        Livro(std::string nome, int quantidade);
        std::string getNome() const;
        int getQuantidade() const;
        bool operator==(const Livro& l) const;
        bool operator<(const Livro& l) const;

};

#endif