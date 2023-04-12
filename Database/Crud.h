#include "sqlite3.h"
#include <iostream>

using namespace std;

class CRUD {
    private:
        sqlite3 *db;
        char *err_msg = 0;
        int rc;
    public:
        CRUD();
        void createObj(string classe, vector<string> atributos);
        void readObj(string classe, string nome);
    
};
