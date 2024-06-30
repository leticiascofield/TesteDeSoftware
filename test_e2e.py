import subprocess
import pytest
import re

def run_program_with_input(input_data):
    process = subprocess.Popen(["./main"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    
    # Input the data
    for data in input_data:
        process.stdin.write(data + "\n")
        process.stdin.flush()
    
    # Read the output
    output = process.communicate()[0]
    
    # Close the input stream and wait for the process to complete
    process.stdin.close()
    process.wait()
    
    return output

def strip_ansi_escape_sequences(text):
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape.sub('', text)

def concatenate_strings(str_list):
    # Joining the list of strings into a single string
    result_string = ''.join(str_list)
    return result_string

@pytest.mark.parametrize("input_data, expected_interactions", [
    (["3"], ["- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\nSaindo...\n"]),
    (["1", "usuarioinexistente", "senha123", "", "3", ""], [
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "- Entrar -\nDigite seu login: ",
        "Digite sua senha: ",
        "\nErro: Esse login não existe.\n",
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "Saindo...\n",
        ""
    ]),
    (["1", "anacosta", "senhaerrada", "", "3", ""], [
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "- Entrar -\nDigite seu login: ",
        "Digite sua senha: ",
        "\nErro: Senha incorreta.\n",
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "Saindo...\n",
        ""
    ]),
    (["1", "anacosta", "senha123", "", "6", "", "3", ""], [
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n- Entrar -\nDigite seu login: ",
        "Digite sua senha: ",
        "\nLogin bem-sucedido! Bem-vindo, anacosta!\n",
        "- Tela Funcionalidades -\nEscolha uma opção:\n\n1. Informações sobre meu empréstimo\n2. Fazer empréstimo de um livro\n3. Devolver livro\n4. Buscar um livro\n5. Exibir todos os livros\n6. Sair\n\n",
        "Saindo...\n",
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "Saindo...\n",
        ""
    ]),
    (["1", "aninha", "1234", "", "1", "", "6", "", "3", ""], [
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "- Entrar -\nDigite seu login: ",
        "Digite sua senha: ",
        "\nLogin bem-sucedido! Bem-vindo, aninha!\n",
        "- Tela Funcionalidades -\nEscolha uma opção:\n\n1. Informações sobre meu empréstimo\n2. Fazer empréstimo de um livro\n3. Devolver livro\n4. Buscar um livro\n5. Exibir todos os livros\n6. Sair\n\n",
        "- Informações sobre meu empréstimo -\n\nNo momento, não há livro emprestado.\n",
        "- Tela Funcionalidades -\nEscolha uma opção:\n\n1. Informações sobre meu empréstimo\n2. Fazer empréstimo de um livro\n3. Devolver livro\n4. Buscar um livro\n5. Exibir todos os livros\n6. Sair\n\n",
        "Saindo...\n",
        "- Tela Inicial -\nEscolha uma opção:\n\n1. Entrar\n2. Criar Conta\n3. Sair\n\n",
        "Saindo...\n",
        ""
    ]), 
])
def test_nested_input_and_assert(input_data, expected_interactions):
    actual_interaction = run_program_with_input(input_data)
    
    actual_interaction_stripped = strip_ansi_escape_sequences(actual_interaction)
    
    assert actual_interaction_stripped == concatenate_strings(expected_interactions)

if __name__ == '__main__':
    pytest.main()
