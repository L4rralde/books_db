#include <iostream>
#include <string>
#include <vector>
#include "../include/database/database.h"

using namespace std;

void set_union(DataBase &db_2022, DataBase &db_2023){
    DataBase set_union = db_2022 | db_2023;
    set_union.set_name("Set Union");
    print(set_union);
    set_union.plot_load_factor();
    cout << endl;
}

void set_intersect(DataBase &db_2022, DataBase &db_2023){
    DataBase intersection = db_2022 & db_2023;
    intersection.set_name("Set Intersection");
    print(intersection);
    intersection.plot_load_factor();
    cout << endl;
}

void set_symm_diff(DataBase &db_2022, DataBase &db_2023){
    print(db_2022);
    db_2022.plot_load_factor();
    cout << endl;

    print(db_2023);
    db_2023.plot_load_factor();
    cout << endl;

    DataBase symm_diff = db_2022 ^ db_2023;
    symm_diff.set_name("Symmetric difference");
    print(symm_diff);
    symm_diff.plot_load_factor();
    cout << endl;
}

void set_diff(DataBase &db_2022, DataBase &db_2023){
    //2022 - 2023
    DataBase former_not_latter = db_2022 - db_2023;
    former_not_latter.set_name("2022 books except 2023");
    print(former_not_latter);
    former_not_latter.show_genres();
    former_not_latter.plot_load_factor();
    cout << endl;

    //2023 - 2022
    DataBase latter_not_former = db_2023 - db_2022;
    latter_not_former.set_name("2023 books except 2022");
    print(latter_not_former);
    latter_not_former.show_genres();
    latter_not_former.plot_load_factor();
    cout << endl;
}

int DataBase::instance_id = 0;

int main(int argc, char **argv){
    if(argc != 3)
        return 0;
    
    DataBase db_2022(argv[1], 2022);
    db_2022.set_name("2022 Database");
    DataBase db_2023(argv[2], 2023);
    db_2023.set_name("2023 Database");

    //Unión de conjuntos:
    set_union(db_2022, db_2023);

    //Intersección de conjuntos:
    set_intersect(db_2022, db_2023);

    //Diferencias de conjuntos:
    set_diff(db_2022, db_2023);

    //Diferencia simétrica
    set_symm_diff(db_2022, db_2023);

    return 0;
}

// Requirements
//  - [x] Generar 2 Tablas hash independientes, 
//      almacenando en cada una de ellas 300 títulos 
//      de libro (clave) y género literario (valor).
//  - [x] El tamaño de cada tabla será de 100 y el
//      encadenamiento es mediante arreglo de vectores
//
// Realizar las operacionesconjuntos de:
//  - [x] Unión
//  - [x] Intersección
//  - [x] Diferencia de ambos conjuntos
//  - [x] Diferencia Simétrica
//
//  - [x] Tabular los resultados con iomanip.
//  - [x] En Diferencia de conjuntos, mostrar la 
//      frecuencia de los generos en cada tabla
//  - [x] En Diferencia simétrica, mostrar la
//      información capturada de cada tabla
//
//  - [x] Graficar el factor de carga de cada tabla
//  - [x] Graficar mediante Cairo o GNUplot