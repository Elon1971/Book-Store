#include "Book.h"
#include <iostream>

// Constructor implementation
Book::Book(int maxSize)
    : maxSize(maxSize) {
    author = new std::string[maxSize];
    title = new std::string[maxSize];
    stock = new int[maxSize];
    publisher = new std::string[maxSize];
    price = new double[maxSize];
}

// Destructor implementation
Book::~Book() {
    delete[] author;
    delete[] title;
    delete[] stock;
    delete[] publisher;
    delete[] price;
}

// Function implementations...

void Book::addBook(std::string author, std::string title, int stock, std::string publisher, double price) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i].empty()) { // Check if slot is empty
            this->author[i] = author;
            this->title[i] = title;
            this->stock[i] = stock;
            this->publisher[i] = publisher;
            this->price[i] = price;
            std::cout << "Book added successfully." << std::endl;
            return;
        }
    }
    std::cout << "Library is full. Cannot add more books." << std::endl;
}

bool Book::isAvailable(int index) const {
    return stock[index] > 0;
}

double Book::getPrice(int index) const {
    return price[index];
}

bool Book::sellCopies(int index, int numCopies) {
    if (stock[index] >= numCopies) {
        stock[index] -= numCopies;
        return true;
    } else {
        std::cout << "Not enough copies available." << std::endl;
        return false;
    }
}

void Book::displayDetails(int index) const {
    std::cout << "Title: " << title[index] << std::endl;
    std::cout << "Author: " << author[index] << std::endl;
    std::cout << "Publisher: " << publisher[index] << std::endl;
    std::cout << "Price: " << price[index] << std::endl;
    std::cout << "Stock: " << stock[index] << std::endl;
}

void Book::displayAllBooks() const {
    std::cout << "Available Books:" << std::endl;
    for (int i = 0; i < maxSize; ++i) {
        if (!author[i].empty()) {
            std::cout << "Book " << i+1 << ":" << std::endl;
            displayDetails(i);
            std::cout << std::endl;
        }
    }
}


void Book::buyBook(std::string author, std::string title, int numCopies) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            if (sellCopies(i, numCopies)) {
                double totalAmount = numCopies * getPrice(i);
                std::cout << "Total amount: " << totalAmount << std::endl;
                return;
            } else {
                std::cout << "Failed to buy the book." << std::endl;
                return;
            }
        }
    }
    std::cout << "Book not found." << std::endl;
}

