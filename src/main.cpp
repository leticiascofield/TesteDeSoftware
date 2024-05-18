#include <iostream>
#include <string>
#include "Biblioteca.cpp"

int main (){
    Biblioteca biblioteca;

    std::string opcao;

    while (true) {
        std::cout << "O que deseja?" << std::endl;
        std::cout << "Para adicionar um livro, digite: adicao" << std::endl;
        std::cout << "Para remover um livro, digite: remocao" << std::endl;
        std::cout << "Para procurar um livro, digite: procura" << std::endl;
        std::cout << "Para listar todos os livros, digite: lista" << std::endl;
        std::cout << "Quando quiser finalizar, digite: exit" << std::endl;

        std::cin >> opcao;

        if (opcao == "exit") {
            break;
        }

        std::string nome;
        int quantidade;

        if (opcao == "adicao") {
            std::cout << "Digite o nome do livro que deseja adicionar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            biblioteca.adicionarLivro(livro);
        } else if (opcao == "remocao") {
            std::cout << "Digite o nome do livro que deseja remover: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            Livro livro(nome, 0);
            biblioteca.removerLivro(livro);
        } else if (opcao == "procura") {
            std::cout << "Digite o nome do livro que deseja procurar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            Livro livro(nome, 0);
            bool temLivro = biblioteca.procurarLivro(livro);
            if (temLivro) {
                std::cout << std::endl << "O livro " << livro.getNome() << " está disponível na biblioteca." << std::endl;
            } else {
                std::cout << std::endl << "O livro " << livro.getNome() << " não está disponível na biblioteca." << std::endl;
            }
        } else if (opcao == "lista") {
            std::cout << std::endl;
            biblioteca.imprimirLivros();
        } else {
            std::cout << std::endl << "Opção inválida, por favor tente novamente." << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
