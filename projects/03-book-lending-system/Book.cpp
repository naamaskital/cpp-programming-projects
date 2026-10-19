#include "Book.hpp"

namespace library {

// Constants for book classification thresholds
const int SHORT_BOOK_LIMIT = 200;
const int MEDIUM_BOOK_LIMIT = 500;

// Initialize static counters
int Book::totalCreated = 0;
int Book::currentExisting = 0;

// Default constructor
Book::Book() : title("Unknown"), author(Author("Unknown")), pages(0), available(true) {
    totalCreated++;
    currentExisting++;
}

// Full parameterized constructor
Book::Book(const std::string& book_title, const Author& book_author, const std::string& book_isbn, int page_count) 
    : title(book_title), author(book_author), isbn(book_isbn), pages(page_count), available(true) {
    totalCreated++;
    currentExisting++;
}

// Constructor with string author name (converts to Author object)
// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Book::Book(const std::string& book_title, const std::string& author_name, const std::string& book_isbn, int page_count) 
    : title(book_title), author(Author(author_name, "Unknown", 0)), isbn(book_isbn), pages(page_count), available(true) {
    totalCreated++;
    currentExisting++;
}

// Copy constructor for deep copy of book data
Book::Book(const Book& other) 
    : title(other.title), author(other.author), isbn(other.isbn), pages(other.pages), available(other.available) {
    totalCreated++;
    currentExisting++;
}

// Destructor decreases existing count
Book::~Book() {
    currentExisting--; 
}

std::string Book::getAuthorName() const {
    return author.name;
}

void Book::setTitle(const std::string& new_title) {
    title = new_title;
}

bool Book::isLargeBook() const {
    return pages > MEDIUM_BOOK_LIMIT;
}

// Returns classification string based on page count
std::string Book::getCategory() const {
    if (pages < SHORT_BOOK_LIMIT) {
        return "Short";
    }
    if (pages <= MEDIUM_BOOK_LIMIT) {
        return "Medium";
    }
    return "Long";
}

void Book::print(std::ostream& output_stream) const {
    output_stream << *this;
}

void Book::setAuthor(const std::string& author_name) {
    author.name = author_name;
}

void Book::setAuthor(const Author& author_obj) {
    author = author_obj;
}

// Global friend functions for comparisons
bool compareByPages(const Book& book1, const Book& book2) {
    return book1.pages > book2.pages;
}

bool haveSameAuthor(const Book& book1, const Book& book2) {
    return book1.author.name == book2.author.name;
}

// Overloaded << operator for easy printing
std::ostream& operator<<(std::ostream& output_stream, const Book& book) {
    output_stream << book.title << " by " << book.author.name << " | ISBN: " 
                  << (book.isbn.empty() ? "N/A" : book.isbn) 
                  << " | " << book.pages << " pages | " 
                  << (book.available ? "Available" : "Borrowed");
    return output_stream;
}

}