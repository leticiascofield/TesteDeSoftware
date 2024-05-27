#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <set>
#include "Livro.hpp"
#include "Usuario.hpp"

class Biblioteca{
    private:
        std::set<Livro> livros;
        std::set<Usuario> usuarios;
        void carregarLivros();
        void carregarUsuarios();

    public:
        Biblioteca();

        Usuario getUsuario(const std::string& login) const;
        void salvarLivros() const;
        void salvarUsuarios() const;

        void adicionarLivro(const Livro& l);
        void removerLivro(const Livro& l);
        bool procurarLivro(const Livro& l) const;
        void imprimirLivrosFuncionario() const;

        void imprimirLivrosCliente() const;
        void pegarLivroEmprestado(Usuario& u, Livro& l);

        void adicionarUsuario(const Usuario& u);
        void removerUsuario(const Usuario& u);
        bool autenticarUsuario(const Usuario& u);
        
};

#endif