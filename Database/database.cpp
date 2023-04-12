#include <iostream> 
#include <vector>
#include "sqlite3.h"

using namespace std;

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

    const char *func_table = "CREATE TABLE IF NOT EXISTS FUNCIONARIO("
                             "id INT PRIMARY KEY NOT NULL,"
                             "nome TEXT NOT NULL,"
                             "idade INT NOT NULL,"
                             "cpf TEXT NOT NULL,"
                             "telefone TEXT NOT NULL,"
                             "codigo TEXT NOT NULL,"
                             "cargo TEXT NOT NULL,"
                             "salario REAL NOT NULL);";
                             

    result = sqlite3_exec(db, func_table, 0, 0, &err_msg);
    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    cout << "Passei daqui 1" << endl;

    //Tabela de Pesquisadores

    const char *research_table = "CREATE TABLE IF NOT EXISTS PESQUISADOR("
                                 "id INT PRIMARY KEY NOT NULL,"
                                 "nome TEXT NOT NULL,"
                                 "idade INT NOT NULL,"
                                 "cpf TEXT NOT NULL,"
                                 "telefone TEXT NOT NULL,"
                                 "codigo TEXT NOT NULL,"
                                 "cargo TEXT NOT NULL,"
                                 "salario REAL NOT NULL,"
                                 "area TEXT NOT NULL);";

    result = sqlite3_exec(db, research_table, 0, 0, &err_msg);
    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    cout << "Passei daqui 2" << endl;

    //Tabela de Projetos

    const char *project_table = "CREATE TABLE IF NOT EXISTS PROJETO("
                                "id INT PRIMARY KEY NOT NULL,"
                                "titulo TEXT NOT NULL,"
                                "descricao TEXT NOT NULL,"
                                "duracao INT NOT NULL);";
    
    result = sqlite3_exec(db, project_table, 0, 0, &err_msg);

    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    cout << "Passei daqui 3" << endl;

    //Tabela de Relacionamento

    const char *project_researcher = "CREATE TABLE IF NOT EXISTS PROJETO_PESQUISADOR("
                                     "id_projeto INT NOT NULL,"
                                     "id_pesquisador INT NOT NULL,"
                                     "FOREIGN KEY (id_projeto) REFERENCES PROJETO(id),"
                                     "FOREIGN KEY (id_pesquisador) REFERENCES PESQUISADOR(id));";
    
    result = sqlite3_exec(db, project_researcher, 0, 0, &err_msg);

    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    cout << "Passei daqui 4" << endl;

    // Tabela de Técnicos

    const char *tech_table = "CREATE TABLE IF NOT EXISTS TECNICO("
                             "id INT PRIMARY KEY NOT NULL,"
                             "nome TEXT NOT NULL,"
                             "idade INT NOT NULL,"
                             "cpf TEXT NOT NULL,"
                             "telefone TEXT NOT NULL,"
                             "codigo TEXT NOT NULL,"
                             "cargo TEXT NOT NULL,"
                             "salario REAL NOT NULL,"
                             "area TEXT NOT NULL);";

    result = sqlite3_exec(db, tech_table, 0, 0, &err_msg);

    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    cout << "Passei daqui 5" << endl;

    // Tabela de Equipamentos

    const char *equip_table = "CREATE TABLE IF NOT EXISTS EQUIPAMENTO("
                               "id INT PRIMARY KEY NOT NULL,"
                               "nome TEXT NOT NULL,"
                               "num_serie INT NOT NULL,"
                               "modelo TEXT NOT NULL,"
                               "disponivel BOOL NOT NULL);";
    
    result = sqlite3_exec(db, equip_table, 0, 0, &err_msg);
    
    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }


    // Tabela de Relacionamento

    const char *tech_equip = "CREATE TABLE IF NOT EXISTS TECNICO_EQUIPAMENTO("
                             "id_tecnico INT NOT NULL,"
                             "id_equipamento INT NOT NULL,"
                             "FOREIGN KEY (id_tecnico) REFERENCES TECNICO(id),"
                             "FOREIGN KEY (id_equipamento) REFERENCES EQUIPAMENTO(id));";
    
    result = sqlite3_exec(db, tech_equip, 0, 0, &err_msg);

    if(result != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }





    cout << "Opened database successfully" << endl;

    sqlite3_close(db);
    
    return 0;
}