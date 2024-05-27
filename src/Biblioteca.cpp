#include "Biblioteca.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Biblioteca::Biblioteca() {
    carregarLivros();
    carregarUsuarios();
}

Usuario Biblioteca::getUsuario(const std::string& login) const {
    for (const auto& usuario : usuarios) {
        if (usuario.getLogin() == login) {
            return usuario;
        }
    }
    return Usuario();
}

void Biblioteca::carregarLivros() {
    std::ifstream inFile("livros.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string nome;
            int quantidade, quantidadeDisponivel;
            if (iss >> std::ws && std::getline(iss, nome, '"') && std::getline(iss, nome, '"') >> quantidade >> quantidadeDisponivel) {
                Livro livro(nome, quantidade, quantidadeDisponivel);
                this->livros.insert(livro);
            }
        }
        inFile.close();
    }
}

void Biblioteca::carregarUsuarios() {
    std::ifstream inFile("usuarios.txt");
    if (inFile.is_open()) {
        std::string linha;
        while (std::getline(inFile, linha)) {
            std::istringstream iss(linha);
            std::string login, senha, cargo, livroEmprestado, dataEmprestimoStr;
            int multa;

            if (iss >> std::quoted(login) >> std::quoted(senha) >> std::quoted(cargo) 
                    >> std::quoted(livroEmprestado) >> std::quoted(dataEmprestimoStr) >> multa) {

                auto dataEmprestimo = stringToTimePoint(dataEmprestimoStr);
                Usuario usuario(login, senha, cargo, livroEmprestado, dataEmprestimo, multa);
                usuarios.insert(usuario);
            }
        }
        inFile.close();
    } else {
        std::cout << "Erro ao abrir o arquivo de usuários." << std::endl;
    }
}

void Biblioteca::salvarLivros() const {
    std::ofstream outFile("livros.txt");
    if (outFile.is_open()) {
        for (const auto& livro : this->livros) {
            outFile << "\"" << livro.getNome() << "\" " << livro.getQuantidade() << " " << livro.getQuantidadeDisponivel() << std::endl;
        }
        outFile.close();
    }
}

void Biblioteca::salvarUsuarios() const{ 
    std::ofstream outFile("usuarios.txt");
    if (outFile.is_open()) {
        for (const auto& usuario : usuarios) {
            outFile << std::quoted(usuario.getLogin()) << " "
                    << std::quoted(usuario.getSenha()) << " "
                    << std::quoted(usuario.getCargo()) << " "
                    << std::quoted(usuario.getLivroEmprestado()) << " "
                    << timePointToString(usuario.getDataEmprestimo()) << " "
                    << usuario.getMulta() << "\n";
        }
        outFile.close();
    }
}

void Biblioteca::adicionarLivro(const Livro& l) {
    if (l.getQuantidade() < 0) {
        std::cout << "Erro: Quantidade de livros a adicionar não pode ser negativa." << std::endl;
        return;
    }

    auto it = this->livros.find(l);
    if (it != this->livros.end()) {
        Livro livroAtualizado(l.getNome(), it->getQuantidade() + l.getQuantidade(), it->getQuantidade() + l.getQuantidade());
        this->livros.erase(it);
        this->livros.insert(livroAtualizado);
    } else if (l.getQuantidade() != 0) {
        this->livros.insert(l);
    }

    std::cout << std::endl << "Livro adicionado com sucesso!" << std::endl;
}

