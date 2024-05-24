#include "Tela.hpp"

void Tela::limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Tela::pausarTela() {
    std::cin.ignore();
    std::cin.get();
}

void Tela::telaInicial(Biblioteca& biblioteca) {
    std::string opcao;
    
    while(true){
        limparTela();

        std::cout << "- Tela Inicial -" << std::endl;
        std::cout << "Escolha uma opção:" << std::endl << std::endl;
        std::cout << "1. Entrar" << std::endl;
        std::cout << "2. Criar Conta" << std::endl;
        std::cout << "3. Sair" << std::endl << std::endl;

        std::cin >> opcao;

        if (opcao == "1") {
            limparTela();
            std::cout << "- Entrar -" << std::endl;
            std::string login, senha;
            std::cout << "Digite seu login: ";
            std::cin >> login;
            std::cout << "Digite sua senha: ";
            std::cin >> senha;

            Usuario usuario(login, senha);

            // Verificar se o usuário existe e se a senha está correta

            std::cout << std::endl;
            std::cout << "Login bem-sucedido! Bem-vindo, " << usuario.getLogin() << "!" << std::endl;
            pausarTela();
            telaFuncionalidades(biblioteca);
            break;

        } else if (opcao == "2") {
            limparTela();
            std::cout << "- Criar Conta -" << std::endl;
            std::string login, senha, cargo;
            std::cout << "Digite seu login desejado: ";
            std::cin >> login;
            std::cout << "Digite sua senha desejada: ";
            std::cin >> senha;
            std::cout << "Digite seu cargo (cliente ou funcionario): ";
            std::cin >> cargo;

            Usuario novoUsuario(login, senha);
            biblioteca.adicionarUsuario(novoUsuario);

        } else if (opcao == "3") {
            limparTela();
            std::cout << "Saindo..." << std::endl;
            pausarTela();
            break;

        } else {
            limparTela();
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
        pausarTela();
    }
}

void Tela::telaFuncionalidades(Biblioteca& biblioteca){
    std::string opcao;

    while (true) {
        limparTela();

        std::cout << "- Tela Funcionalidades -" << std::endl;
        std::cout << "Escolha uma opção:" << std::endl << std::endl;

        std::cout << "1. Adicionar um livro" << std::endl;
        std::cout << "2. Remover um livro" << std::endl;
        std::cout << "3. Buscar um livro" << std::endl;
        std::cout << "4. Exibir todos os livros" << std::endl;
        std::cout << "5. Sair" << std::endl << std::endl;

        std::cin >> opcao;

        if (opcao == "5") {
            limparTela();
            std::cout << "Saindo..." << std::endl;
            pausarTela();
            break;
        }

        limparTela();
        std::string nome;
        int quantidade;

        if (opcao == "1") {
            std::cout << "- Adicionar um livro -" << std::endl;
            std::cout << "Digite o nome do livro que deseja adicionar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            biblioteca.adicionarLivro(livro);
            biblioteca.salvarLivros();

        } else if (opcao == "2") {
            std::cout << "- Remover um livro -" << std::endl;
            std::cout << "Digite o nome do livro que deseja remover: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            std::cout << "Quantidade: ";
            std::cin >> quantidade;

            Livro livro(nome, quantidade);
            biblioteca.removerLivro(livro);
            biblioteca.salvarLivros();

        } else if (opcao == "3") {
            std::cout << "- Buscar um livro -" << std::endl;
            std::cout << "Digite o nome do livro que deseja buscar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            Livro livro(nome, 0);
            bool temLivro = biblioteca.procurarLivro(livro);

            if (temLivro) {
                std::cout << std::endl << "O livro " << livro.getNome() << " está disponível na biblioteca.";
            } else {
                std::cout << std::endl << "O livro " << livro.getNome() << " não está disponível na biblioteca.";
            }


        } else if (opcao == "4") {
            std::cout << "- Exibir todos os livros -" << std::endl;
            std::cout << std::endl;
            biblioteca.imprimirLivros();

        } else {
            std::cout << std::endl << "Opção inválida, por favor tente novamente." << std::endl;
        }

        pausarTela();
    }
}
