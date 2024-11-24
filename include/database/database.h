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
};

class DataBase{
private:
    vector< vector<Book> > table;
    int hash(string input);
public:
    DataBase(string path, int year);
    void add(Book book);
    void print();
};

vector<string> read_lines(string path);
vector<string> get_fields(string book);


void print(DataBase &db);

#endif