#include <iostream>
#include <vector>
#include <string>
#include "Livro.cpp"

class Biblioteca{
    private:
        std::vector<Livro> livros;

        void setUpBiblioteca(){
            Livro livro("Dracula", 3);
            this->livros.push_back(livro);
            Livro livro("Jane Eyre", 2);
            this->livros.push_back(livro);
            Livro livro("O Conde de Monte Cristo", 3);
            this->livros.push_back(livro);
        }

    public:
        Biblioteca(std::vector<Livro> livros){
            this->livros = livros;
        }

        void adicionarLivro(Livro l){
            this->livros.push_back(l);
        }

        void removerLivro(Livro l){
            int i = 0;
            for(Livro livro : livros){
                if(livro == l){
                    this->livros.erase(livros.begin() + i, livros.begin() + i);
                }
                i++;
            }
        }

        bool procurarLivro(Livro l){
            int i = 0;
            for(Livro livro : livros){
                if(livro == l){
                    return true;
                }
                i++;
            }
            return false;
        }
};