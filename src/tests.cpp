#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Doctest.hpp"
#include "Biblioteca.hpp"
#include "Livro.hpp"

// Test adding an item
TEST_CASE("Add Item") {
    Biblioteca biblioteca;
    Livro livro("Book A", 5);

    biblioteca.adicionarLivro(livro);

    CHECK(biblioteca.procurarLivro(livro));
}

// Test removing an item
TEST_CASE("Remove Item") {
    Biblioteca biblioteca;
    Livro livro("Book B", 10);

    biblioteca.adicionarLivro(livro);
    biblioteca.removerLivro(livro);

    CHECK_FALSE(biblioteca.procurarLivro(livro));
}

// Test adding an item and then removing it
TEST_CASE("Add and Remove Item") {
    Biblioteca biblioteca;
    Livro livro("Book C", 7);

    biblioteca.adicionarLivro(livro);
    biblioteca.removerLivro(livro);

    CHECK_FALSE(biblioteca.procurarLivro(livro));
}

// Test removing an item and then adding it again
TEST_CASE("Remove and Add Item Again") {
    Biblioteca biblioteca;
    Livro livro("Book D", 3);

    biblioteca.adicionarLivro(livro);
    biblioteca.removerLivro(livro);
    biblioteca.adicionarLivro(livro);

    CHECK(biblioteca.procurarLivro(livro));
}

// Test removing an item that is not present
TEST_CASE("Remove Nonexistent Item") {
    Biblioteca biblioteca;
    Livro livro("Book E", 2);

    CHECK_NOTHROW(biblioteca.removerLivro(livro)); // No exception should be thrown
}

// Test adding an item that is already present
TEST_CASE("Add Existing Item") {
    Biblioteca biblioteca;
    Livro livro("Book F", 4);

    biblioteca.adicionarLivro(livro);
    biblioteca.adicionarLivro(livro); // Adding the same book again

    CHECK(biblioteca.procurarLivro(livro));
}

// Test removing more quantities than are available
TEST_CASE("Remove More Quantities Than Available") {
    Biblioteca biblioteca;
    Livro livro("Book G", 3);

    biblioteca.adicionarLivro(livro);

    // Attempt to remove more quantities than available
    biblioteca.removerLivro(Livro("Book G", 5));

    CHECK(biblioteca.procurarLivro(livro)); // The book should still be present
}

// Test searching for a book that is present
TEST_CASE("Search for Present Book") {
    Biblioteca biblioteca;
    Livro livro("Book H", 6);

    biblioteca.adicionarLivro(livro);

    CHECK(biblioteca.procurarLivro(livro));
}

// Test searching for a book that is not present
TEST_CASE("Search for Nonexistent Book") {
    Biblioteca biblioteca;
    Livro livro("Book I", 8);

    CHECK_FALSE(biblioteca.procurarLivro(livro));
}

// Test removing a book and then searching
TEST_CASE("Remove and Then Search") {
    Biblioteca biblioteca;
    Livro livro("Book J", 9);

    biblioteca.adicionarLivro(livro);
    biblioteca.removerLivro(livro);

    CHECK_FALSE(biblioteca.procurarLivro(livro));
}

// Test adding a book and then searching
TEST_CASE("Add and Then Search") {
    Biblioteca biblioteca;
    Livro livro("Book K", 1);

    biblioteca.adicionarLivro(livro);

    CHECK(biblioteca.procurarLivro(livro));
}

// Test adding a quantity of 0
TEST_CASE("Add Zero Quantity") {
    Biblioteca biblioteca;
    Livro livro("Book L", 0);

    biblioteca.adicionarLivro(livro);

    CHECK_FALSE(biblioteca.procurarLivro(livro)); // The book should not be added
}

// Test removing a quantity of 0
TEST_CASE("Remove Zero Quantity") {
    Biblioteca biblioteca;
    Livro livro("Book M", 3);

    biblioteca.adicionarLivro(livro);

    // Attempt to remove a zero quantity
    biblioteca.removerLivro(Livro("Book M", 0));

    CHECK(biblioteca.procurarLivro(livro)); // The book should still be present
}

// Test adding negative quantity
TEST_CASE("Add Negative Quantity") {
    Biblioteca biblioteca;
    Livro livro("Book N", -2);

    biblioteca.adicionarLivro(livro);

    CHECK_FALSE(biblioteca.procurarLivro(livro)); // The book should not be added
}

// Test removing negative quantity
TEST_CASE("Remove Negative Quantity") {
    Biblioteca biblioteca;
    Livro livro("Book O", 4);

    biblioteca.adicionarLivro(livro);

    // Attempt to remove a negative quantity
    biblioteca.removerLivro(Livro("Book O", -3));

    CHECK(biblioteca.procurarLivro(livro)); // The book should still be present
}
