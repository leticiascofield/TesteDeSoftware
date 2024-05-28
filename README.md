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

Para executar os testes, utilize o comando:

```bash
make test
```

Para executar o programa, utilize o comando:

```bash
make run
```
