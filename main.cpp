#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string author;
    string title;
    int stock;
    string publisher;
    double price;

public:
    // Constructor
    Book(string author, string title, int stock, string publisher, double price)
        : author(author), title(title), stock(stock), publisher(publisher), price(price) {}

    // Function to check if the book is available
    bool isAvailable() const {
        return stock > 0;
    }

    // Function to get the price of the book
    double getPrice() const {
        return price;
    }

    // Function to sell copies of the book
    bool sellCopies(int numCopies) {
        if (stock >= numCopies) {
            stock -= numCopies;
            return true;
        } else {
            cout << "Not enough copies available." << endl;
            return false;
        }
    }

    // Function to display book details
    void displayDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Price: " << price << endl;
        cout << "Stock: " << stock << endl;
    }

    // Function to get author of the book
    string getAuthor() const {
        return author;
    }

    // Function to get title of the book
    string getTitle() const {
        return title;
    }
};

int main() {
    // Create an array of books
    Book library[5] = {
        Book("Yash", "Black", 2, "Bansal", 1000),
        Book("Karan", "Fairy Tales", 5, "Bansal", 500),
        Book("Ashutosh", "Horror Files", 3, "Patel", 800),
        Book("Om", "Embedded Copies", 4, "Gohel", 800),
        Book("Elizabeth", "Cosmic Rays", 0, "Richard", 1200)
    };

    string author, title;
    cout << "Enter the author name: ";
    cin >> author;
    cout << "Enter the title: ";
    cin >> title;

    bool found = false;
    for (int i = 0; i < 5; ++i) {
        library[i].displayDetails();  // Display book details
        if (library[i].isAvailable() && library[i].getAuthor() == author && library[i].getTitle() == title) {
            found = true;
            int numCopies;
            cout << "Enter the number of copies required: ";
            cin >> numCopies;
            if (library[i].sellCopies(numCopies)) {
                double totalAmount = numCopies * library[i].getPrice();
                cout << "Total amount: " << totalAmount << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Book not found or not available." << endl;
    }

    return 0;
}