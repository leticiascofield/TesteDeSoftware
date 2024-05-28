#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Doctest.hpp"
#include "Biblioteca.hpp"
#include "Livro.hpp"
#include "Utils.hpp"

TEST_CASE("Usuario getMulta - Sem multa para empréstimo dentro do período permitido") {
    Usuario usuario("testuser", "password");
    usuario.setLivroEmprestado("Livro A");
    usuario.setDataEmprestimo(std::chrono::system_clock::now() - std::chrono::hours(10 * 24)); 

    CHECK(usuario.getMulta() == 0);
}

TEST_CASE("Usuario getMulta - Sem multa no dia de devolução") {
    Usuario usuario("testuser", "password");
    usuario.setLivroEmprestado("Livro A");
    usuario.setDataEmprestimo(std::chrono::system_clock::now() - std::chrono::hours(14 * 24)); 

    CHECK(usuario.getMulta() == 0);
}

TEST_CASE("Usuario getMulta - 1 dia de atraso - 1 real de multa") {
    Usuario usuario("testuser", "password");
    usuario.setLivroEmprestado("Livro B");
    usuario.setDataEmprestimo(std::chrono::system_clock::now() - std::chrono::hours(15 * 24)); 

    CHECK(usuario.getMulta() == 1);
}

TEST_CASE("Usuario getMulta - 6 dias de atraso - 6 reais de multa") {
    Usuario usuario("testuser", "password");
    usuario.setLivroEmprestado("Livro B");
    usuario.setDataEmprestimo(std::chrono::system_clock::now() - std::chrono::hours(20 * 24)); 

    CHECK(usuario.getMulta() == 6);
}

TEST_CASE("Usuario getMulta - 16 dias de atraso - 16 reais de multa") {
    Usuario usuario("testuser", "password");
    usuario.setLivroEmprestado("Livro B");
    usuario.setDataEmprestimo(std::chrono::system_clock::now() - std::chrono::hours(30 * 24)); 

    CHECK(usuario.getMulta() == 16);
}

TEST_CASE("stringToTimePoint - Conversão válida de string de data") {
    std::string date = "2024-05-23";
    auto tp = stringToTimePoint(date);

    CHECK(tp.time_since_epoch().count() != 0); 
}

TEST_CASE("stringToTimePoint - Conversão de string de data futura") {
    std::string date = "2100-01-01"; 
    auto tp = stringToTimePoint(date);

    CHECK(tp > std::chrono::system_clock::now()); 
}

TEST_CASE("stringToTimePoint - Conversão de string de data passada") {
    std::string date = "1900-01-01"; 
    auto tp = stringToTimePoint(date);

    CHECK(tp < std::chrono::system_clock::now()); 
}

TEST_CASE("timePointToString - Conversão de ponto de tempo futuro") {

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() + std::chrono::hours(24 * 30); 

    std::string date = timePointToString(tp);

    CHECK(date != ""); 
    CHECK(date.find("1970") == std::string::npos); 
}

TEST_CASE("timePointToString - Conversão de ponto de tempo passado") {

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() - std::chrono::hours(24 * 30); 

    std::string date = timePointToString(tp);

    CHECK(date != ""); 
    CHECK(date.find("1970") == std::string::npos); 
}

TEST_CASE("Biblioteca getUsuario - Usuário existente") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password");
    biblioteca.adicionarUsuario(usuario);

    Usuario usuarioObtido = biblioteca.getUsuario("testuser");

    CHECK(usuarioObtido == usuario);
}

TEST_CASE("Biblioteca getUsuario - Usuário inexistente") {
    Biblioteca biblioteca;

    Usuario usuarioObtido = biblioteca.getUsuario("nonexistentuser");

    CHECK(usuarioObtido.getLogin() == ""); 
}

TEST_CASE("Biblioteca getUsuario - Biblioteca vazia") {
    Biblioteca biblioteca;

    Usuario usuarioObtido = biblioteca.getUsuario("anyuser");

    CHECK(usuarioObtido.getLogin() == ""); 
}

TEST_CASE("Biblioteca adicionarLivro - Adicionar um novo livro") {
    Biblioteca biblioteca;
    Livro livro("Book A", 10, 10);

    biblioteca.adicionarLivro(livro);

    CHECK(biblioteca.procurarLivro(livro) == true);
}

TEST_CASE("Biblioteca adicionarLivro - Adicionar quantidade positiva de livros") {
    Biblioteca biblioteca;
    Livro livro("Book B", 5, 5);
    biblioteca.adicionarLivro(livro); 

    Livro livroAtualizado("Book B", 10, 10); 
    biblioteca.adicionarLivro(livroAtualizado);

    CHECK(biblioteca.procurarLivro(livroAtualizado) == true);
}

