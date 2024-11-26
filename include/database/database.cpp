#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include "database.h"

using namespace std;

Book::Book(string title, int year, string genre){
    this->title = title;
    this->year = year;
    this->genre = genre;
}

void Book::print(){
    cout << title << ". " << genre << endl;
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

//Implemented in case get_fields didn't not work. However, it turned out the latter 
//is better than this
vector<string> match_fields(string book){
    vector<string> fields;
    regex pattern("Title:\\s*(.+?),\\s*Genre:\\s*(.+)");
    smatch matches;
    if(!regex_match(book, matches, pattern))
        return fields;
    fields.push_back(matches.str(1));
    fields.push_back(matches.str(2));
    return fields;
}

vector<string> get_fields(string book){
    vector<string> fields;
    int title_i = book.find("Title: ");
    int genre_i = book.find(", Genre:");
    char title[book.size()];
    book.copy(title, genre_i - 7 - title_i, 7 + title_i);
    title[genre_i - 7] = '\0';
    fields.push_back(title);
    char genre[book.size()];
    book.copy(genre, book.size() - genre_i - 9, genre_i+9);
    genre[book.size() - genre_i - 9] = '\0';
    fields.push_back(genre);

    return fields;
}


DataBase::DataBase(): table(100), cnt(0){}

DataBase::DataBase(string path, int year): table(100), cnt(0) {
    vector<string> lines = read_lines(path);

    if(lines.size() == 0)
        return;

    // Remove UTF-8 BOM if present
    const string utf8_bom = "\xEF\xBB\xBF";
    if (lines[0].compare(0, utf8_bom.size(), utf8_bom) == 0)
        lines[0].erase(0, utf8_bom.size());

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
    int title_width = 1;
    int genre_width = 1;
    for(int i=0; i<100; ++i){
        int len = table[i].size();
        for(int j=0; j<len; ++j){
            title_width = max(title_width, static_cast<int>(table[i][j].title.size()));
            genre_width = max(genre_width, static_cast<int>(table[i][j].genre.size()));
        }
    }

    int cnt_len = 1;
    for(int dec = 1; dec < cnt; dec *= 10)
        cnt_len++;
    
    // Print header
    cout << left << setw(cnt_len) << ""
         << left << setw(title_width + 2) << "Title"
         << "| "
         << left << setw(genre_width) << "Genre" << endl;
    cout    << setfill('-') << setw(cnt_len + title_width + genre_width + 4)
            << "" << setfill(' ') << endl;


    int line = 1;
    for(int i=0; i<100; ++i){
        int len = table[i].size();
        for(int j=0; j<len; ++j){
            cout    << left << setw(cnt_len) << line++
                    << left << setw(title_width + 2) << table[i][j].title
                    << "| "
                    << left << setw(genre_width) << table[i][j].genre
                    << endl;
        }
    }
    cout    << setfill('-') << setw(cnt_len + title_width + genre_width + 4) 
            << "" << setfill(' ') << endl;
    cout << endl;
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