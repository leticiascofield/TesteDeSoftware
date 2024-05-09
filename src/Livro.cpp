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

        std::string getNome(){
            return this-> nome;
        }

        int getQuantidade(){
            return this->quantidade;
        }

        bool operator==(Livro l) const {
            return this->nome == l.nome;
        }
};