TEST_CASE("Biblioteca adicionarLivro - Adicionar quantidade negativa de livros") {
    Biblioteca biblioteca;
    Livro livro("Book C", 5, 5);

    biblioteca.adicionarLivro(livro);
    biblioteca.adicionarLivro(Livro("Book C", -3, -3)); 

    CHECK(biblioteca.procurarLivro(livro) == true); 
}

TEST_CASE("Biblioteca adicionarLivro - Livro existente com quantidade zero") {
    Biblioteca biblioteca;
    Livro livro("Book D", 0, 0);

    biblioteca.adicionarLivro(livro);
    biblioteca.adicionarLivro(Livro("Book D", 5, 5)); 

    CHECK(biblioteca.procurarLivro(Livro("Book D", 5, 5)) == true); 
}

TEST_CASE("Biblioteca adicionarLivro - Livro inexistente com quantidade zero") {
    Biblioteca biblioteca;

    biblioteca.adicionarLivro(Livro("Book E", 0, 0)); 

    CHECK(biblioteca.procurarLivro(Livro("Book E", 0, 0)) == false); 
}

TEST_CASE("Biblioteca removerLivro - Remover livro existente com quantidade suficiente") {
    Biblioteca biblioteca;
    Livro livro("Book A", 10, 5); 
    biblioteca.adicionarLivro(livro);

    biblioteca.removerLivro(Livro("Book A", 2, 2)); 

    CHECK(biblioteca.procurarLivro(Livro("Book A", 8, 3)) == true); 
}

TEST_CASE("Biblioteca removerLivro - Remover livro existente com quantidade insuficiente") {
    Biblioteca biblioteca;
    Livro livro("Book B", 3, 3); 
    biblioteca.adicionarLivro(livro);

    biblioteca.removerLivro(Livro("Book B", 5, 5)); 

    WARN("Erro: Quantidade de livros a remover maior do que a existente no estoque.");
    CHECK(biblioteca.procurarLivro(livro) == true); 
}

TEST_CASE("Biblioteca removerLivro - Remover livro existente com quantidade zero") {
    Biblioteca biblioteca;
    Livro livro("Book C", 0, 0); 
    biblioteca.adicionarLivro(livro);

    biblioteca.removerLivro(Livro("Book C", 0, 0)); 

    CHECK(biblioteca.procurarLivro(livro) == false); 
}

TEST_CASE("Biblioteca removerLivro - Remover livro inexistente") {
    Biblioteca biblioteca;
    Livro livro("Book D", 10, 10); 

    biblioteca.removerLivro(livro); 

    WARN("Erro: Livro não encontrado no estoque.");
}

TEST_CASE("Biblioteca removerLivro - Remover livro com quantidade negativa") {
    Biblioteca biblioteca;

    biblioteca.removerLivro(Livro("Book E", -5, -5)); 

    WARN("Erro: Quantidade de livros a remover não pode ser negativa.");
}

TEST_CASE("Biblioteca pegarLivroEmprestado - Livro disponível para empréstimo") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente");
    Livro livro("Book A", 5, 5); 
    biblioteca.adicionarLivro(livro);

    biblioteca.pegarLivroEmprestado(usuario, livro);

    CHECK(usuario.getLivroEmprestado() == "Book A");
    CHECK(usuario.getDataEmprestimo() != stringToTimePoint("2000-01-01"));
    CHECK(usuario.getMulta() == 0);
}

TEST_CASE("Biblioteca pegarLivroEmprestado - Livro indisponível para empréstimo") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente");
    Livro livro("Book B", 0, 0); 
    biblioteca.adicionarLivro(livro);

    biblioteca.pegarLivroEmprestado(usuario, livro);

    WARN("Erro: Livro não disponível para empréstimo.");
    CHECK(usuario.getLivroEmprestado() == ""); 
}

TEST_CASE("Biblioteca pegarLivroEmprestado - Livro já emprestado") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente", "Book C", std::chrono::system_clock::now(), 0); 
    Livro livro("Book C", 5, 5); 
    biblioteca.adicionarLivro(livro);

    biblioteca.pegarLivroEmprestado(usuario, livro);

    WARN("Erro: Usuário já tem livro emprestado.");
}

