#include "library.h"
#include <iostream>
#include <vector>


int main() {
    std::vector<book> library;
    loadLibrary(library, "library.txt");

    int choice;
    do {
        choice = printMenu();

        switch(choice) {
            case 1:
                printLibrary(library);
                pause();
                break;
            case 2:
                addBook(library);
                saveLibrary(library, "library.txt");
                pause();
                break;
            case 3:
                searchBook(library);
                pause();
                break;
            case 4:
                updateBook(library);
                saveLibrary(library, "library.txt");
                pause();
                break;
            case 5:
                deleteBook(library);
                saveLibrary(library, "library.txt");
                pause();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
        }
    } while (choice != 6);
    return 0;
}