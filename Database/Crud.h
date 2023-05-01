#include "sqlite3.h"
#include <iostream>
#include <vector>

using namespace std;

class CRUD {
    public:
        CRUD(sqlite3 *db);
        void CreateDB();
        void createObj(string classe, vector<string> atributos);
        vector<string> readObj(string classe, string nome);
        vector<string> readAll(string classe);
        void updateObj(string classe, string id, vector<string> atributos, vector<string> valores);
        void deleteObj(string classe, string id);
        vector<string> getColumnNames(string classe);   
        vector<string> getRelation(string classe, string id);

    
    private:
        sqlite3 *db;
        char *err_msg = 0;
        int rc;
};
