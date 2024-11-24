#include <iostream>
#include <fstream>
#include <regex>
#include "database.h"

using namespace std;

Book::Book(string title, int year, string genre){
    this->title = title;
    this->year = year;
    this->genre = genre;
}

void Book::print(){
    cout << title << ". " << year << ". " << genre << endl;
}

vector<string> read_lines(string path){
    vector<string> lines;
    ifstream file(path);

    string line;

    if (file.is_open()) {
        while (getline(file, line))
            lines.push_back(line);
        file.close();
    }

    return lines;
}

vector<string> get_fields(string book){
    vector<string> fields;
    int idx = book.find(", Genre:");
    char title[book.size()];
    book.copy(title, idx - 7, 7);
    title[idx - 7] = '\0';
    fields.push_back(title);
    char genre[book.size()];
    book.copy(genre, book.size() - idx - 9, idx+9);
    genre[book.size() - idx - 9] = '\0';
    fields.push_back(genre);

    return fields;
}


DataBase::DataBase(string path, int year): table(100){
    vector<string> lines = read_lines(path);
    int n_lines = lines.size();
    for(int i=0; i<n_lines; ++i){
        vector<string> fields = get_fields(lines[i]);
        if(fields.size() != 2)
            continue;
        Book book(fields[0], year, fields[1]);
        add(book);
    }
}

int DataBase::hash(string input){
    int size = input.size();
    int acc = 0;
    for(int i=0; i<size; ++i)
        acc += input[i];
    return acc % 100;
}

void DataBase::add(Book book){
    int idx = hash(book.title);
    table[idx].push_back(book);
}

void DataBase::print(){
    for(int i=0; i<100; ++i){
        int len = table[i].size();
        for(int j=0; j<len; ++j)
            table[i][j].print();
    }
}

void print(DataBase &db){
    db.print();
}
