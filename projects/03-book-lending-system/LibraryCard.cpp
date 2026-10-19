#include "LibraryCard.hpp"
#include <span>

namespace library {

int LibraryCard::totalCardsIssued = 0;

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
LibraryCard::LibraryCard(std::string name_str, std::string id_str, size_t initial_cap) 
    : memberName(std::move(name_str)), memberID(std::move(id_str)), borrowCount(0), capacity(initial_cap) {
    if (capacity == 0) {
        books = nullptr;
    } else {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        books = new Book*[capacity]; 
    }
    totalCardsIssued++;
}

LibraryCard::LibraryCard(const LibraryCard& other) 
    : memberName(other.memberName), memberID(other.memberID), 
      borrowCount(other.borrowCount), capacity(other.capacity) {
    if (capacity == 0) {
        books = nullptr;
    } else {
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        books = new Book*[capacity];
        std::span<Book*> dest_view(books, capacity);
        std::span<Book*> src_view(other.books, other.capacity);
        for (size_t i = 0; i < borrowCount; i++) {
            dest_view[i] = src_view[i];
        }
    }
    totalCardsIssued++;
}

LibraryCard::~LibraryCard() {
    delete[] books; 
}

// Resizes dynamic array by doubling capacity when full
bool LibraryCard::borrowBook(Book& book_obj) {
    if (borrowCount == capacity) {
        size_t new_cap = (capacity == 0) ? 1 : capacity * 2;
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        Book** new_array = new Book*[new_cap];
        
        std::span<Book*> new_view(new_array, new_cap);
        std::span<Book*> old_view(books, capacity);
        
        for (size_t i = 0; i < borrowCount; i++) {
            new_view[i] = old_view[i];
        }
        
        delete[] books; 
        books = new_array;
        capacity = new_cap;
    }
    std::span<Book*> current_view(books, capacity);
    current_view[borrowCount] = &book_obj;
    borrowCount++;
    book_obj.setAvailability(false);
    return true; 
}

// Removes book and shifts subsequent pointers
bool LibraryCard::returnBook(size_t index) {
    if (index < borrowCount) {
        std::span<Book*> view(books, capacity);
        view[index]->setAvailability(true);
        for (size_t i = index; i < borrowCount - 1; i++) {
            view[i] = view[i + 1];
        }
        borrowCount--;
        return true;
    }
    return false;
}

bool LibraryCard::returnBook(const std::string& book_title) {
    std::span<Book*> view(books, capacity);
    for (size_t i = 0; i < borrowCount; i++) {
        if (view[i]->getTitle() == book_title) {
            return returnBook(i);
        }
    }
    return false;
}

void LibraryCard::clear() {
    std::span<Book*> view(books, capacity);
    for (size_t i = 0; i < borrowCount; i++) {
        view[i]->setAvailability(true);
    }
    borrowCount = 0;
}

Book* LibraryCard::findBorrowedBook(const std::string& book_title) const {
    std::span<Book*> view(books, capacity);
    for (size_t i = 0; i < borrowCount; i++) {
        if (view[i]->getTitle() == book_title) {
            return view[i];
        }
    }
    return nullptr;
}

int LibraryCard::getTotalBorrowedPages() const {
    int total = 0;
    std::span<Book*> view(books, capacity);
    for (size_t i = 0; i < borrowCount; i++) {
        total += view[i]->getPages();
    }
    return total;
}

// Overloaded assignment
LibraryCard& LibraryCard::operator=(const LibraryCard& other) {
    if (this != &other) {
        delete[] books;
        memberName = other.memberName;
        memberID = other.memberID;
        borrowCount = other.borrowCount;
        capacity = other.capacity;
        if (capacity == 0) {
            books = nullptr;
        } else {
            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            books = new Book*[capacity];
            std::span<Book*> dest_view(books, capacity);
            std::span<Book*> src_view(other.books, other.capacity);
            for (size_t i = 0; i < borrowCount; i++) {
                dest_view[i] = src_view[i];
            }
        }
    }
    return *this;
}

void LibraryCard::print(std::ostream& output_stream) const {
    output_stream << "Card Owner: " << memberName << " (ID: " << memberID << ")\n";
    output_stream << "Books Borrowed (" << borrowCount << "/" << capacity << "):\n";
    std::span<Book*> view(books, capacity);
    for (size_t i = 0; i < borrowCount; i++) {
        output_stream << "  [" << i << "] " << *(view[i]) << "\n";
    }
}

bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2) {
    return card1.getBorrowCount() > card2.getBorrowCount();
}

Book* LibraryCard::operator[](size_t index) const {
    if (index < borrowCount) {
        std::span<Book*> view(books, capacity);
        return view[index];
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& output_stream, const LibraryCard& card) {
    card.print(output_stream);
    return output_stream;
}

}