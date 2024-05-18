#include <iostream>
#include <string>

class Livro{
    private:
        std::string nome;
        int quantidade;

    public:
        Livro(){}

        Livro(std::string nome, int quantidade){
            this->nome = nome;
            this->quantidade = quantidade;
        }

        std::string getNome() const {
            return this->nome;
        }

        int getQuantidade() const {
            return this->quantidade;
        }

        bool operator==(const Livro& l) const {
            return this->nome == l.nome;
        }

        bool operator<(const Livro& l) const {
            return this->nome < l.nome;
        }
};
