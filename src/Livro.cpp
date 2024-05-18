#include "Livro.hpp"

Livro::Livro() : nome(""), quantidade(0) {}

Livro::Livro(std::string nome, int quantidade) : nome(nome), quantidade(quantidade) {}

std::string Livro::getNome() const {
    return nome;
}

int Livro::getQuantidade() const {
    return quantidade;
}

bool Livro::operator==(const Livro& l) const {
    return nome == l.nome;
}

bool Livro::operator<(const Livro& l) const {
    return nome < l.nome;
}
