#include <iostream>
#include "Book.h"
using namespace std;

int main() {
    int maxSize;
    cout << "Enter the maximum size of the library: ";
    cin >> maxSize;
    char choice;

    Book library(maxSize);
    while (choice != 'e') {

        cout << "Do you want to add, buy, or display the books?\n";
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

                library.addBook(author, title, stock, publisher, price);
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

                library.buyBook(bookAuthor, bookTitle, numCopies);
                break;
            }
            case 'd':
                library.displayAllBooks();
                break;
            case 'e':
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

