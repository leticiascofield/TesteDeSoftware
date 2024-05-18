#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <set>
#include "Livro.hpp"

class Biblioteca{
    private:
        std::set<Livro> livros;
        void setUpBiblioteca();
        void carregarLivros();
        void salvarLivros() const;

    public:
        Biblioteca();
        void adicionarLivro(const Livro& l);
        void removerLivro(const Livro& l);
        bool procurarLivro(const Livro& l) const;
        void imprimirLivros() const;
        
};

#endif