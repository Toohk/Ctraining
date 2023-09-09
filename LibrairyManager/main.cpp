#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include "Book.h"
#include "Library.h"


void handleCommand(Library& lib1){

    while (true) {
    
        std::string line;
        std::string command;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        int arg4;
 
        std::cout << "Commands : [add, remove, update, list, search, quit]: \n";
        std::getline(std::cin, line);
        std::istringstream stream(line);
        stream >> command;

        if (command == "quit") {
            break;
        }

        if (command == "add") {
            if (stream >> arg1 && stream >> arg2 && stream >> arg3 && stream >> arg4) {
                Book newBook(arg1, arg2, arg3, arg4);
                lib1.addBook(newBook);
                std::cout << arg1 << " added to the library. \n";
            } else {
                std::cout << "Wrong format: NAME AUTHOR ISBN PUBLICATION_DATE \n";
            }
        }

        if (command == "update") {
            if (stream >> arg1 && stream >> arg2 && stream >> arg3 && stream >> arg4) {
                lib1.updateBook(arg1, arg2, arg3, arg4);
                std::cout << arg3 << " has been updated. \n";
            } else {
                std::cout << "Wrong format: ISBN -> AUTHOR TITLE ISBN PUBLICATION_DATE \n";
            }
        }

        if (command == "remove") {
            if (stream >> arg1) {
                lib1.removeBook(arg1);
            } else {
                std::cout << "ISBN required";
            }
        }

        if (command == "list") {
            const std::vector<Book>& allBooks = lib1.getBooks();
            for (const Book& book : allBooks) {
                std::cout << book.getTitle() << " \n";
            }
        }

        if (command == "search") {
            if (stream >> arg1) {
                std::vector<Book> allBooks = lib1.searchBookByNameOrAuthor(arg1);
                for (Book book : allBooks) {
                    std::cout << book.getTitle() << " \n";
                }
            } else {
                std::cout << "String required for search";
            }
        }
    }
}

int main () {
    Book b1("Book about all the things", "Polo", "B1", 10061998);
    Book b2("The great pickaxe", "Polo", "B2", 10041998);
    std::vector<Book> bookshelf;
    Library lib1(bookshelf);
    lib1.addBook(b1);
    lib1.addBook(b2);

    handleCommand(lib1);

    return 0;
}
