#include "library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

int bookCounter = 0; // дефиниция на глобалния брояч

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
               << "Заглавие: " << b.title << "\n"
               << "Автор: " << b.author << "\n"
               << "Година: " << b.year << "\n"
               << "Жанр: " << b.genre << "\n"
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
        std::cout << "\n=== Библиотека ===\n";
        std::cout << "1. Покажи всички книги\n";
        std::cout << "2. Добави книга\n";
        std::cout << "3. Търси книга\n";
        std::cout << "4. Обнови книга\n";
        std::cout << "5. Изтрий книга\n";
        std::cout << "6. Изход\n";
        std::cout << "Вашият избор: ";
        std::cin >> userChoice;
        std::cout << "\n";

    } while (userChoice < 1 || userChoice > 6);

    return userChoice;
}

void addBook(std::vector<book>& lib) {
    std::string title, author, genre, isbn;
    int year;

    std::cin.ignore(); // чисти оставащия newline от предишния cin

    std::cout << "Въведете заглавие: ";
    std::getline(std::cin, title);

    std::cout << "Въведете автор: ";
    std::getline(std::cin, author);

    std::cout << "Въведете година: ";
    std::cin >> year;
    std::cin.ignore(); // пак чистим буфера

    std::cout << "Въведете жанр: ";
    std::getline(std::cin, genre);

    std::cout << "Въведете ISBN: ";
    std::getline(std::cin, isbn);

    // Създава нова книга и я добавя
    book newBook = createBook(title, author, year, genre, isbn);
    lib.push_back(newBook);

    std::cout << "\nКнигата \"" << newBook.title << "\" беше добавена успешно!\n";
}

void searchBook(const std::vector<book>& lib) {
    int option;
    std::cout << "Търсене по:\n1. ID\n2. Заглавие\nВаш избор: ";
    std::cin >> option;
    std::cout << "\n";

    if (option == 1) {
        int searchId;
        std::cout << "Въведете ID: ";
        std::cin >> searchId;

        bool found = false;
        for (const auto& b : lib) {
            if (b.id == searchId) {
                printBook(b);
                found = true;
                break;
            }
        }
        if (!found) std::cout << "Няма книга с такова ID.\n";

    } else if (option == 2) {
        std::cin.ignore();
        std::string searchTitle;
        std::cout << "Въведете заглавие: ";
        std::getline(std::cin, searchTitle);

        bool found = false;
        for (const auto& b : lib) {
            if (b.title == searchTitle) {
                printBook(b);
                found = true;
            }
        }
        if (!found) std::cout << "Няма книга с такова заглавие.\n";
    } else {
        std::cout << "Невалиден избор.\n";
    }
}

void updateBook(std::vector<book>& lib) {
    int updateId;
    std::cout << "Въведете ID на книгата за обновяване: ";
    std::cin >> updateId;
    std::cin.ignore(); // чистим буфера

    bool found = false;
    for (auto& b : lib) {
        if (b.id == updateId) {
            found = true;
            std::string input;

            std::cout << "Въведете ново заглавие (оставете празно за без промяна): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.title = input;

            std::cout << "Въведете нов автор (оставете празно за без промяна): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.author = input;

            std::cout << "Въведете нова година (оставете празно за без промяна): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.year = std::stoi(input);

            std::cout << "Въведете нов жанр (оставете празно за без промяна): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.genre = input;

            std::cout << "Въведете нов ISBN (оставете празно за без промяна): ";
            std::getline(std::cin, input);
            if (!input.empty()) b.isbn = input;

            std::cout << "\nКнигата беше успешно обновена!\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Няма книга с ID: " << updateId << "\n";
    }
}

void pause() {
    std::cout << "\nНатиснете Enter, за да продължите...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // изчаква натискане на Enter
}

// Четене на книги от файл
void loadLibrary(std::vector<book>& lib, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return; // ако няма файл, започваме празна библиотека

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

        if (b.id > bookCounter) bookCounter = b.id; // за да не се дублират ID-та
    }

    file.close();
}

// Записване на книги във файл
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
    std::cout << "Въведете ID на книгата за изтриване: ";
    std::cin >> delId;
    std::cin.ignore(); // чистим буфера

    bool found = false;
    for (auto it = lib.begin(); it != lib.end(); ++it) {
        if (it->id == delId) {
            found = true;
            std::cout << "Книгата \"" << it->title << "\" ще бъде изтрита. Потвърждавате ли? (y/n): ";
            char confirm;
            std::cin >> confirm;
            std::cin.ignore();
            if (confirm == 'y' || confirm == 'Y') {
                lib.erase(it);
                std::cout << "Книгата беше успешно изтрита!\n";
            } else {
                std::cout << "Изтриването беше отменено.\n";
            }
            break;
        }
    }

    if (!found) {
        std::cout << "Няма книга с ID: " << delId << "\n";
    }
}