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

            if (biblioteca.autenticarUsuario(usuario)) {
                Usuario usuarioAutenticado = biblioteca.getUsuario(login); // Obter o usuário completo do banco de dados

                pausarTela();
                if (usuarioAutenticado.getCargo() == "cliente") {
                    telaFuncionalidadesCliente(biblioteca, usuarioAutenticado);
                } else {
                    telaFuncionalidadesFuncionario(biblioteca);
                }
            } else {
                pausarTela();
            }

        } else if (opcao == "2") {
            limparTela();
            std::cout << "- Criar Conta -" << std::endl;
            std::string login, senha;
            std::cout << "Digite seu login desejado: ";
            std::cin >> login;
            std::cout << "Digite sua senha desejada: ";
            std::cin >> senha;

            Usuario novoUsuario(login, senha);
            biblioteca.adicionarUsuario(novoUsuario);
            biblioteca.salvarUsuarios();
            pausarTela();

        } else if (opcao == "3") {
            limparTela();
            std::cout << "Saindo..." << std::endl;
            pausarTela();
            break;

        } else {
            limparTela();
            std::cout << "Opção inválida. Tente novamente." << std::endl;
            pausarTela();
        }
    }
}

void Tela::telaFuncionalidadesFuncionario(Biblioteca& biblioteca){
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
            pausarTela();

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
            pausarTela();

        } else if (opcao == "3") {
            std::cout << "- Buscar um livro -" << std::endl;
            std::cout << "Digite o nome do livro que deseja buscar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            Livro livro(nome, 0, 0);
            bool temLivro = biblioteca.procurarLivro(livro);

            if (temLivro) {
                std::cout << std::endl << "O livro " << livro.getNome() << " está disponível na biblioteca." << std::endl;
            } else {
                std::cout << std::endl << "O livro " << livro.getNome() << " não está disponível na biblioteca." << std::endl;
            }
            std::cin.get();

        } else if (opcao == "4") {
            std::cout << "- Exibir todos os livros -" << std::endl;
            std::cout << std::endl;
            biblioteca.imprimirLivrosFuncionario();
            pausarTela();

        } else {
            std::cout << std::endl << "Opção inválida, por favor tente novamente." << std::endl;
            pausarTela();
        }

    }
}


void Tela::telaFuncionalidadesCliente(Biblioteca& biblioteca, Usuario& u){
    std::string opcao;

    while (true) {
        limparTela();

        std::cout << "- Tela Funcionalidades -" << std::endl;
        std::cout << "Escolha uma opção:" << std::endl << std::endl;

        std::cout << "1. Informações sobre meu empréstimo" << std::endl;
        std::cout << "2. Fazer empréstimo de um livro" << std::endl;
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

        if (opcao == "1") {
            std::cout << "- Informações sobre meu empréstimo -" << std::endl;
            std::cout << std::endl;

            if (u.getLivroEmprestado() != "") {
                std::cout << "Livro Emprestado: " << u.getLivroEmprestado() << std::endl;
                std::cout << "Data do empréstimo: " << u.getDataEmprestimoStr() << std::endl;
                std::cout << "Multa por atraso: " << u.getMulta() << std::endl;
            } else {
                std::cout << "No momento, não há livro emprestado." << std::endl;
            }
            pausarTela();

        } else if (opcao == "2") {
            std::cout << "- Fazer empréstimo de um livro -" << std::endl;

            if (u.getLivroEmprestado() == "") {
                std::cout << "Qual livro gostaria de fazer um empréstimo? ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                Livro livro(nome, 1);

                biblioteca.pegarLivroEmprestado(u, livro);
                biblioteca.salvarLivros();
                biblioteca.salvarUsuarios();

            } else {
                std::cout << std::endl << "Não é permitido pegar mais de um livro emprestado. Devolva " 
                            << u.getLivroEmprestado() << " para poder pegar outro." << std::endl;
                pausarTela();
            }

        } else if (opcao == "3") {
            std::cout << "- Buscar um livro -" << std::endl;
            std::cout << "Digite o nome do livro que deseja buscar: ";
            std::cin.ignore();
            std::getline(std::cin, nome);
            Livro livro(nome, 0, 0);
            bool temLivro = biblioteca.procurarLivro(livro);

            if (temLivro) {
                std::cout << std::endl << "O livro " << livro.getNome() << " está disponível na biblioteca." << std::endl;
            } else {
                std::cout << std::endl << "O livro " << livro.getNome() << " não está disponível na biblioteca." << std::endl;
            }
            std::cin.get();

        } else if (opcao == "4") {
            std::cout << "- Exibir todos os livros -" << std::endl;
            std::cout << std::endl;
            biblioteca.imprimirLivrosCliente();
            pausarTela();

        } else {
            std::cout << std::endl << "Opção inválida, por favor tente novamente." << std::endl;
            pausarTela();
        }

    }
}