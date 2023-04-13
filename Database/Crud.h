#include "sqlite3.h"
#include <iostream>
#include <vector>

using namespace std;

class CRUD {
    private:
        sqlite3 *db;
        char *err_msg = 0;
        int rc;
    public:
        CRUD(sqlite3 *db);
        void CreateDB();
        void createObj(string classe, vector<string> atributos);
        vector<string> readObj(string classe, string nome);
        void updateObj(string classe, int id, vector<string> atributos, vector<string> valores);
        void deleteObj(string classe, int id);
    
};
