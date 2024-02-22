#include "Book.h"

Book::Book(int maxSize) : maxSize(maxSize) {
    author = new string[maxSize];
    title = new string[maxSize];
    stock = new int[maxSize];
    publisher = new string[maxSize];
    price = new double[maxSize];

    // Initialize with default values
    for (int i = 0; i < maxSize; ++i) {
        author[i] = "Unknown";
        title[i] = "Untitled";
        stock[i] = 0;
        publisher[i] = "Unknown";
        price[i] = 0.0;
    }

    // Adding default books
    author[0] = "Yash";
    title[0] = "Black";
    stock[0] = 2;
    publisher[0] = "Bansal";
    price[0] = 1000;

    author[1] = "Karan";
    title[1] = "Fairy Tales";
    stock[1] = 5;
    publisher[1] = "Bansal";
    price[1] = 500;

    author[2] = "Ashutosh";
    title[2] = "Horror Files";
    stock[2] = 3;
    publisher[2] = "Patel";
    price[2] = 800;

    author[3] = "Om";
    title[3] = "Embedded Copies";
    stock[3] = 4;
    publisher[3] = "Gohel";
    price[3] = 800;

    author[4] = "Elizabeth";
    title[4] = "Cosmic Rays";
    stock[4] = 0;
    publisher[4] = "Richard";
    price[4] = 1200;
}

Book::~Book() {
    delete[] author;
    delete[] title;
    delete[] stock;
    delete[] publisher;
    delete[] price;
}

void Book::addBook(string author, string title, int stock, string publisher, double price) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == "Unknown") {
            this->author[i] = author;
            this->title[i] = title;
            this->stock[i] = stock;
            this->publisher[i] = publisher;
            this->price[i] = price;
            cout << "Book added successfully." << endl;
            return;
        }
    }
    cout << "Library is full. Cannot add more books." << endl;
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
        cout << "Not enough copies available." << endl;
        return false;
    }
}

void Book::displayDetails(int index) const {
    cout << "Title: " << title[index] << endl;
    cout << "Author: " << author[index] << endl;
    cout << "Publisher: " << publisher[index] << endl;
    cout << "Price: " << price[index] << endl;
    cout << "Stock: " << stock[index] << endl;
}

void Book::displayAllBooks() const {
    cout << "Available Books:" << endl;
    for (int i = 0; i < maxSize; ++i) {
        if (author[i] != "Unknown") {
            cout << "Book " << i+1 << ":" << endl;
            displayDetails(i);
            cout << endl;
        }
    }
}

void Book::buyBook(string author, string title, int numCopies) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            if (sellCopies(i, numCopies)) {
                double totalAmount = numCopies * getPrice(i);
                cout << "Total amount: " << totalAmount << endl;
                return;
            } else {
                cout << "Failed to buy the book." << endl;
                return;
            }
        }
    }
    cout << "Book not found." << endl;
}

