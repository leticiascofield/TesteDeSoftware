#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string login;
    std::string senha;
    std::string cargo;

public:
    Usuario(const std::string& login, const std::string& senha);
    Usuario(const std::string& login, const std::string& senha, const std::string& cargo);

    std::string getLogin() const;
    std::string getSenha() const;
    std::string getCargo() const;
    bool operator==(const Usuario& u) const;
    bool operator<(const Usuario& u) const;

};

#endif
