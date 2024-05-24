#include "Usuario.hpp"

Usuario::Usuario(const std::string& login, const std::string& senha) {
    this->login = login;
    this->senha = senha;
    this->cargo = "cliente";
}

std::string Usuario::getLogin() const {
    return this->login;
}

std::string Usuario::getSenha() const {
    return this->senha;
}

std::string Usuario::getCargo() const {
    return this->cargo;
}

bool Usuario::operator==(const Usuario& u) const {
    return this->login == u.login;
}

bool Usuario::operator<(const Usuario& u) const {
    return this->login < u.login;
}
