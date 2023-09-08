#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    int publicationDate;

public:
    Book(
        const std::string& title, 
        const std::string& author, 
        const std::string& isbn, 
        int publicationDate
    );

    std::string getTitle() const;
    void setTitle(const std::string& newTitle);

    std::string getAuthor() const;
    void setAuthor(const std::string& newAuthor);

    std::string getIsbn() const;
    void setIsbn(const std::string& newIsbn);

    int getPublicationDate() const;
    void setPublicationDate(int newPublicationDate);
};

#endif //BOOK_H
