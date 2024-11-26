/*
Librería de Bases de datos de libros mediante tablas Hash
Autor: Emmanuel A. Larralde Ortiz | emmanuel.larralde@cimat.mx
*/
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

using namespace std;

//Clase que contiene la información de un libro en la base de datos.
class Book{
public:
    string title; //Título
    int year; //Año
    string genre; //Género
    Book(string, int, string); //Constructor

    void print(); //Imprime en la terminal el contenido
    bool operator==(const Book &other);
};

//Clase que cuenta la repetición de una llave dada.
class Frequency{
public:
    string key;
    int cnt;
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
    string name;
    void print_name();
public:
    static int instance_id;
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
    void set_name(string in);
    void plot_load_factor();
};

vector<string> read_lines(string path);
vector<string> get_fields(string book);


void print(DataBase &db);

#endif