void Biblioteca::removerLivro(const Livro& l) {
    if (l.getQuantidade() < 0) {
        std::cout << "Erro: Quantidade de livros a remover não pode ser negativa." << std::endl;
        return;
    }

    for (auto it = this->livros.begin(); it != this->livros.end(); ++it) {
        if (it->getNome() == l.getNome()) {
            if (it->getQuantidade() < l.getQuantidade()) {
                std::cout << "Erro: Quantidade de livros a remover maior do que a existente no estoque." << std::endl;
                return;
            } 
            
            if (it->getQuantidade() > l.getQuantidade()) {
                Livro livroAtualizado(l.getNome(), it->getQuantidade() - l.getQuantidade(), it->getQuantidade() - l.getQuantidade());
                this->livros.erase(it);
                this->livros.insert(livroAtualizado);
            } else {
                this->livros.erase(it);
            }
            std::cout << std::endl << "Livro removido com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Erro: Livro não encontrado no estoque." << std::endl;
    return;
}

bool Biblioteca::procurarLivro(const Livro& l) const {
    auto it = this->livros.find(l);
    return it != this->livros.end();
}

void Biblioteca::imprimirLivrosFuncionario() const {
    for (const auto& livro : this->livros) {
        std::cout << livro.getNome() << " - Quantidade: " << livro.getQuantidade() << std::endl;
    }
}

void Biblioteca::imprimirLivrosCliente() const {
    for (const auto& livro : this->livros) {
        std::cout << livro.getNome();
        if(livro.getQuantidadeDisponivel() > 0) {
            std::cout << " - Disponível" << std::endl;
        } else {
            std::cout << " - Indisponível" << std::endl;
        }
    }
}

void Biblioteca::pegarLivroEmprestado(Usuario& u, Livro& l) {
    auto it = this->livros.find(l);
    if (it != this->livros.end() && it->getQuantidadeDisponivel() > 0) {
        Livro livroAtualizado = *it;
        livroAtualizado.setQuantidadeDisponivel(livroAtualizado.getQuantidadeDisponivel() - 1);

        this->livros.erase(it);
        this->livros.insert(livroAtualizado);

        u.setLivroEmprestado(livroAtualizado.getNome());
        u.setDataEmprestimo(std::chrono::system_clock::now());

        auto itUsuario = this->usuarios.find(u);
        if (itUsuario != this->usuarios.end()) {
            this->usuarios.erase(itUsuario);
        }
        this->usuarios.insert(u);

        std::string dataDevolucao = timePointToString(u.getDataEmprestimo() + std::chrono::hours(24 * 14));
        std::cout << "Empréstimo feito com sucesso, devolva o livro até o dia " << dataDevolucao  << " para que não haja multas." << std::endl;
    } else {
        std::cout << "Erro: Livro não disponível para empréstimo." << std::endl;
    }
} 

void Biblioteca::devolverLivroEmprestado(Usuario& u){
    std::string livroEmprestado = u.getLivroEmprestado();

    auto it = this->usuarios.find(u);
    if (it != this->usuarios.end()) {
        this->usuarios.erase(it);
    } else {
        std::cout << "Erro: Usuário não encontrado na lista de usuários." << std::endl;
        return;
    }

    u.setLivroEmprestado("");
    u.setDataEmprestimo(stringToTimePoint("2000-01-01")); 
    u.setMulta(0);

    this->usuarios.insert(u);

    auto itLivro = this->livros.find(Livro(livroEmprestado, 0, 0));
    if (itLivro != this->livros.end()) {
        Livro livroAtualizado = *itLivro;
        livroAtualizado.setQuantidadeDisponivel(livroAtualizado.getQuantidadeDisponivel() + 1);
        this->livros.erase(itLivro);
        this->livros.insert(livroAtualizado);
        std::cout << std::endl << "Livro '" << livroEmprestado << "' devolvido com sucesso!" << std::endl;
    } else {
        std::cout << std::endl << "Erro: Livro '" << livroEmprestado << "' não encontrado na biblioteca." << std::endl;
    }
}

void Biblioteca::adicionarUsuario(const Usuario& u){
    auto it = this->usuarios.find(u);

    if (it != this->usuarios.end()) {
        std::cout << std::endl << "Erro: Login desejado já existente, escolha outro." << std::endl;
    } else {
        this->usuarios.insert(u);
        std::cout << std::endl << "Conta criada com sucesso! Faça login para continuar." << std::endl;
    }
}

bool Biblioteca::autenticarUsuario(const Usuario& u){
    auto it = this->usuarios.find(u);

    if (it == this->usuarios.end()) {
        std::cout << std::endl << "Erro: Esse login não existe." << std::endl;
    } else {
        if (it->getSenha() == u.getSenha()) {
            std::cout << std::endl << "Login bem-sucedido! Bem-vindo, " << u.getLogin() << "!" << std::endl;
            return true;
        } else {
            std::cout << std::endl << "Erro: Senha incorreta." << std::endl;
        }
    }
    return false;
}
