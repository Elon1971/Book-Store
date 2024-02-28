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
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <string>
#include <sstream>

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

    void addBook(string author, string title, int stock, string publisher, double price);
    bool isAvailable(int index) const;
    double getPrice(int index) const;
    bool sellCopies(int index, int numCopies);
    void removeEntryFromCSV(int index);
    void displayDetails(int index) const;
    void displayAllBooks() const;
    void buyBook(string author, string title, int numCopies);
    void updateDetail(const string& author, const string& title);
    void updateCS(const string& filename, const vector<string>& data);
    void updateCSV();
    int findBook(const string& author, const string& title);
};


int main() {
    int maxSize;
    cout << "Enter the maximum size of the library: ";
    cin >> maxSize;
    Book* library = new Book(maxSize);
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
        string bokAuthor, bokTitle;

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
            case 'u':
                cout << "Enter the name of the author you want to update the data of: ";
                cin >> bokAuthor;
                cout << "Enter the name of the title of the book you want to update of: ";
                cin >> bokTitle;

                library->updateDetail(bokAuthor, bokTitle);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    delete library;
    return 0;
}

Book::Book(int maxSize)
    : maxSize(maxSize) {
    author = new string[maxSize];
    title = new string[maxSize];
    stock = new int[maxSize];
    publisher = new string[maxSize];
    price = new double[maxSize];
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
        if (this->author[i] == author && this->title[i] == title) {
            cout << "Book already exists in the library. Skipping addition." << endl;
            return;
        }
    }

    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i].empty()) {
            this->author[i] = author;
            this->title[i] = title;
            this->stock[i] = stock;
            this->publisher[i] = publisher;
            this->price[i] = price;

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
        updateCSV();
        return true;
    } else {
        cout << "Not enough copies available." << endl;
        return false;
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

void Book::displayDetails(int index) const {
    cout << "Title: " << title[index] << endl;
    cout << "Author: " << author[index] << endl;
    cout << "Publisher: " << publisher[index] << endl;
    cout << "Price: " << price[index] << endl;
    cout << "Stock: " << stock[index] << endl;
    if (stock[index] == 0) {
        cout << "Out Of Stock" << endl;
    }
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



void Book::updateDetail(const string& author, const string& title) {
    int index = -1;
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        int choice;
        cout << "What do you want to update?\n";
        cout << "1. Stock\n";
        cout << "2. Price\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int newStock;
                cout << "Enter new stock: ";
                cin >> newStock;
                stock[index] = newStock;
                cout << "Stock updated successfully." << endl;
                updateCSV();
                break;
            }
            case 2: {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                price[index] = newPrice;
                cout << "Price updated successfully." << endl;
                updateCSV();
                break;
            }
            default:
                cout << "Invalid choice." << endl;
        }
    } else {
        cout << "Book not found." << endl;
    }
}

void Book::updateCSV() {
    ofstream outputfile("inventory.csv");
    if (outputfile.is_open()) {
        for (int i = 0; i < maxSize; ++i) {
            if (!author[i].empty()) {
                if (stock[i] > 0) {
                    outputfile << author[i] << ", " << title[i] << ", " << stock[i] << ", " << publisher[i] << ", " << price[i] << endl;
                } else {
                    outputfile << author[i] << ", " << title[i] << ", " << 0 << ", " << publisher[i] << ", " << price[i] << endl;
                }
            }
        }
        outputfile.close();
        cout << "CSV file updated successfully." << endl;
    } else {
        cerr << "Error opening file" << endl;
    }
}



int Book::findBook(const string& author, const string& title) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            return i; // Return the index of the book if found
        }
    }
    return -1; // Return -1 if the book is not found
}


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <string>
#include <sstream>

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

    void addBook(string author, string title, int stock, string publisher, double price);
    bool isAvailable(int index) const;
    double getPrice(int index) const;
    bool sellCopies(int index, int numCopies);
    void removeEntryFromCSV(int index);
    void displayDetails(int index) const;
    void displayAllBooks() const;
    void buyBook(string author, string title, int numCopies);
    void updateDetail(const string& author, const string& title);
    void updateCS(const string& filename, const vector<string>& data);
    void updateCSV();
    int findBook(const string& author, const string& title);
};


int main() {
    int maxSize;
    cout << "Enter the maximum size of the library: ";
    cin >> maxSize;
    Book* library = new Book(maxSize);
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
        string bokAuthor, bokTitle;

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
            case 'u':
                cout << "Enter the name of the author you want to update the data of: ";
                cin >> bokAuthor;
                cout << "Enter the name of the title of the book you want to update of: ";
                cin >> bokTitle;

                library->updateDetail(bokAuthor, bokTitle);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    delete library;
    return 0;
}

Book::Book(int maxSize)
    : maxSize(maxSize) {
    author = new string[maxSize];
    title = new string[maxSize];
    stock = new int[maxSize];
    publisher = new string[maxSize];
    price = new double[maxSize];
}

Book::~Book() {
    delete[] author;
    delete[] title;
    delete[] stock;
    delete[] publisher;
    delete[] price;
}

// void Book::addBook(string author, string title, int stock, string publisher, double price) {
//     // Check if the CSV file is empty
//     ifstream inputfile("inventory.csv");
//     if (inputfile.peek() != ifstream::traits_type::eof()) {
//         cout << "The library is already populated with data from the CSV file. Skipping addition of default books." << endl;
//         inputfile.close();
//         return;
//     }
//     inputfile.close();

