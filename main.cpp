#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <string>

class Book {
private:
    string* author;
    string* title;
    int* stock;
    string* publisher;
    double* price;
    int maxSize;

public:
    // Constructor and destructor
    Book(int maxSize = 10);
    ~Book();

    // Function to add a book
    void addBook(string author, string title, int stock, string publisher, double price);

    // Function to check if the book is available
    bool isAvailable(int index) const;

    // Function to get the price of the book
    double getPrice(int index) const;

    // Function to sell copies of the book
    bool sellCopies(int index, int numCopies);

    void removeEntryFromCSV(int index);

    // Function to display book details
    void displayDetails(int index) const;

    // Function to display all available books
    void displayAllBooks() const;

    // Function to buy a book
    void buyBook(string author, string title, int numCopies);
};


int main() {
    int maxSize;
    cout << "Enter the maximum size of the library: ";
    cin >> maxSize;

    // Create Book library dynamically
    Book* library = new Book(maxSize);

    // Add default books
    library->addBook("Yash", "Black", 2, "Bansal", 1000);
    library->addBook("Karan", "Fairy Tales", 5, "Bansal", 500);
    library->addBook("Ashutosh", "Horror Files", 3, "Patel", 800);
    library->addBook("Om", "Embedded Copies", 4, "Gohel", 800);
    library->addBook("Elizabeth", "Cosmic Rays", 0, "Richard", 1200);

    char choice;
    while (choice != 'e') {
        cout << "Do you want to add, buy, display, or exit?\n";
        cout << "Type 'a' to add, 'b' to buy, 'd' to display, 'e' to exit: ";
        cin >> choice;

        switch (choice) {
            case 'a': {
                string author, title, publisher;
                double price;
                int stock;

                cout << "Enter author name: ";
                cin >> author;
                cout << "Enter title: ";
                cin >> title;
                cout << "Enter stock: ";
                cin >> stock;
                cout << "Enter publisher: ";
                cin >> publisher;
                cout << "Enter price: ";
                cin >> price;

                library->addBook(author, title, stock, publisher, price);
                break;
            }
            case 'b': {
                string bookAuthor, bookTitle;
                int numCopies;

                cout << "Enter the author of the book you want to buy: ";
                cin >> bookAuthor;
                cout << "Enter the title of the book you want to buy: ";
                cin >> bookTitle;
                cout << "Enter the number of copies you want to buy: ";
                cin >> numCopies;

                library->buyBook(bookAuthor, bookTitle, numCopies);
                break;
            }
            case 'd':
                library->displayAllBooks();
                break;
            case 'e':
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    // Free allocated memory
    delete library;
    return 0;
}

// Constructor implementation
Book::Book(int maxSize)
    : maxSize(maxSize) {
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
    // Check if the book already exists in the library
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            cout << "Book already exists in the library. Skipping addition." << endl;
            return;
        }
    }

    // Find an empty slot in the library to add the new book
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i].empty()) { // Check if slot is empty
            this->author[i] = author;
            this->title[i] = title;
            this->stock[i] = stock;
            this->publisher[i] = publisher;
            this->price[i] = price;

            // Check if the book already exists in the CSV file
            ifstream inputfile("inventory.csv");
            string line;
            bool alreadyExists = false;
            while (getline(inputfile, line)) {
                if (line.find(author) != string::npos && line.find(title) != string::npos) {
                    alreadyExists = true;
                    break;
                }
            }
            inputfile.close();

            // Append the new book to the CSV file only if it doesn't already exist
            if (!alreadyExists) {
                ofstream outputfile("inventory.csv", ios::app);
                if (outputfile.is_open()) {
                    outputfile << author << ", " << title << ", " << stock << ", " << publisher << ", " << price << endl;
                    outputfile.close();
                } else {
                    cerr << "Error opening file";
                }
                cout << "Book added successfully." << endl;
            }
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
        if (stock[index] == 0) {
            author[index] = "Unknown";
            title[index] = "Untitled";
            stock[index] = 0;
            publisher[index] = "Unknown";
            price[index] = 0.0;
            removeEntryFromCSV(index);
        }
        return true;
    } else {
        cout << "Not enough copies available." << endl;
        return false;
    }
}

void Book::removeEntryFromCSV(int index) {
    ifstream inputFile("inventory.csv");
    ofstream tempFile("temp.csv");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        int count = 0;
        while (getline(inputFile, line)) {
            if (count != index) {
                tempFile << line << endl;
            }
            count++;
        }
        inputFile.close();
        tempFile.close();

        remove("inventory.csv");
        rename("temp.csv", "inventory.csv");
    } else {
        cerr << "Error opening file";
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
        if (!author[i].empty()) {
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
