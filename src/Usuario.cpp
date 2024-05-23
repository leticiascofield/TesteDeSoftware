#include "Usuario.hpp"

Usuario::Usuario(const std::string& login, const std::string& senha, const std::string& cargo)
    : login(login), senha(senha), cargo(cargo) {}

std::string Usuario::getLogin() const {
    return this->login;
}

std::string Usuario::getSenha() const {
    return this->senha;
}

std::string Usuario::getCargo() const {
    return this->cargo;
}
