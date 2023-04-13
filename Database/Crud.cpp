#include "Crud.h"

CRUD::CRUD(sqlite3 *db)
{
    this->db = db;
}

void CRUD::createObj(string classe, vector<string> atributos){
    
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    string sql = "INSERT INTO " + classe + " (";
    string values = " VALUES (";

    if(classe != "PROJETO" && classe != "EQUIPAMENTO"){
        sql += "nome, idade, cpf, telefone";
        values += "'" + atributos[0] + "', " + atributos[1] + ", '" + atributos[2] + "', '" + atributos[3] + "'";

        if(classe == "FUNCIONARIO"){
            sql += ", codigo, cargo, salario)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ")";
        }
        else if(classe == "PESQUISADOR" || classe == "TECNICO"){
            sql += ", codigo, cargo, salario, area)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ", '" + atributos[7] + "')";
        }
        else if(classe == "CLIENTE"){
            sql += ", encomenda, data)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "')";
        }
    }
    else if(classe == "PROJETO"){
        sql += "titulo, descricao, duracao)";
        values += "'" + atributos[0] + "', '" + atributos[1] + "', " + atributos[2] + ")";
    }
    else if(classe == "EQUIPAMENTO"){
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

int searchByNameCallBack(void* data, int argc, char** argv, char** azColName){
    vector<string> *result = static_cast< vector<string> *>(data);
    for(int i = 0; i < argc; i++){
        result->push_back(argv[i]);
    }
    return 0;
}

vector<string> CRUD::readObj(string classe, string nome){

    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    vector<string> result;
    string sql = "SELECT * FROM " + classe + " WHERE nome LIKE '%" + nome + "%';";
    rc = sqlite3_exec(db, sql.c_str(), searchByNameCallBack, &result, &err_msg);

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }


    sqlite3_close(db);
    return result;
}

void CRUD::updateObj(string classe, int id, vector<string> atributos){
    
}