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
                this->livros.insert(livro);
            }
        }
        inFile.close();
    }
}

void Biblioteca::salvarLivros() const {
    std::ofstream outFile("livros.txt");
    if (outFile.is_open()) {
        for (const auto& livro : this->livros) {
            outFile << "\"" << livro.getNome() << "\" " << livro.getQuantidade() << std::endl;
        }
        outFile.close();
    }
}

void Biblioteca::adicionarLivro(const Livro& l) {
    auto it = this->livros.find(l);
    if (it != this->livros.end()) {
        Livro livroAtualizado(l.getNome(), it->getQuantidade() + l.getQuantidade());
        this->livros.erase(it);
        this->livros.insert(livroAtualizado);
    } else {
        this->livros.insert(l);
    }
}

void Biblioteca::removerLivro(const Livro& l) {
    for (auto it = this->livros.begin(); it != this->livros.end(); ++it) {
        if (it->getNome() == l.getNome()) {
            if (it->getQuantidade() < l.getQuantidade()) {
                std::cout << "Erro: Quantidade de livros a remover maior do que a existente no estoque." << std::endl;
            } else if (it->getQuantidade() > l.getQuantidade()) {
                Livro livroAtualizado(l.getNome(), it->getQuantidade() - l.getQuantidade());
                this->livros.erase(it);
                this->livros.insert(livroAtualizado);
            } else {
                this->livros.erase(it);
            }
            return;
        }
    }
    std::cout << "Erro: Livro não encontrado no estoque." << std::endl;
}

bool Biblioteca::procurarLivro(const Livro& l) const {
    auto it = this->livros.find(l);
    return it != this->livros.end();
}

void Biblioteca::imprimirLivros() const {
    for (const auto& livro : this->livros) {
        std::cout << livro.getNome() << " - Quantidade: " << livro.getQuantidade() << std::endl;
    }
}
