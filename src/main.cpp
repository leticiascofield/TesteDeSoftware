#include <iostream>
#include <string>
#include <vector>
#include "Biblioteca.cpp"



int main (){
    std::vector<Livro> livros;


    Biblioteca biblioteca(livros);

    std::cout << "O que deseja?" << std::endl;
    std::cout << "Para adicionar um livro, digite: adicao" << std::endl;
    std::cout << "Para remover um livro, digite: remocao" << std::endl;
    std::cout << "Para procurar um livro, digite: procura" << std::endl;
    std::cout << "Quando quiser finalizar, digite: exit" << std::endl;

    std::string opcao;
    std::cin >> opcao;


    std::string nome;
    int quantidade;

    while(opcao != "exit"){
        std::cin >> opcao;
        if(opcao == "adicao"){
            std::cout << "Digite o livro que deseja adicionar." << std::endl;
            std::cout << "Nome: ";
            std::cin >> nome;
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            biblioteca.adicionarLivro(livro);
        }
        else if(opcao == "remocao"){
            std::cout << "Digite o livro que deseja remover." << std::endl;
            std::cout << "Nome: ";
            std::cin >> nome;
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            biblioteca.removerLivro(livro);
        }
        else if(opcao == "procura"){
            std::cout << "Digite o livro que deseja remover." << std::endl;
            std::cout << "Nome: ";
            std::cin >> nome;
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            bool temLivro = biblioteca.procurarLivro(livro);
            if(temLivro){
                std::cout << "Há " << livro.getQuantidade() << " exemplares do livro " << livro.getNome() << " nesta biblioteca" << std::endl;
            } else {
                std::cout << "Não há exemplares do livro " << livro.getNome() << " nesta biblioteca" << std::endl;
            }
        }
    }

    return 0;
}