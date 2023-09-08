#include "Book.h"

Book::Book(
        const std::string& title, 
        const std::string& author, 
        const std::string& isbn, 
        int publicationDate
    ) : title(title), author(author), isbn(isbn), publicationDate(publicationDate) {}

std::string Book::getTitle() const {
    return title;
}

void Book::setTitle(const std::string& newTitle) {
    title = newTitle;
}

std::string Book::getAuthor() const {
    return author;
}

void Book::setAuthor(const std::string& newAuthor) {
    author = newAuthor;
}

std::string Book::getIsbn() const {
    return isbn;
}

void Book::setIsbn(const std::string& newIsbn) {
    isbn = newIsbn;
}

int Book::getPublicationDate() const {
    return publicationDate;
}

void Book::setPublicationDate(int newPublicationDate) {
    publicationDate = newPublicationDate;
}
