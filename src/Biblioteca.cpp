#include "Biblioteca.hpp"


void Biblioteca::setUpBiblioteca(){
    Livro livro1("Dracula", 3);
    this->livros.push_back(livro1);
    Livro livro2("Jane Eyre", 2);
    this->livros.push_back(livro2);
    Livro livro3("O Conde de Monte Cristo", 3);
    this->livros.push_back(livro3);
}

Biblioteca::Biblioteca(std::vector<Livro> livros){
    this->livros = livros;
}

void Biblioteca::adicionarLivro(Livro l){
    this->livros.push_back(l);
}

void Biblioteca::removerLivro(Livro l){
    int i = 0;
    for(Livro livro : livros){
        if(livro == l){
            this->livros.erase(livros.begin() + i, livros.begin() + i);
        }
        i++;
    }
}

bool Biblioteca::procurarLivro(Livro l){
    int i = 0;
    for(Livro livro : livros){
        if(livro == l){
            return true;
        }
        i++;
    }
    return false;
}