TEST_CASE("Biblioteca pegarLivroEmprestado - Usuário sem livro emprestado") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente");
    Livro livro("Book D", 5, 5); 
    biblioteca.adicionarLivro(livro);

    biblioteca.pegarLivroEmprestado(usuario, livro);

    CHECK(usuario.getLivroEmprestado() == "Book D");
    CHECK(usuario.getDataEmprestimo() != stringToTimePoint("2000-01-01"));
    CHECK(usuario.getMulta() == 0);
}

TEST_CASE("Biblioteca pegarLivroEmprestado - Atualização correta da quantidade disponível") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente");
    Livro livro("Book E", 3, 3); 
    biblioteca.adicionarLivro(livro);

    biblioteca.pegarLivroEmprestado(usuario, livro);

    CHECK(biblioteca.procurarLivro(Livro("Book E", 3, 2)) == true);
}

TEST_CASE("Biblioteca devolverLivroEmprestado - Usuário não tem livro emprestado") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente"); 

    biblioteca.devolverLivroEmprestado(usuario);

    WARN("Erro: Usuário não encontrado na lista de usuários.");
}

TEST_CASE("Biblioteca devolverLivroEmprestado - Livro devolvido corretamente") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente", "Book B", std::chrono::system_clock::now(), 0); 
    Livro livro("Book B", 5, 4); 
    biblioteca.adicionarLivro(livro);

    biblioteca.devolverLivroEmprestado(usuario);

    CHECK(biblioteca.procurarLivro(Livro("Book B", 5, 5)) == true);
}

TEST_CASE("Biblioteca devolverLivroEmprestado - Atualização correta da quantidade disponível") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente", "Book C", std::chrono::system_clock::now(), 0); 
    Livro livro("Book C", 5, 4); 
    biblioteca.adicionarLivro(livro);

    biblioteca.devolverLivroEmprestado(usuario);

    CHECK(biblioteca.procurarLivro(Livro("Book C", 5, 5)) == true);
}

TEST_CASE("Biblioteca devolverLivroEmprestado - Usuário com multa") {
    Biblioteca biblioteca;
    Usuario usuario("testuser", "password", "cliente", "Book D", std::chrono::system_clock::now() - std::chrono::hours(24 * 16), 0); 
    Livro livro("Book D", 5, 4); 
    biblioteca.adicionarLivro(livro);

    biblioteca.devolverLivroEmprestado(usuario);

    CHECK(usuario.getMulta() == 2); 
}

TEST_CASE("Biblioteca adicionarUsuario - Novo usuário adicionado com sucesso") {
    Biblioteca biblioteca;
    Usuario novoUsuario("novousuario", "senha123", "cliente");

    biblioteca.adicionarUsuario(novoUsuario);

    CHECK(biblioteca.getUsuario("novousuario") == novoUsuario);
}

TEST_CASE("Biblioteca adicionarUsuario - Usuário com login existente") {
    Biblioteca biblioteca;
    Usuario usuarioExistente("usuarioexistente", "senha456", "cliente");
    biblioteca.adicionarUsuario(usuarioExistente); 

    biblioteca.adicionarUsuario(usuarioExistente);

    WARN("Erro: Login desejado já existente, escolha outro.");
}

TEST_CASE("Biblioteca adicionarUsuario - Adicionar múltiplos usuários") {
    Biblioteca biblioteca;
    Usuario usuario1("user1", "pass1", "cliente");
    Usuario usuario2("user2", "pass2", "funcionario");

    biblioteca.adicionarUsuario(usuario1);
    biblioteca.adicionarUsuario(usuario2);

    CHECK(biblioteca.getUsuario("user1") == usuario1);
    CHECK(biblioteca.getUsuario("user2") == usuario2);
}

TEST_CASE("Biblioteca adicionarUsuario - Adicionar usuário com senha em branco") {
    Biblioteca biblioteca;
    Usuario usuarioSemSenha("usuariosemsenha", "", "cliente");

    biblioteca.adicionarUsuario(usuarioSemSenha);

    WARN("Erro: Senha não pode estar em branco.");
}

TEST_CASE("Biblioteca adicionarUsuario - Adicionar usuário com login em branco") {
    Biblioteca biblioteca;
    Usuario usuarioSemLogin("", "senha789", "cliente");

    biblioteca.adicionarUsuario(usuarioSemLogin);

    WARN("Erro: Login não pode estar em branco.");
}

TEST_CASE("Biblioteca autenticarUsuario - Usuário autenticado com sucesso") {
    Biblioteca biblioteca;
    Usuario usuario("usuario", "senha", "cliente");
    biblioteca.adicionarUsuario(usuario); 

    CHECK(biblioteca.autenticarUsuario(usuario) == true);
}

