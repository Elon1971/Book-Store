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
    Book(string author, string title, int stock, string publisher, double price)
        : author(author), title(title), stock(stock), publisher(publisher), price(price) {}

    bool isAvailable() const {
        return stock > 0;
    }

    double getPrice() const {
        return price;
    }

    bool sellCopies(int numCopies) {
        if (stock >= numCopies) {
            stock -= numCopies;
            return true;
        } else {
            cout << "Not enough copies available." << endl;
            return false;
        }
    }

    void displayDetails() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Price: " << price << endl;
        cout << "Stock: " << stock << endl;
    }

    string getAuthor() const {
        return author;
    }

    string getTitle() const {
        return title;
    }
};

int main() {
    Book* library = new Book[5] {
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

    if (author.empty() || title.empty()) {
        cout << "Author name or title cannot be empty." << endl;
        delete[] library;
        return 1;
    }

    bool found = false;
    for (int i = 0; i < 5; ++i) {
        if (library[i].getAuthor() == author && library[i].getTitle() == title && library[i].isAvailable()) {
            found = true;
            library[i].displayDetails();
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

    delete[] library;
    return 0;
}
