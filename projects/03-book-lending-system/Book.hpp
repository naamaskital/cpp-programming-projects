#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>

namespace library {

// Structure representing a book's author
struct Author {
    std::string name;
    std::string country;
    int birthYear;

    // Constructor with default values for Unknown authors
    Author(std::string name_str = "Unknown", std::string country_str = "Unknown", int year = 0) 
        : name(std::move(name_str)), country(std::move(country_str)), birthYear(year) {}
};

class Book {
private:
    std::string title;
    Author author;
    std::string isbn;
    int pages;
    bool available;

    // Static members to track book counts across all instances
    static int totalCreated;   
    static int currentExisting; 

public:
    // Constructors: Default, Parameterized, and Copy
    Book();
    Book(const std::string& book_title, const Author& book_author, const std::string& book_isbn, int page_count);
    Book(const std::string& book_title, const std::string& author_name, const std::string& book_isbn, int page_count);
    Book(const Book& other);
    ~Book(); // Destructor

    // Getters (Inline for performance)
    std::string getTitle() const { return title; }
    std::string getISBN() const { return isbn; }
    int getPages() const { return pages; }
    bool getAvailability() const { return available; }
    void setAvailability(bool status) { available = status; }
    const Author& getAuthor() const { return author; }
    Author& getAuthorReference() { return author; } 
    
    // Setters and logic (Outline)
    std::string getAuthorName() const; 
    void setTitle(const std::string& new_title);
    void print(std::ostream& output_stream) const;
    void setAuthor(const std::string& author_name);
    void setAuthor(const Author& author_obj);
    
    // Classification logic
    bool isLargeBook() const;
    std::string getCategory() const;

    // Static accessors
    static int getTotalBooksCreated() { return totalCreated; }
    static int getCurrentBookCount() { return currentExisting; }

    // Friend functions for external access to private data
    friend bool compareByPages(const Book& book1, const Book& book2);
    friend bool haveSameAuthor(const Book& book1, const Book& book2);
    friend std::ostream& operator<<(std::ostream& output_stream, const Book& book);
};

} 
#endif