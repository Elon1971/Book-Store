#include <iostream>
#include "Book.h"

int main() {
    int maxSize;
    std::cout << "Enter the maximum size of the library: ";
    std::cin >> maxSize;

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
        std::cout << "Do you want to add, buy, display, or exit?\n";
        std::cout << "Type 'a' to add, 'b' to buy, 'd' to display, 'e' to exit: ";
        std::cin >> choice;

        switch (choice) {
            case 'a': {
                std::string author, title, publisher;
                double price;
                int stock;

                std::cout << "Enter author name: ";
                std::cin >> author;
                std::cout << "Enter title: ";
                std::cin >> title;
                std::cout << "Enter stock: ";
                std::cin >> stock;
                std::cout << "Enter publisher: ";
                std::cin >> publisher;
                std::cout << "Enter price: ";
                std::cin >> price;

                library->addBook(author, title, stock, publisher, price);
                break;
            }
            case 'b': {
                std::string bookAuthor, bookTitle;
                int numCopies;

                std::cout << "Enter the author of the book you want to buy: ";
                std::cin >> bookAuthor;
                std::cout << "Enter the title of the book you want to buy: ";
                std::cin >> bookTitle;
                std::cout << "Enter the number of copies you want to buy: ";
                std::cin >> numCopies;

                library->buyBook(bookAuthor, bookTitle, numCopies);
                break;
            }
            case 'd':
                library->displayAllBooks();
                break;
            case 'e':
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    // Free allocated memory
    delete library;
    return 0;
}
