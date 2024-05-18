#include "Biblioteca.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Biblioteca::Biblioteca() {
    setUpBiblioteca();
}

void Biblioteca::setUpBiblioteca() {
    carregarLivros();
}

void Biblioteca::carregarLivros() {
    std::ifstream inFile("livros.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string nome;
            int quantidade;
            if (iss >> std::ws && std::getline(iss, nome, '"') && std::getline(iss, nome, '"') >> quantidade) {
                Livro livro(nome, quantidade);
                livros.insert(livro);
            }
        }
        inFile.close();
    }
}

void Biblioteca::salvarLivros() const {
    std::ofstream outFile("livros.txt");
    if (outFile.is_open()) {
        for (const auto& livro : livros) {
            outFile << "\"" << livro.getNome() << "\" " << livro.getQuantidade() << std::endl;
        }
        outFile.close();
    }
}

void Biblioteca::adicionarLivro(const Livro& l) {
    livros.insert(l);
    salvarLivros();
}

void Biblioteca::removerLivro(const Livro& l) {
    auto it = livros.find(l);
    if (it != livros.end()) {
        livros.erase(it);
        salvarLivros();
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
