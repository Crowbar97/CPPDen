#include <iostream>
#include <string>

namespace book {

// Книга
class Book {

private:
    // идентификатор книги
    size_t isbn;
    std::string name;
    size_t edition;
    size_t year;
    std::string authors;
    size_t page_count;
    size_t bookmark;


public:
    Book(size_t id, const std::string &name) {
        this->isbn = id;
        this->name = name;
    }
    // why calling?
    Book() {
        std::cout << "book created!" << std::endl;
    }

public:
    friend std::ostream& operator<<(std::ostream& stream, const Book& b);
    bool operator!=(const Book& b);

    void open() {
        std::cout << "Книга открыта!" << std::endl;
    }
    void close() {
        std::cout << "Книга закрыта!" << std::endl;
    }
    void set_bookmark(size_t bookmark) {
        if (bookmark < 1 || bookmark > page_count)
            std::cout << "Закладка должна находиться внутри книги!" << std::endl;
        else
            this->bookmark = bookmark;
    }


    size_t get_isbn() const {
        return isbn;
    }
    std::string get_name() const {
        return name;
    }
    size_t get_edition() const {
        return edition;
    }
    size_t get_year() const {
        return year;
    }
    std::string get_authors() const {
        return authors;
    }
    size_t get_bookmark() const {
        return bookmark;
    }

    void set_isbn(size_t isbn) {
        this->isbn = isbn;
    }
    void set_name(const std::string& name) {
        this->name = name;
    }
    void set_edition(size_t edition) {
        this->edition = edition;
    }
    void set_authors(const std::string& authors) {
        this->authors = authors;
    }
};

// перегрузка оператора вывода
std::ostream& operator<<(std::ostream& stream, const Book& b) {
    stream << "(" << b.get_isbn() << ", " << b.get_name() << ")";
    return stream;
}

// перегрузка оператора неравенства
bool Book::operator!=(const Book& b) {
    return isbn != b.isbn;
}

}












