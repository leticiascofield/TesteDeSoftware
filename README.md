# Biblioteca

## Descrição do Projeto
Este projeto implementa um sistema de gerenciamento de biblioteca em C++. Ele permite a administração de livros, usuários, empréstimos e devoluções, bem como a aplicação de multas para livros devolvidos após o prazo. O sistema é dividido em várias classes, como `Biblioteca`, `Usuario`, `Livro` e `Utils`.

## Estrutura do Projeto
- `src/`: Contém os arquivos fonte (.cpp) do projeto, `tests.cpp` incluso.
- `include/`: Contém os arquivos de cabeçalho (.hpp) do projeto.
- `build/`: Diretório onde os arquivos objetos (.o) serão gerados durante a compilação.
- `tests.cpp`: Arquivo contendo os casos de teste utilizando a biblioteca Doctest.

## Dependências
- C++17 ou superior
- Doctest (já incluído no projeto)

## Compilação e Execução
### Compilação
Para compilar o projeto, você pode utilizar o Makefile fornecido. Abra um terminal na raiz do projeto e execute o seguinte comando:

```bash
make
```

### Execução
Após a compilação, um executável será gerado no diretório `build`. Para executar o programa principal, utilize o comando:

```bash
./build/main
```

Para executar os testes, utilize o comando:

```bash
./build/tests
```

## Testes
Os testes foram escritos utilizando a biblioteca Doctest. Eles cobrem diversos cenários, incluindo:
- Verificação de multas para diferentes períodos de empréstimo.
- Conversão de strings de datas para `time_point` e vice-versa.
- Adição, remoção e busca de usuários e livros na biblioteca.
- Empréstimo e devolução de livros, incluindo a atualização correta das quantidades disponíveis e aplicação de multas.
- Autenticação de usuários.
- Impressão de listas de livros para funcionários e clientes.

Para executar os testes, basta compilar e rodar o executável de testes:

```bash
make tests
./build/tests
```

## Classes e Métodos
### Classe `Usuario`
Representa um usuário da biblioteca.

#### Métodos Principais:
- `Usuario()`: Construtor padrão.
- `Usuario(const std::string& login, const std::string& senha)`: Construtor com login e senha.
- `Usuario(const std::string& login, const std::string& senha, const std::string& cargo)`: Construtor com login, senha e cargo.
- `Usuario(const std::string& login, const std::string& senha, const std::string& cargo, const std::string& livroEmprestado, const std::chrono::system_clock::time_point& dataEmprestimo, const int multa)`: Construtor completo.
- `std::string getLogin() const`: Retorna o login do usuário.
- `std::string getSenha() const`: Retorna a senha do usuário.
- `std::string getCargo() const`: Retorna o cargo do usuário.
- `std::string getLivroEmprestado() const`: Retorna o livro emprestado pelo usuário.
- `std::chrono::system_clock::time_point getDataEmprestimo() const`: Retorna a data de empréstimo.
- `int getMulta() const`: Calcula e retorna a multa do usuário.
- `void setLivroEmprestado(const std::string& livroEmprestado)`: Define o livro emprestado.
- `void setDataEmprestimo(const std::chrono::system_clock::time_point& dataEmprestimo)`: Define a data de empréstimo.
- `void setMulta(int multa)`: Define a multa do usuário.

### Classe `Livro`
Representa um livro na biblioteca.

#### Métodos Principais:
- `Livro(const std::string& titulo, int quantidadeTotal, int quantidadeDisponivel)`: Construtor da classe.
- `std::string getTitulo() const`: Retorna o título do livro.
- `int getQuantidadeTotal() const`: Retorna a quantidade total do livro.
- `int getQuantidadeDisponivel() const`: Retorna a quantidade disponível do livro.

### Classe `Biblioteca`
Representa a biblioteca e gerencia usuários e livros.

#### Métodos Principais:
- `void adicionarUsuario(const Usuario& usuario)`: Adiciona um usuário à biblioteca.
- `Usuario getUsuario(const std::string& login)`: Retorna um usuário com base no login.
- `void adicionarLivro(const Livro& livro)`: Adiciona um livro à biblioteca.
- `bool procurarLivro(const Livro& livro)`: Verifica se o livro está na biblioteca.
- `void removerLivro(const Livro& livro)`: Remove um livro da biblioteca.
- `void pegarLivroEmprestado(Usuario& usuario, Livro& livro)`: Realiza o empréstimo de um livro para um usuário.
- `void devolverLivroEmprestado(Usuario& usuario)`: Realiza a devolução de um livro por um usuário.
- `bool autenticarUsuario(const Usuario& usuario)`: Autentica um usuário com base no login e senha.
- `void imprimirLivrosFuncionario() const`: Imprime a lista de livros para funcionários.
- `void imprimirLivrosCliente() const`: Imprime a lista de livros para clientes.

### Classe `Utils`
Contém funções utilitárias.

#### Métodos Principais:
- `std::chrono::system_clock::time_point stringToTimePoint(const std::string& date)`: Converte uma string de data para `time_point`.
- `std::string timePointToString(const std::chrono::system_clock::time_point& tp)`: Converte um `time_point` para string.
