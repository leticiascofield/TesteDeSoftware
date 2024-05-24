#include "Biblioteca.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Biblioteca::Biblioteca() {
    carregarLivros();
    carregarUsuarios();
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

void Biblioteca::carregarUsuarios() {
    std::ifstream inFile("usuarios.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string login, senha, cargo;
            if (iss >> login >> senha >> cargo) {
                Usuario usuario(login, senha, cargo);
                this->usuarios.insert(usuario);
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

void Biblioteca::salvarUsuarios() const{ 
    std::ofstream outFile("usuarios.txt");
    if (outFile.is_open()) {
        for (const auto& usuario : this->usuarios) {
            outFile << usuario.getLogin() << " " << usuario.getSenha() << " " << usuario.getCargo() << std::endl;
        }
        outFile.close();
    }
}

void Biblioteca::adicionarLivro(const Livro& l) {
    if (l.getQuantidade() < 0) {
        std::cout << "Erro: Quantidade de livros a adicionar não pode ser negativa." << std::endl;
        return;
    }

    auto it = this->livros.find(l);
    if (it != this->livros.end()) {
        Livro livroAtualizado(l.getNome(), it->getQuantidade() + l.getQuantidade());
        this->livros.erase(it);
        this->livros.insert(livroAtualizado);
    } else if (l.getQuantidade() != 0) {
        this->livros.insert(l);
    }

    std::cout << std::endl << "Livro adicionado com sucesso!" << std::endl;
}

void Biblioteca::removerLivro(const Livro& l) {
    if (l.getQuantidade() < 0) {
        std::cout << "Erro: Quantidade de livros a remover não pode ser negativa." << std::endl;
        return;
    }

    for (auto it = this->livros.begin(); it != this->livros.end(); ++it) {
        if (it->getNome() == l.getNome()) {
            if (it->getQuantidade() < l.getQuantidade()) {
                std::cout << "Erro: Quantidade de livros a remover maior do que a existente no estoque." << std::endl;
                return;
            } 
            
            if (it->getQuantidade() > l.getQuantidade()) {
                Livro livroAtualizado(l.getNome(), it->getQuantidade() - l.getQuantidade());
                this->livros.erase(it);
                this->livros.insert(livroAtualizado);
            } else {
                this->livros.erase(it);
            }
            std::cout << std::endl << "Livro removido com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Erro: Livro não encontrado no estoque." << std::endl;
    return;
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

void Biblioteca::adicionarUsuario(const Usuario& u){
    auto it = this->usuarios.find(u);

    if (it != this->usuarios.end()) {
        std::cout << std::endl << "Erro: Login desejado já existente, escolha outro." << std::endl;
    } else {
        this->usuarios.insert(u);
        std::cout << std::endl << "Conta criada com sucesso! Faça login para continuar." << std::endl;
    }
}

bool Biblioteca::autenticarUsuario(const Usuario& u){
    auto it = this->usuarios.find(u);
    
    if (it == this->usuarios.end()) {
        std::cout << std::endl << "Erro: Esse login não existe." << std::endl;
    } else {
        if (it->getSenha() == u.getSenha()) {
            return true;
        } else {
            std::cout << std::endl << "Erro: Senha incorreta." << std::endl;
        }
    }
    return false;
}
