#ifndef LIBRARYCARD_HPP
#define LIBRARYCARD_HPP

#include "Book.hpp"
#include <cstddef>
#include <span> 

namespace library {

// Manages a member's borrowed books using dynamic memory
class LibraryCard {
private:
    std::string memberName;
    std::string memberID;
    Book** books;            // Dynamic array of pointers to books
    size_t borrowCount;      // Actual books currently borrowed
    size_t capacity;         // Current size of the dynamic array
    static int totalCardsIssued; 

public:
    // Rule of Three implementation
    LibraryCard(std::string name_str = "Guest", std::string id_str = "Unknown", size_t initial_cap = 3);
    LibraryCard(const LibraryCard& other);
    ~LibraryCard();

    // Functional methods
    bool borrowBook(Book& book_obj);
    bool returnBook(size_t index);
    bool returnBook(const std::string& book_title);
    
    void clear(); 
    Book* findBorrowedBook(const std::string& book_title) const;
    bool isFull() const { return borrowCount >= capacity; }
    
    void setMemberName(const std::string& new_name) { memberName = new_name; }
    void print(std::ostream& output_stream) const;
    
    // Getters
    std::string getMemberName() const { return memberName; }
    std::string getMemberID() const { return memberID; }
    size_t getBorrowCount() const { return borrowCount; }
    size_t getCapacity() const { return capacity; }
    int getTotalBorrowedPages() const; 
    
    static int getTotalCardsIssued() { return totalCardsIssued; }

    // Operators
    LibraryCard& operator=(const LibraryCard& other);
    Book* operator[](size_t index) const;

    friend bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2);
    friend std::ostream& operator<<(std::ostream& output_stream, const LibraryCard& card);
};

bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2);

} 
#endif