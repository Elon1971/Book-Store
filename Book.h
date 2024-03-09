#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string* author;
    std::string* title;
    int* stock;
    std::string* publisher;
    double* price;
    int maxSize;

public:
    // Constructor and destructor
    Book(int maxSize);
    ~Book();

    // Function to add a book
    void addBook(string author, string title, int stock, string publisher, double price);

    // Function to check if the book is available
    bool isAvailable(int index) const;

    // Function to get the price of the book
    double getPrice(int index) const;

    // Function to sell copies of the book
    bool sellCopies(int index, int numCopies);

    // Function to display book details
    void displayDetails(int index) const;

    // Function to display all available books
    void displayAllBooks() const;

    // Function to buy a book
    void buyBook(std::string author, std::string title, int numCopies);
};

#endif

