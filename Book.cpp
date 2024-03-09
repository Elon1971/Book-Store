#include "Book.h"

// Constructor implementation
Book::Book(int maxSize)
    : maxSize(maxSize), nextIndex(0) {
    author = new string[maxSize];
    title = new string[maxSize];
    stock = new int[maxSize];
    publisher = new string[maxSize];
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

void Book::addBook(string author, string title, int stock, string publisher, double price) {
    if (nextIndex < maxSize) { // Ensure there's space available
        this->author[nextIndex] = author;
        this->title[nextIndex] = title;
        this->stock[nextIndex] = stock;
        this->publisher[nextIndex] = publisher;
        this->price[nextIndex] = price;
        nextIndex++; // Move to the next available index
    } else {
        cout << "Library is full. Cannot add more books." << endl;
    }
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
    for (int i = 0; i < nextIndex; ++i) {
        cout << "Book " << i+1 << ":" << endl;
        displayDetails(i);
        cout << endl;
    }
}

void Book::buyBook(string author, string title, int numCopies) {
    for (int i = 0; i < nextIndex; ++i) {
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

void Book::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < nextIndex; ++i) {
            file << author[i] << "," << title[i] << "," << stock[i] << "," << publisher[i] << "," << price[i] << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void Book::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Parse the line to extract book details
            size_t pos = 0;
            string token;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // Last token

            if (tokens.size() == 5) {
                addBook(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], stod(tokens[4]));
            }
        }
        file.close();
    } else {
        cout << "Unable to open file for reading. Starting with an empty library." << endl;
    }
}
