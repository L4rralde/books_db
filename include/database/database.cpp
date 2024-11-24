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
    cout << title << ", " << genre << endl;
}

bool Book::operator==(const Book &other){
    return title == other.title && genre == other.genre;
}

Frequency::Frequency(): key(""), cnt(0){}

Frequency::Frequency(string key): cnt(1){
    this->key = key;
}

bool Frequency::operator==(Frequency &other){
    return other.key == key;
}

bool Frequency::operator==(string &key){
    return this->key == key;
}

void Frequency::inc(){
    cnt++;
}

void Frequency::print(){
    cout << cnt << " " << key << endl;
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


DataBase::DataBase(): table(100), cnt(0) {}

DataBase::DataBase(string path, int year): table(100), cnt(0){
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

DataBase DataBase::operator&(DataBase &other){
    DataBase and_db;
    DataBase *small, *large;
    if(other.cnt > cnt){
        small = this;
        large = &other;
    }else{
        small = &other;
        large = this;
    }
    for(int i=0; i<100; ++i){
        for(int j=0; j < static_cast<int>(small->table[i].size()); ++j)
            if(large->exists(small->table[i][j]))
                and_db.add(small->table[i][j]);
    }

    return and_db;
}

DataBase DataBase::operator|(DataBase &other){
    DataBase or_db;
    for(int i=0; i<100; ++i){
        for(int j = 0; j < static_cast<int>(table[i].size()); ++j)
            or_db.add(table[i][j]);
        for(int j = 0; j < static_cast<int>(other.table[i].size()); ++j)
            or_db.add(other.table[i][j]);
    }
    return or_db;
}

DataBase DataBase::operator-(DataBase &other){
    DataBase wo_db;
    for(int i = 0; i < 100; ++i){
        for(int j = 0; j < static_cast<int>(table[i].size()); ++j){
            if(other.exists(table[i][j]))
                continue;
            wo_db.add(table[i][j]);
        }
    }
    return wo_db;
}

DataBase DataBase::operator^(DataBase &other){
    DataBase xor_db;
    DataBase or_db = this->operator|(other);
    DataBase and_db = this->operator&(other);
    return or_db - and_db;
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
    int len = table[idx].size();
    for(int j = 0; j < len; ++j)
        if(book == table[idx][j])
            return;
    cnt++;
    table[idx].push_back(book);
    
    len = genres.size();
    for(int j = 0; j < len; ++j){
        if(genres[j] == book.genre){
            genres[j].inc();
            return;
        }
    }

    genres.push_back(Frequency(book.genre));
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

bool DataBase::exists(const Book &book){
    int idx = hash(book.title);
    if(table[idx].empty())
        return false;
    int len = table[idx].size();
    for(int i=0; i<len; ++i)
        if(table[idx][i] == book)
            return true;
    return false;
}

void DataBase::show_genres(){
    int len = genres.size();
    for(int i = 0; i < len; ++i)
        genres[i].print();
}