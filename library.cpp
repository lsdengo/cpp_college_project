#include "library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

int bookCounter = 0; // initializing a global counter

book createBook(std::string title, std::string author, int year, std::string genre, std::string isbn) {
    book b;
    b.id = ++bookCounter;
    b.title = title;
    b.author = author;
    b.year = year;
    b.genre = genre;
    b.isbn = isbn;
    return b;
}

void printBook(const book& b) {
    std:: cout << "ID: " << b.id << "\n"
               << "Title: " << b.title << "\n"
               << "Author: " << b.author << "\n"
               << "Year: " << b.year << "\n"
               << "Genre: " << b.genre << "\n"
               << "ISBN: " << b.isbn << "\n"
               << "-----------------------\n";
}

void printLibrary(const std::vector<book>& lib) {
    for (const auto& b: lib) {
        printBook(b);
    }
}

int printMenu() {
    int userChoice;
    do {
        std::cout << "\n=== Library ===\n";
        std::cout << "1. Show all books\n";
        std::cout << "2. Add a book\n";
        std::cout << "3. Book lookup\n";
        std::cout << "4. Update a book\n";
        std::cout << "5. Delete a book\n";
        std::cout << "6. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> userChoice;
        std::cout << "\n";

    } while (userChoice < 1 || userChoice > 6);

    return userChoice;
}

void addBook(std::vector<book>& lib) {
    std::string title, author, genre, isbn;
    int year;

    std::cin.ignore(); // cleans up the remaining newline from the previous cin

    std::cout << "Enter book title: ";
    std::getline(std::cin, title);

    std::cout << "Enter book author: ";
    std::getline(std::cin, author);

    std::cout << "Enter year: ";
    std::cin >> year;
    std::cin.ignore();

    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);

    // Creates and adds a new book
    book newBook = createBook(title, author, year, genre, isbn);
    lib.push_back(newBook);

    std::cout << "\nThe book \"" << newBook.title << "\" has been successfully added!\n";
}

void searchBook(const std::vector<book>& lib) {
    int option;
    std::cout << "Search via:\n1. ID\n2. Title\nYour choice: ";
    std::cin >> option;
    std::cout << "\n";

    if (option == 1) {
        int searchId;
        std::cout << "Enter book ID: ";
        std::cin >> searchId;

        bool found = false;
        for (const auto& b : lib) {
            if (b.id == searchId) {
                printBook(b);
                found = true;
                break;
            }
        }
        if (!found) std::cout << "No matching book with said ID.\n";

    } else if (option == 2) {
        std::cin.ignore();
        std::string searchTitle;
        std::cout << "Enter a book title: ";
        std::getline(std::cin, searchTitle);

        bool found = false;
        for (const auto& b : lib) {
            if (b.title == searchTitle) {
                printBook(b);
                found = true;
            }
        }
        if (!found) std::cout << "No matching book with said title.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void updateBook(std::vector<book>& lib) {
    int updateId;
    std::cout << "Enter book ID to update: ";
    std::cin >> updateId;
    std::cin.ignore(); // clearing the buffer

    bool found = false;
    for (auto& b : lib) {
        if (b.id == updateId) {
            found = true;
            std::string input;

            std::cout << "Enter a new title (leave blank for no change): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.title = input;

            std::cout << "Enter new author (leave blank for no change): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.author = input;

            std::cout << "Enter new year (leave blank for no change): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.year = std::stoi(input);

            std::cout << "Enter a new genre (leave blank for no change): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.genre = input;

            std::cout << "Enter new ISBN (leave blank for no change): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.isbn = input;

            std::cout << "\nThe book has been updated successfully!\n";
            break;
        }
    }

    if (!found) {
        std::cout << "No book found with ID: " << updateId << "\n";
    }
}

void pause() {
    std::cout << "\nPress enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // waits for a key press
}

// Reading books from a file
void loadLibrary(std::vector<book>& lib, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return; // if no file found, creates a new library

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, author, yearStr, genre, isbn;

        std::getline(ss, idStr, '|');
        std::getline(ss, title, '|');
        std::getline(ss, author, '|');
        std::getline(ss, yearStr, '|');
        std::getline(ss, genre, '|');
        std::getline(ss, isbn, '|');

        book b;
        b.id = std::stoi(idStr);
        b.title = title;
        b.author = author;
        b.year = std::stoi(yearStr);
        b.genre = genre;
        b.isbn = isbn;

        lib.push_back(b);

        if (b.id > bookCounter) bookCounter = b.id; // so that the IDs don't dublicate
    }

    file.close();
}

// Save books to a file
void saveLibrary(const std::vector<book>& lib, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& b : lib) {
        file << b.id << "|" << b.title << "|" << b.author << "|" 
             << b.year << "|" << b.genre << "|" << b.isbn << "\n";
    }
    file.close();
}

void deleteBook(std::vector<book>& lib) {
    int delId;
    std::cout << "Enter book ID to delete: ";
    std::cin >> delId;
    std::cin.ignore(); // buffer clear

    bool found = false;
    for (auto it = lib.begin(); it != lib.end(); ++it) {
        if (it->id == delId) {
            found = true;
            std::cout << "The book \"" << it->title << "\" will be deleted. Do you confirm? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            if (confirm == 'y' || confirm == 'Y') {
                lib.erase(it);
                std::cout << "The book has been successfully deleted!\n";
            } else {
                std::cout << "Deletion aborted.\n";
            }
            break;
        }
    }

    if (!found) {
        std::cout << "No book found with ID: " << delId << "\n";
    }
}