TEST_CASE("Biblioteca autenticarUsuario - Login inexistente") {
    Biblioteca biblioteca;
    Usuario usuario("usuarioinexistente", "senha", "cliente");

    CHECK(biblioteca.autenticarUsuario(usuario) == false);
}

TEST_CASE("Biblioteca autenticarUsuario - Senha incorreta") {
    Biblioteca biblioteca;
    Usuario usuario("usuario", "senha", "cliente");
    biblioteca.adicionarUsuario(usuario); 

    Usuario usuarioSenhaIncorreta("usuario", "senhaincorreta", "cliente");
    CHECK(biblioteca.autenticarUsuario(usuarioSenhaIncorreta) == false);
}

TEST_CASE("Biblioteca autenticarUsuario - Login vazio") {
    Biblioteca biblioteca;
    Usuario usuario("", "senha", "cliente");

    CHECK(biblioteca.autenticarUsuario(usuario) == false);
}

TEST_CASE("Biblioteca autenticarUsuario - Senha vazia") {
    Biblioteca biblioteca;
    Usuario usuario("usuario", "", "cliente");

    CHECK(biblioteca.autenticarUsuario(usuario) == false);
}

TEST_CASE("Biblioteca imprimirLivrosFuncionario - Impressão bem-sucedida") {
    Biblioteca biblioteca;
    Livro livro1("Livro 1", 5, 5);
    Livro livro2("Livro 2", 10, 10);
    biblioteca.adicionarLivro(livro1);
    biblioteca.adicionarLivro(livro2);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosFuncionario();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "Livro 1 - Quantidade: 5\nLivro 2 - Quantidade: 10\n");
}

TEST_CASE("Biblioteca imprimirLivrosFuncionario - Sem livros disponíveis") {
    Biblioteca biblioteca;

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosFuncionario();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosFuncionario - Livros com quantidades negativas") {
    Biblioteca biblioteca;
    Livro livro("Livro com quantidade negativa", -5, -5);
    biblioteca.adicionarLivro(livro);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosFuncionario();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosFuncionario - Livros com quantidades zero") {
    Biblioteca biblioteca;
    Livro livro("Livro com quantidade zero", 0, 0);
    biblioteca.adicionarLivro(livro);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosFuncionario();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosFuncionario - Múltiplos livros") {
    Biblioteca biblioteca;
    Livro livro1("Livro 1", 5, 5);
    Livro livro2("Livro 2", 10, 10);
    Livro livro3("Livro 3", 3, 3);
    biblioteca.adicionarLivro(livro1);
    biblioteca.adicionarLivro(livro2);
    biblioteca.adicionarLivro(livro3);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosFuncionario();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "Livro 1 - Quantidade: 5\nLivro 2 - Quantidade: 10\nLivro 3 - Quantidade: 3\n");
}

TEST_CASE("Biblioteca imprimirLivrosCliente - Livros disponíveis") {
    Biblioteca biblioteca;
    Livro livro1("Livro 1", 5, 5);
    Livro livro2("Livro 2", 10, 0); 
    Livro livro3("Livro 3", 3, 3);
    biblioteca.adicionarLivro(livro1);
    biblioteca.adicionarLivro(livro2);
    biblioteca.adicionarLivro(livro3);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosCliente();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "Livro 1 - Disponível\nLivro 2 - Indisponível\nLivro 3 - Disponível\n");
}

TEST_CASE("Biblioteca imprimirLivrosCliente - Sem livros disponíveis") {
    Biblioteca biblioteca;

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosCliente();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosCliente - Livros com quantidades negativas") {
    Biblioteca biblioteca;
    Livro livro("Livro com quantidade negativa", -5, -5);
    biblioteca.adicionarLivro(livro);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosCliente();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosCliente - Livros com quantidades zero") {
    Biblioteca biblioteca;
    Livro livro("Livro com quantidade zero", 0, 0);
    biblioteca.adicionarLivro(livro);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosCliente();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "");
}

TEST_CASE("Biblioteca imprimirLivrosCliente - Múltiplos livros") {
    Biblioteca biblioteca;
    Livro livro1("Livro 1", 5, 5);
    Livro livro2("Livro 2", 0, 0); 
    Livro livro3("Livro 3", 3, 3);
    biblioteca.adicionarLivro(livro1);
    biblioteca.adicionarLivro(livro2);
    biblioteca.adicionarLivro(livro3);

    std::stringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf()); 
    biblioteca.imprimirLivrosCliente();
    std::cout.rdbuf(oldCoutBuffer); 

    CHECK(output.str() == "Livro 1 - Disponível\nLivro 3 - Disponível\n");
}