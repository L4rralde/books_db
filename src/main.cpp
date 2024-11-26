#include <iostream>
#include <string>
#include <vector>
#include "../include/database/database.h"

using namespace std;

void set_union(DataBase &db_2022, DataBase &db_2023){
    DataBase set_union = db_2022 | db_2023;
    cout << "Set Union:" << endl;
    print(set_union);
    cout << endl;
}

void set_intersect(DataBase &db_2022, DataBase &db_2023){
    DataBase intersection = db_2022 & db_2023;
    cout << "Set Intersection:" << endl;
    print(intersection);
    cout << endl;
}

void set_symm_diff(DataBase &db_2022, DataBase &db_2023){
    DataBase symm_diff = db_2022 ^ db_2023;
    cout << "Symmetric difference:" << endl;
    print(symm_diff);
    cout << endl;
}

void set_diff(DataBase &db_2022, DataBase &db_2023){
    //2022 - 2023
    DataBase former_not_latter = db_2022 - db_2023;
    cout << "2022 books except 2023:" << endl;
    print(former_not_latter);
    cout << "Genres' frequencies" << endl;
    former_not_latter.show_genres();
    cout << endl;

    //2023 - 2022
    DataBase latter_not_former = db_2023 - db_2022;
    cout << "2023 books except 2022:" << endl;
    print(latter_not_former);
    cout << "Genres' frequencies" << endl;
    latter_not_former.show_genres();
    cout << endl;
}

int main(int argc, char **argv){
    if(argc != 3)
        return 0;
    
    DataBase db_2022(argv[1], 2022);
    DataBase db_2023(argv[2], 2023);

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

