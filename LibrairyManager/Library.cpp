#include "Library.h"
#include "Book.h"
#include <string>
#include <vector>
#include <algorithm>

Library::Library(const std::vector<Book>& books): books(books) {}

void Library::addBook(const Book& book){
    books.push_back(book);
}

const std::vector<Book> Library::getBooks() const{
    return books;
}

std::vector<Book> Library::searchBookByNameOrAuthor(const std::string& input){
    std::vector<Book> result;
    for(const Book& book : books){
        if (book.getTitle().find(input) != std::string::npos || book.getAuthor().find(input) != std::string::npos) {
            result.push_back(book); 
        }
    }
    return result;
}

void Library::removeBook(const std::string& isbn){
    auto it = std::remove_if(
            books.begin(), 
            books.end(),
            [&isbn](const Book& book){
                return book.getIsbn() == isbn;
            }
        );
    if (it != books.end()){
        books.erase(it, books.end());
    }
}

void Library::updateBook(const std::string& isbn, const std::string& newAuthor, const std::string& newTitle, int newPublicationDate){
    for(auto& book : books){
        if(book.getIsbn() == isbn){
            book.setAuthor(newAuthor);
            book.setTitle(newTitle);
            book.setPublicationDate(newPublicationDate);
            return;
        }
    }
}
