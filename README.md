# 📚 BookVault - Library Management Console Application

## Description
BookVault is a console-based library management application written in C++ with a modular structure (header + cpp files).  
It provides full CRUD operations for books and stores data in a text file (`library.txt`).  
The goal of the project is to demonstrate skills in working with structures, vectors, file handling, basic algorithms, and organizing code into separate modules.

---

## ⚙️ Features
- **View all books** – display a list of all books in the library.  
- **Add a book** – enter a new book with ID, title, author, year, genre, and ISBN.  
- **Search a book** – search by ID or title.  
- **Update a book** – edit an existing book (with the option to leave some fields unchanged).  
- **Delete a book** – remove a book by ID with confirmation.  
- **File persistence** – automatically read and write library data from `library.txt`.  
- **Modular code** – CRUD functions implemented in `library.cpp` and declared in `library.h`.  

---

## 🛠️ Technologies
- **Language:** C++17  
- **Data structures:** `struct book`, `std::vector<book>`  
- **File handling:** read/write from a text file  
- **Interface:** console-based menu system  

---

## 📁 Project Structure
BookVault/<br> 
├── main.cpp # main.cpp # Main file with the menu and program loop<br>
├── library.h # Header file with CRUD declarations and book struct<br>
├── library.cpp # Implementation of CRUD functions and file handling<br>
├── library.txt # Data file for storing books<br>
└── Makefile # Build configuration

---

## 🚀 How to Run
1. Compile with Makefile:  
make
3. Run the program:
./BookVault
3. Follow the menu to manage the library.
   
---

## 💡 Possible improvements
- Introduce a graphical interface (e.g., Qt or SFML)
- Replace text file storage with a database
