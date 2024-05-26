#include "Usuario.hpp"
#include "Utils.hpp"

Usuario::Usuario(const std::string& login, const std::string& senha) {
    this->login = login;
    this->senha = senha;
    this->cargo = "cliente";
    this->livroEmprestado = "";
    this->dataEmprestimo = stringToTimePoint("2000-01-01");
    this->multa = 0;
}

Usuario::Usuario(const std::string& login, const std::string& senha, const std::string& cargo) {
    this->login = login;
    this->senha = senha;
    this->cargo = cargo;
    this->livroEmprestado = "";
    this->dataEmprestimo = stringToTimePoint("2000-01-01");
    this->multa = 0;
}

Usuario::Usuario(const std::string& login, const std::string& senha, const std::string& cargo,
                const std::string& livroEmprestado, const std::chrono::system_clock::time_point& dataEmprestimo,
                const int multa) {
    this->login = login;
    this->senha = senha;
    this->cargo = cargo;
    this->livroEmprestado = livroEmprestado;
    this->dataEmprestimo = dataEmprestimo;
    this->multa = multa;
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

std::string Usuario::getLivroEmprestado() const {
    return this->livroEmprestado;
}

std::chrono::system_clock::time_point Usuario::getDataEmprestimo() const {
    return this->dataEmprestimo;
}

std::string Usuario::getDataEmprestimoStr() const {
    return timePointToString(this->dataEmprestimo);
}

int Usuario::getMulta() const {
    return this->multa;
}

bool Usuario::operator==(const Usuario& u) const {
    return this->login == u.login;
}

bool Usuario::operator<(const Usuario& u) const {
    return this->login < u.login;
}
