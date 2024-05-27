#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <chrono>

class Usuario {
private:
    std::string login;
    std::string senha;
    std::string cargo;
    
    std::string livroEmprestado;
    std::chrono::system_clock::time_point dataEmprestimo;
    int multa;

public:
    Usuario();
    Usuario(const std::string& login, const std::string& senha);
    Usuario(const std::string& login, const std::string& senha, const std::string& cargo);
    Usuario(const std::string& login, const std::string& senha, const std::string& cargo,
            const std::string& livroEmprestado, const std::chrono::system_clock::time_point& dataEmprestimo,
            int multa);

    std::string getLogin() const;
    std::string getSenha() const;
    std::string getCargo() const;

    std::string getLivroEmprestado() const;
    std::chrono::system_clock::time_point getDataEmprestimo() const;
    std::string getDataEmprestimoStr() const;
    int getMulta() const;

    void setLivroEmprestado(const std::string& livroEmprestado);
    void setDataEmprestimo(const std::chrono::system_clock::time_point& dataEmprestimo);
    void setMulta(int multa);

    bool operator==(const Usuario& u) const;
    bool operator<(const Usuario& u) const;

};

#endif
