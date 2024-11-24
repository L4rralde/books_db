#include <iostream>
#include <string>
#include <vector>
#include "../include/database/database.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 3)
        return 0;
    
    DataBase db_2022(argv[1], 2022);
    DataBase db_2023(argv[2], 2023);

    DataBase db_union = db_2022 - db_2023;
    print(db_union);

    return 0;
}