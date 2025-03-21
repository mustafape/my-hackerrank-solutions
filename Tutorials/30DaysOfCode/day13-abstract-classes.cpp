#include <iostream>
#include <string>

using namespace std;

class Book {
protected:
    std::string m_title;
    std::string m_author;
    int m_price;

public:
    Book(const std::string& title, const std::string& author, int price)
        : m_title(title), m_author(author), m_price(price) {}

    virtual ~Book() = default;

    virtual std::string getTitle() const = 0;
    virtual std::string getAuthor() const = 0;
    virtual int getPrice() const = 0;
    virtual void display() const = 0;
};

class MyBook : public Book {
    friend istream& getline(istream &input, MyBook& obj);
public:
    MyBook(const std::string& title, const std::string& author, int price)
        : Book(title, author, price) {
            getline(cin, *this);
        }

    std::string getTitle() const override {
        return m_title;
    }

    std::string getAuthor() const override {
        return m_author;
    }

    int getPrice() const override {
        return m_price;
    }

    void display() const override {
        std::cout << "Title: " << m_title << "\n"
                  << "Author: " << m_author << "\n"
                  << "Price: " << m_price << std::endl;
    }
};

istream& getline(istream &input, MyBook& obj)
{
    getline(input, obj.m_title);
    getline(input, obj.m_author);
    input >> obj.m_price;
	return input;
}

int main() {
    MyBook book("The Alchemist", "Paulo Coelho", 248);
    book.display();
    return 0;
}