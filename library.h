#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

// Defining a book structure
struct book {
    int id;
    std::string title;
    std::string author;
    int year;
    std::string genre;
    std::string isbn;
};

// global ID counter
extern int bookCounter;

// Function declarations
book createBook(std::string title, std::string author, int year, std::string genre, std::string isbn);
void printBook(const book& b);
void printLibrary(const std::vector<book>& lib);
void addBook(std::vector<book>& lib);
void searchBook(const std::vector<book>& lib);
void updateBook(std::vector<book>& lib);
void deleteBook(std::vector<book>& lib);
void loadLibrary(std::vector<book>& lib, const std::string& filename);
void saveLibrary(const std::vector<book>& lib, const std::string& filename);
void pause();
int printMenu();

#endif // LIBRARY_H