#include <iostream>
#include <string>
#include <map>
#include <sstream>

class PhoneBook {
private:
    std::map<std::string, std::string> phoneBook;

public:
    void addEntry(const std::string& name, const std::string& phoneNumber) {
        phoneBook[name] = phoneNumber;
    }

    std::string getPhoneNumber(const std::string& name) const {
        auto it = phoneBook.find(name);
        if (it != phoneBook.end()) {
            return it->second;
        } else {
            return "Not found";
        }
    }

    void printPhoneNumber(const std::string& name) const {
        auto it = phoneBook.find(name);
        if (it != phoneBook.end()) {
            std::cout << name << "=" << it->second << std::endl;
        } else {
            std::cout << "Not found" << std::endl;
        }
    }

    void printAllEntries() const {
        for (const auto& entry : phoneBook) {
            std::cout << entry.first << ": " << entry.second << std::endl;
        }
    }

    void getEntriesFromConsole() {
        int n;
        std::cin >> n;
        std::cin.ignore(); // To ignore the newline character after the number input

        for (int i = 0; i < n; ++i) {
            std::string line, name, phoneNumber;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            iss >> name >> phoneNumber;
            addEntry(name, phoneNumber);
        }
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    PhoneBook pb;
    pb.getEntriesFromConsole();
    std::string query;
    while (std::getline(std::cin, query)) {
        pb.printPhoneNumber(query);
    }
    return 0;
}