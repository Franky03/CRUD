#include "Crud.h"

void Executar(const char *sql_ms, sqlite3 *db, char *err_msg, int rc) {
    rc = sqlite3_exec(db, sql_ms, 0, 0, &err_msg);

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
}

int main(void){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = 0;

    int result = sqlite3_open("mydb.db", &db);
    if(result != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    //Tabela de Funcionários


    cout << "Opened database successfully" << endl;

    CRUD myCrud = CRUD(db);
    myCrud.CreateDB();
    
    vector<string> joao = myCrud.readObj("FUNCIONARIO", "Joao");

    vector<string> colunas =  myCrud.getColumnNames("FUNCIONARIO");
    cout << "Colunas: " << endl;
    for(int i = 0; i < colunas.size(); i++) {
        cout << colunas[i] << endl;
    }

 
    // for(int i = 0; i < joao.size(); i++) {
    //     cout << joao[i] << endl;
    // }

    vector<string> data2 = {"Joao Silva", "1200.4"}; 
    vector<string> atributos = {"nome", "salario"};

    //myCrud.updateObj("FUNCIONARIO", 3, atributos, data2);

    //joao = myCrud.readObj("FUNCIONARIO", "Joao");

    //for(int i = 0; i < joao.size(); i++) {
    //    cout << joao[i] << endl;
    //} 

    //vector<string> data = {"Projeto1", "Descricao1", "10", "1"};
    //myCrud.createObj("PROJETO", data);
    //nome, num_serie, modelo, disponivel
    vector<string> data1 = {"Equipamento1", "1", "Modelo1", "1", "2"};
    myCrud.createObj("EQUIPAMENTO", data1); 
    
    sqlite3_close(db);

    cout << "Closed database successfully" << endl;
    
    return 0;
}