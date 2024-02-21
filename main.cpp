#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string author[10];
    string title[10];
    int stock[10];
    string publisher[10];
    double price[10];

public:
    // Constructor
    Book() {
        // Initialize with predefined values
        addBook(0, "Yash", "Black", 2, "Bansal", 1000);
        addBook(1, "Karan", "Fairy Tales", 5, "Bansal", 500);
        addBook(2, "Ashutosh", "Horror Files", 3, "Patel", 800);
        addBook(3, "Om", "Embedded Copies", 4, "Gohel", 800);
        addBook(4, "Elizabeth", "Cosmic Rays", 0, "Richard", 1200);
    }

    // Function to add a book
    void addBook(int index, string author, string title, int stock, string publisher, double price) {
        if (index >= 0 && index < 10) {
            // Check if a book already exists at the given index
            if (this->author[index].empty() && this->title[index].empty()) {
                // Add the book only if the index is empty
                this->author[index] = author;
                this->title[index] = title;
                this->stock[index] = stock;
                this->publisher[index] = publisher;
                this->price[index] = price;
            } else {
                cout << "A book already exists at index " << index << ". Cannot add another book." << endl;
            }
        } else {
            cout << "Invalid index." << endl;
        }
    }

    // Function to check if the book is available
    bool isAvailable(int index) const {
        return stock[index] > 0;
    }

    // Function to get the price of the book
    double getPrice(int index) const {
        return price[index];
    }

    // Function to sell copies of the book
    bool sellCopies(const string& author, const string& title, int numCopies) {
        for (int i = 0; i < 10; ++i) {
            if (this->author[i] == author && this->title[i] == title) {
                if (stock[i] >= numCopies) {
                    stock[i] -= numCopies;
                    return true;
                } else {
                    cout << "Not enough copies available." << endl;
                    return false;
                }
            }
        }
        cout << "Book not found." << endl;
        return false;
    }

    // Function to display book details
    void displayDetails(int index) const {
        cout << "Title: " << title[index] << endl;
        cout << "Author: " << author[index] << endl;
        cout << "Publisher: " << publisher[index] << endl;
        cout << "Price: " << price[index] << endl;
        cout << "Stock: " << stock[index] << endl;
    }

    // Function to get author of the book
    string getAuthor(int index) const {
        return author[index];
    }

    // Function to get title of the book
    string getTitle(int index) const {
        return title[index];
    }
};

int main() {
    Book* library = new Book();

    char choice;
    int index;

    cout << "Do you want to add the book or buy the book\n";
    cout << "Type a to add and b for buy: ";
    cin >> choice;

    if (choice == 'a') {

        string author, title, publisher;
        double price;
        int stock;

        cout << "Enter the index to add a book: ";
        cin >> index;

        if (index >= 0 && index < 10) {
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

            library->addBook(index, author, title, stock, publisher, price);
        } else {
            cout << "Invalid index." << endl;
        }
    }

    else if (choice == 'b') {
        string bookAuthor, bookTitle;
        int numCopies;

        cout << "Enter the author of the book you want to buy: ";
        cin >> bookAuthor;
        cout << "Enter the title of the book you want to buy: ";
        cin >> bookTitle;

        // Search for the book and get its index
        for (int i = 0; i < 10; ++i) {
            if (library->getAuthor(i) == bookAuthor && library->getTitle(i) == bookTitle) {
                index = i;
                break;
            }
        }

        cout << "Enter the number of copies you want to buy: ";
        cin >> numCopies;

        if (library->sellCopies(bookAuthor, bookTitle, numCopies)) {
            double totalAmount = numCopies * library->getPrice(index);
            cout << "Total amount: " << totalAmount << endl;
        }
    }

    delete library;
    return 0;
}
