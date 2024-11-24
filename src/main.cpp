#include <iostream>
#include <string>
#include <vector>
#include "../include/database/database.h"

using namespace std;

int main(int argc, char **argv){
    if(argc != 2)
        return 0;
    
    DataBase db_2022(argv[1], 2022);
    db_2022.print();
    return 0;
}