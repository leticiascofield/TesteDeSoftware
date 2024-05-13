#include "Livro.hpp"

Livro::Livro(){}

Livro::Livro(std::string nome, int quantidade){
    this->nome = nome;
    this->quantidade = quantidade;
}

std::string Livro::getNome(){
    return this-> nome;
}

int Livro::getQuantidade(){
    return this->quantidade;
}
