#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string* author;
    string* title;
    int* stock;
    string* publisher;
    double* price;

public:
    int maxSize;

    Book(int maxSize = 10);
    ~Book();

    void addBook(string author, string title, int stock, string publisher, double price);
    bool isAvailable(int index) const;
    double getPrice(int index) const;
    bool sellCopies(int index, int numCopies);
    void displayDetails(int index) const;
    void displayAllBooks() const;
    void buyBook(string author, string title, int numCopies);
};

#endif
