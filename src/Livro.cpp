#include "Livro.hpp"

Livro::Livro(std::string nome, int quantidade) {
    this->nome = nome;
    this->quantidade = quantidade;
    this->quantidadeDisponivel = quantidade;
}

Livro::Livro(std::string nome, int quantidade, int quantidadeDisponivel) {
    this->nome = nome;
    this->quantidade = quantidade;
    this->quantidadeDisponivel = quantidadeDisponivel;
}

std::string Livro::getNome() const {
    return this->nome;
}

int Livro::getQuantidade() const {
    return this->quantidade;
}

int Livro::getQuantidadeDisponivel() const {
    return this->quantidadeDisponivel;
}

bool Livro::operator==(const Livro& l) const {
    return this->nome == l.nome;
}

bool Livro::operator<(const Livro& l) const {
    return this->nome < l.nome;
}
