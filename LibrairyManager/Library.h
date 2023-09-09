#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "Book.h"

class Library {
    private:
        std::vector<Book> books;

    public:
        Library(const std::vector<Book>& books);

        void addBook(const Book& book);
        const std::vector<Book> getBooks() const;
        std::vector<Book> searchBookByNameOrAuthor(const std::string& input);
        void removeBook(const std::string& isbn);
        void updateBook(const std::string& isbn, const std::string& newAuthor, const std::string& newTitle, int newPublicationDate);
};

#endif 