//     // Proceed with adding the book
//     for (int i = 0; i < maxSize; ++i) {
//         if (this->author[i].empty()) {
//             this->author[i] = author;
//             this->title[i] = title;
//             this->stock[i] = stock;
//             this->publisher[i] = publisher;
//             this->price[i] = price;

//             // Append the new book to the CSV file
//             ofstream outputfile("inventory.csv", ios::app);
//             if (outputfile.is_open()) {
//                 outputfile << author << ", " << title << ", " << stock << ", " << publisher << ", " << price << endl;
//                 outputfile.close();
//                 cout << "Book added successfully." << endl;
//             } else {
//                 cerr << "Error opening file";
//             }
//             return;
//         }
//     }
//     cout << "Library is full. Cannot add more books." << endl;
// }


// bool isFirstRun = true; // Flag to track if it's the first run

// void Book::addBook(string author, string title, int stock, string publisher, double price) {
//     if (isFirstRun) {
//         // If it's the first run, add all default books
//         for (int i = 0; i < maxSize; ++i) {
//             if (this->author[i].empty()) {
//                 this->author[i] = author;
//                 this->title[i] = title;
//                 this->stock[i] = stock;
//                 this->publisher[i] = publisher;
//                 this->price[i] = price;
//                 cout << "Book added successfully." << endl;
                
//                 // Append the new book to the CSV file
//                 ofstream outputFile("inventory.csv", ios::app);
//                 if (outputFile.is_open()) {
//                     outputFile << author << ", " << title << ", " << stock << ", " << publisher << ", " << price << endl;
//                     outputFile.close();
//                 } else {
//                     cerr << "Error opening file";
//                 }
//                 return;
//             }
//         }
//         isFirstRun = false; // Set the flag to false after adding default books
//     } else {
//         // If it's not the first run, do not add default books
//         cout << "The library is already populated with data from the CSV file. Skipping addition of default books." << endl;
//     }
// }

void Book::addBook(string author, string title, int stock, string publisher, double price) {
    // Check if the library is already populated with data from the CSV file
    ifstream inputFile("inventory.csv");
    if (inputFile.peek() != ifstream::traits_type::eof()) {
        cout << "The library is already populated with data from the CSV file. Skipping addition of default books." << endl;
        inputFile.close();
        return;
    }
    inputFile.close();

    // Proceed with adding default books
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i].empty()) {
            this->author[i] = author;
            this->title[i] = title;
            this->stock[i] = stock;
            this->publisher[i] = publisher;
            this->price[i] = price;
            cout << "Book added successfully." << endl;

            // Append the new book to the CSV file
            ofstream outputFile("inventory.csv", ios::app);
            if (outputFile.is_open()) {
                outputFile << author << ", " << title << ", " << stock << ", " << publisher << ", " << price << endl;
                outputFile.close();
            } else {
                cerr << "Error opening file";
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
    if (stock[index] == 0) {
        cout << "The book is out of stock." << endl;
        return false;
    }
    
    if (stock[index] >= numCopies) {
        stock[index] -= numCopies;
        if (stock[index] == 0) {
            // Update CSV file to reflect changes
            updateCSV();
        }
        return true;
    } else {
        cout << "Not enough copies available." << endl;
        return false;
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

void Book::displayDetails(int index) const {
    cout << "Title: " << title[index] << endl;
    cout << "Author: " << author[index] << endl;
    cout << "Publisher: " << publisher[index] << endl;
    cout << "Price: " << price[index] << endl;
    cout << "Stock: " << stock[index] << endl;
    if (stock[index] == 0) {
        cout << "Out Of Stock" << endl;
    }
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



void Book::updateDetail(const string& author, const string& title) {
    int index = -1;
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        int choice;
        cout << "What do you want to update?\n";
        cout << "1. Stock\n";
        cout << "2. Price\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int newStock;
                cout << "Enter new stock: ";
                cin >> newStock;
                stock[index] = newStock;
                cout << "Stock updated successfully." << endl;
                updateCSV();
                break;
            }
            case 2: {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                price[index] = newPrice;
                cout << "Price updated successfully." << endl;
                updateCSV();
                break;
            }
            default:
                cout << "Invalid choice." << endl;
        }
    } else {
        cout << "Book not found." << endl;
    }
}

void Book::updateCSV() {
    ofstream outputfile("inventory.csv");
    if (outputfile.is_open()) {
        for (int i = 0; i < maxSize; ++i) {
            if (!author[i].empty()) {
                if (stock[i] > 0) {
                    outputfile << author[i] << ", " << title[i] << ", " << stock[i] << ", " << publisher[i] << ", " << price[i] << endl;
                } else {
                    outputfile << author[i] << ", " << title[i] << ", " << 0 << ", " << publisher[i] << ", " << price[i] << endl;
                }
            }
        }
        outputfile.close();
        cout << "CSV file updated successfully." << endl;
    } else {
        cerr << "Error opening file" << endl;
    }
}



int Book::findBook(const string& author, const string& title) {
    for (int i = 0; i < maxSize; ++i) {
        if (this->author[i] == author && this->title[i] == title) {
            return i; // Return the index of the book if found
        }
    }
    return -1; // Return -1 if the book is not found
}
