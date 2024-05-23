#include "Livro.hpp"

Livro::Livro() : nome(""), quantidade(0) {}

Livro::Livro(std::string nome, int quantidade) : nome(nome), quantidade(quantidade) {}

std::string Livro::getNome() const {
    return this->nome;
}

int Livro::getQuantidade() const {
    return this->quantidade;
}

bool Livro::operator==(const Livro& l) const {
    return this->nome == l.nome;
}

bool Livro::operator<(const Livro& l) const {
    return this->nome < l.nome;
}
