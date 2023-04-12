#include <iostream> 
#include <vector>
#include "sqlite3.h"

using namespace std;

//crie uma função para adicionar um objeto de uma classe que vai ser especificada como parametro e vai receber uma lista com os atributos do objeto
//exemplo: createObj("Funcionário", {1, "João", 20, "123.456.789-10", "1234-5678", "1234", "Pesquisador", 1000.00});
//exemplo: createObj("Pesquisador", {1, "João", 20, "123.456.789-10", "1234-5678", "1234", "Pesquisador", 1000.00, "Computação"});
//exemplo: createObj("Técnico", {1, "João", 20, "123.456.789-10", "1234-5678", "1234", "Pesquisador", 1000.00, "Computação"});
//exemplo: createObj("Equipamento", {1, "Computador", 1234, "Dell", true});
//exemplo: createObj("Projeto", {1, "Projeto 1", "Projeto de teste", 10});

void createObj(string classe, vector<string> atributos){
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    rc = sqlite3_open("mydb.db", &db);
    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    string sql = "INSERT INTO " + classe + " (";
    string values = " VALUES (";

    if(classe != "Projeto" && classe != "Equipamento"){
        sql += "nome, idade, cpf, telefone";
        values += "'" + atributos[0] + "', " + atributos[1] + ", '" + atributos[2] + "', '" + atributos[3] + "'";

        if(classe == "Funcionario"){
            sql += ", codigo, cargo, salario)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ")";
        }
        else if(classe == "Pesquisador" || classe == "Tecnico"){
            sql += ", codigo, cargo, salario, area)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ", '" + atributos[7] + "')";
        }
        else if(classe == "Cliente"){
            sql += ", encomenda, data)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "')";
        }
    }
    else if(classe == "Projeto"){
        sql += "titulo, descricao, duracao)";
        values += "'" + atributos[0] + "', '" + atributos[1] + "', " + atributos[2] + ")";
    }
    else if(classe == "Equipamento"){
        sql += "nome, num_serie, modelo, disponivel)",
        values += "'" + atributos[0] + "', " + atributos[1] + ", '" + atributos[2] + "', " + atributos[3] + ")";
    }

    sql += values;

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
    cout << "Objeto criado com sucesso!" << endl;
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