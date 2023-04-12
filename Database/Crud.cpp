#include "Crud.h"

void CRUD::createObj(string classe, vector<string> atributos){
    
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

void CRUD::readObj(string classe, string nome){

    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    string sql = "SELECT * from " + classe + "WHERE"


}