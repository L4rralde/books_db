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

class Frequency{
private:
    string key;
    int cnt;
public:
    Frequency();
    Frequency(string key);
    bool operator==(Frequency &other);
    bool operator==(string &key);

    void inc();
    void print();
};


class DataBase{
private:
    vector< vector<Book> > table;
    vector<Frequency> genres;
    int hash(string input);
    int cnt;
public:
    DataBase();
    DataBase(string path, int year);

    DataBase operator&(DataBase &other);
    DataBase operator|(DataBase &other);
    DataBase operator-(DataBase &other);    
    DataBase operator^(DataBase &other);

    void add(Book book);
    void print();
    bool exists(const Book &book);
    void show_genres();
};

vector<string> read_lines(string path);
vector<string> get_fields(string book);


void print(DataBase &db);

#endif