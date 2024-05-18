#include <iostream>
#include <string>
#include <set>
#include "Livro.cpp"

class Biblioteca{
    private:
        std::set<Livro> livros;

        void setUpBiblioteca(){
            Livro livro1("Dracula", 3);
            this->livros.insert(livro1);
            Livro livro2("Jane Eyre", 2);
            this->livros.insert(livro2);
            Livro livro3("O Conde de Monte Cristo", 3);
            this->livros.insert(livro3);
        }

    public:
        Biblioteca(){
            setUpBiblioteca();
        }

        void adicionarLivro(const Livro& l){
            this->livros.insert(l);
        }

        void removerLivro(const Livro& l){
            auto it = this->livros.find(l);
            if (it != this->livros.end()) {
                this->livros.erase(it);
            }
        }

        bool procurarLivro(const Livro& l) const {
            auto it = livros.find(l);
            return it != livros.end();
        }

        void imprimirLivros() const {
            for (const auto& livro : livros) {
                std::cout << livro.getNome() << " - Quantidade: " << livro.getQuantidade() << std::endl;
            }
        }
};
