#include "Biblioteca.hpp"
#include <iostream>

Biblioteca::Biblioteca() {
    setUpBiblioteca();
}

void Biblioteca::setUpBiblioteca() {
    Livro livro1("Dracula", 3);
    livros.insert(livro1);
    Livro livro2("Jane Eyre", 2);
    livros.insert(livro2);
    Livro livro3("O Conde de Monte Cristo", 3);
    livros.insert(livro3);
}

void Biblioteca::adicionarLivro(const Livro& l) {
    livros.insert(l);
}

void Biblioteca::removerLivro(const Livro& l) {
    auto it = livros.find(l);
    if (it != livros.end()) {
        livros.erase(it);
    }
}

bool Biblioteca::procurarLivro(const Livro& l) const {
    auto it = livros.find(l);
    return it != livros.end();
}

void Biblioteca::imprimirLivros() const {
    for (const auto& livro : livros) {
        std::cout << livro.getNome() << " - Quantidade: " << livro.getQuantidade() << std::endl;
    }
}
