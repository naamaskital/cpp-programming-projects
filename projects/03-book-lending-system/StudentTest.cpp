#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Book.hpp"
#include "LibraryCard.hpp"

using namespace library;

// --- Book Tests (1-10) ---

TEST_CASE("1: Book Default Constructor Title") {
    Book b;
    CHECK(b.getTitle() == "Unknown");
}

TEST_CASE("2: Book Default Constructor Author") {
    Book b;
    CHECK(b.getAuthorName() == "Unknown");
}

TEST_CASE("3: Book Parameterized Constructor") {
    Book b("C++ Guide", "Stroustrup", "123", 500);
    CHECK(b.getTitle() == "C++ Guide");
    CHECK(b.getPages() == 500);
}

TEST_CASE("4: Book Category - Short") {
    Book b("Shorty", "Author", "1", 150);
    CHECK(b.getCategory() == "Short");
}

TEST_CASE("5: Book Category - Medium Boundary Lower") {
    Book b("Med", "Author", "1", 200);
    CHECK(b.getCategory() == "Medium");
}

TEST_CASE("6: Book Category - Medium Boundary Upper") {
    Book b("Med", "Author", "1", 500);
    CHECK(b.getCategory() == "Medium");
}

TEST_CASE("7: Book Category - Long") {
    Book b("Epic", "Author", "1", 501);
    CHECK(b.getCategory() == "Long");
}

TEST_CASE("8: Book isLargeBook Logic") {
    Book b1("Almost", "A", "I", 500);
    Book b2("Large", "A", "I", 501);
    CHECK_FALSE(b1.isLargeBook());
    CHECK(b2.isLargeBook());
}

TEST_CASE("9: Book Availability Toggle") {
    Book b;
    b.setAvailability(false);
    CHECK(b.getAvailability() == false);
}

TEST_CASE("10: Static Counters - Books") {
    int current = Book::getCurrentBookCount();
    {
        Book temp;
        CHECK(Book::getCurrentBookCount() == current + 1);
    }
    CHECK(Book::getCurrentBookCount() == current);
}

// --- LibraryCard Tests (11-25) ---

TEST_CASE("11: LibraryCard Default Name") {
    LibraryCard card;
    CHECK(card.getMemberName() == "Guest");
}

TEST_CASE("12: LibraryCard Default Capacity") {
    LibraryCard card;
    CHECK(card.getCapacity() == 3);
}

TEST_CASE("13: LibraryCard Custom Initialization") {
    LibraryCard card("Naama", "318", 5);
    CHECK(card.getMemberName() == "Naama");
    CHECK(card.getCapacity() == 5);
}

TEST_CASE("14: LibraryCard Borrow Count") {
    LibraryCard card;
    Book b;
    card.borrowBook(b);
    CHECK(card.getBorrowCount() == 1);
}

TEST_CASE("15: LibraryCard Availability on Borrow") {
    LibraryCard card;
    Book b;
    card.borrowBook(b);
    CHECK(b.getAvailability() == false);
}

TEST_CASE("16: LibraryCard Return by Index") {
    LibraryCard card;
    Book b;
    card.borrowBook(b);
    card.returnBook((size_t)0);
    CHECK(card.getBorrowCount() == 0);
    CHECK(b.getAvailability() == true);
}

TEST_CASE("17: LibraryCard Return by Title") {
    LibraryCard card;
    Book b("FindMe", "A", "I", 100);
    card.borrowBook(b);
    CHECK(card.returnBook("FindMe") == true);
}

TEST_CASE("18: LibraryCard Find Book") {
    LibraryCard card;
    Book b("Target", "A", "I", 100);
    card.borrowBook(b);
    CHECK(card.findBorrowedBook("Target") != nullptr);
}

TEST_CASE("19: LibraryCard Total Pages Calculation") {
    LibraryCard card;
    Book b1("B1", "A", "I", 100), b2("B2", "A", "I", 250);
    card.borrowBook(b1);
    card.borrowBook(b2);
    CHECK(card.getTotalBorrowedPages() == 350);
}

TEST_CASE("20: LibraryCard Dynamic Resize Growth") {
    LibraryCard card("Test", "ID", 1);
    Book b1, b2;
    card.borrowBook(b1);
    card.borrowBook(b2); // Should resize
    CHECK(card.getCapacity() == 2);
}

TEST_CASE("21: LibraryCard Edge Case - Capacity Zero") {
    LibraryCard card("Zero", "ID", 0);
    Book b;
    card.borrowBook(b); // Should resize from 0 to 1
    CHECK(card.getCapacity() == 1);
}

TEST_CASE("22: LibraryCard Assignment Operator") {
    LibraryCard c1("Alice", "ID", 5), c2;
    Book b;
    c1.borrowBook(b);
    c2 = c1;
    CHECK(c2.getMemberName() == "Alice");
    CHECK(c2.getBorrowCount() == 1);
}

TEST_CASE("23: LibraryCard Clear Function") {
    LibraryCard card;
    Book b;
    card.borrowBook(b);
    card.clear();
    CHECK(card.getBorrowCount() == 0);
    CHECK(b.getAvailability() == true);
}

TEST_CASE("24: Friend Function - compareByBorrowCount") {
    LibraryCard c1("A", "1", 5), c2("B", "2", 5);
    Book b;
    c1.borrowBook(b);
    CHECK(compareByBorrowCount(c1, c2) == true);
}

TEST_CASE("25: Static Counter - Cards") {
    int start = LibraryCard::getTotalCardsIssued();
    LibraryCard c;
    CHECK(LibraryCard::getTotalCardsIssued() == start + 1);
}