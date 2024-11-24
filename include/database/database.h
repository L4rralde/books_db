#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

using namespace std;

class Book{
public:
    string title;
    int year;
    string genre;
    Book(string, int, string);

    void print();
    bool operator==(const Book &other);
};

class DataBase{
private:
    vector< vector<Book> > table;
    int hash(string input);
    int cnt;
public:
    DataBase();
    DataBase(string path, int year);

    DataBase operator&(DataBase &other);
    DataBase operator|(DataBase &other);
    DataBase operator-(DataBase &other);    

    void add(Book book);
    void print();
    bool exists(const Book &book);
};

vector<string> read_lines(string path);
vector<string> get_fields(string book);


void print(DataBase &db);

#endif