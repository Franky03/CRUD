#include <iostream> 
#include "sqlite3.h"

using namespace std;

int main(void){
    sqlite3 *db;
    sqlite3_stmt *stmt;

    sqlite3_open("mydb.db", &db);
    cout << "Opened database successfully" << endl;
    
    return 0;
}