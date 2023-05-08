#include "Crud.h"
#include <cctype>
#include <string.h>

CRUD::CRUD(sqlite3 *db)
{
    this->db = db;
}
 
void Execute(const char *sql_ms, sqlite3 *db, char *err_msg, int rc) {
    rc = sqlite3_exec(db, sql_ms, 0, 0, &err_msg);

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
}

int searchByNameCallBack(void* data, int argc, char** argv, char** azColName){
    vector<string> *result = static_cast< vector<string> *>(data);
    for(int i = 0; i < argc; i++){
        result->push_back(argv[i]);
    }
    return 0;
}


int getIdFromNameCallback(void* data, int argc, char** argv, char** azColName){
    if(argc != 1){
        cerr << "Callback error: invalid number of columns" << endl;
        return SQLITE_ERROR;
    }
    string* result = static_cast<string*>(data);
    *result = argv[0];
    return SQLITE_OK;
}

void CRUD::CreateDB(){

    int result = sqlite3_open("mydb.db", &db);

    if(result != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    //Tabela de Funcionários

    const char *func_table = "CREATE TABLE IF NOT EXISTS FUNCIONARIO("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "nome TEXT NOT NULL,"
                             "idade INTEGER NOT NULL,"
                             "cpf TEXT NOT NULL,"
                             "telefone TEXT NOT NULL,"
                             "codigo TEXT NOT NULL,"
                             "cargo TEXT NOT NULL,"
                             "salario REAL NOT NULL);";
                             

    Execute(func_table, db, err_msg, result);

    //Tabela de Pesquisadores

    const char *research_table = "CREATE TABLE IF NOT EXISTS PESQUISADOR("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "nome TEXT NOT NULL,"
                                 "idade INTEGER NOT NULL,"
                                 "cpf TEXT NOT NULL,"
                                 "telefone TEXT NOT NULL,"
                                 "codigo TEXT NOT NULL,"
                                 "cargo TEXT NOT NULL,"
                                 "salario REAL NOT NULL,"
                                 "area TEXT NOT NULL);";

    Execute(research_table, db, err_msg, result);

    //Tabela de Projetos

    const char *project_table = "CREATE TABLE IF NOT EXISTS PROJETO("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "nome TEXT NOT NULL,"
                                "descricao TEXT NOT NULL,"
                                "duracao INTEGER NOT NULL);";
    
    Execute(project_table, db, err_msg, result);

    //Tabela de Relacionamento

    const char *project_researcher = "CREATE TABLE IF NOT EXISTS PROJETO_PESQUISADOR("
                                     "id_projeto INTEGER NOT NULL,"
                                     "id_pesquisador INTEGER NOT NULL,"
                                     "PRIMARY KEY (id_projeto,id_pesquisador),"
                                     "FOREIGN KEY (id_projeto) REFERENCES PROJETO(id),"
                                     "FOREIGN KEY (id_pesquisador) REFERENCES PESQUISADOR(id));";
    
    Execute(project_researcher, db, err_msg, result);

    // Tabela de Técnicos

    const char *tech_table = "CREATE TABLE IF NOT EXISTS TECNICO("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "nome TEXT NOT NULL,"
                             "idade INTEGER NOT NULL,"
                             "cpf TEXT NOT NULL,"
                             "telefone TEXT NOT NULL,"
                             "codigo TEXT NOT NULL,"
                             "cargo TEXT NOT NULL,"
                             "salario REAL NOT NULL,"
                             "area TEXT NOT NULL);";

    Execute(tech_table, db, err_msg, result);

    // Tabela de Equipamentos

    const char *equip_table = "CREATE TABLE IF NOT EXISTS EQUIPAMENTO("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "nome TEXT NOT NULL,"
                               "num_serie INTEGER NOT NULL,"
                               "modelo TEXT NOT NULL,"
                               "disponivel BOOL NOT NULL);";
    
    Execute(equip_table, db, err_msg, result);

    // Tabela de Relacionamento

    const char *tech_equip = "CREATE TABLE IF NOT EXISTS TECNICO_EQUIPAMENTO("
                             "id_tecnico INTEGER NOT NULL,"
                             "id_equipamento INTEGER NOT NULL,"
                             "PRIMARY KEY (id_tecnico, id_equipamento),"
                             "FOREIGN KEY (id_tecnico) REFERENCES TECNICO(id),"
                             "FOREIGN KEY (id_equipamento) REFERENCES EQUIPAMENTO(id));";
    
    Execute(tech_equip, db, err_msg, result);

    const char *cliente_table = "CREATE TABLE IF NOT EXISTS CLIENTE("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "nome TEXT NOT NULL,"
                                "idade INTEGER NOT NULL,"
                                "cpf TEXT NOT NULL,"
                                "telefone TEXT NOT NULL,"
                                "encomenda TEXT NOT NULL,"
                                "data TEXT NOT NULL,"
                                "devendo REAL NOT NULL);";

    Execute(cliente_table, db, err_msg, result);

    cout << "Opened database successfully" << endl;

    sqlite3_close(db);

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
    string sql2;

    if(classe != "PROJETO" && classe != "EQUIPAMENTO"){
        sql += "nome, idade, cpf, telefone";
        values += "'" + atributos[0] + "', " + atributos[1] + ", '" + atributos[2] + "', '" + atributos[3] + "'";
        //verifica cpf repetido
        sql2 = "SELECT cpf FROM " + classe + " WHERE cpf = '" + atributos[2] + "';";
        vector<string> result;
        rc = sqlite3_exec(db, sql2.c_str(), searchByNameCallBack, &result, &err_msg);
        if(rc != SQLITE_OK ) {
            cerr << "SQL error: " << err_msg << endl;
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
        if(result.size() > 0){
            cout << "CPF já cadastrado, tente novamente." << endl;
            sqlite3_close(db);
            return;
        }

        if(classe == "FUNCIONARIO"){
            sql += ", codigo, cargo, salario)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ")";
        }
        else if(classe == "PESQUISADOR" || classe == "TECNICO"){
            sql += ", codigo, cargo, salario, area)";
            values += ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ", '" + atributos[7] + "')";
        }
        else if(classe == "CLIENTE"){
            sql += ", encomenda, data, devendo)";
            values +=  ", '" + atributos[4] + "', '" + atributos[5] + "', " + atributos[6] + ")";
        }
    }
    else if(classe == "PROJETO"){
        sql += "nome, descricao, duracao)";
        values += "'" + atributos[0] + "', '" + atributos[1] + "', " + atributos[2] + ")";

        // Adicionar registro na tabela de relacionamento de projeto-pesquisador
        cout << "Atributo 3: " << atributos[3] << endl;
        sql2 = " INSERT INTO PROJETO_PESQUISADOR (id_projeto, id_pesquisador) VALUES ((SELECT MAX(id) FROM PROJETO), " + atributos[3]+ ")";
    }
    else if(classe == "EQUIPAMENTO"){
        sql += "nome, num_serie, modelo, disponivel)";
        values += "'" + atributos[0] + "', " + atributos[1] + ", '" + atributos[2] + "', " + atributos[3] + ")";

        // Adicionar registro na tabela de relacionamento de tecnico-equipamento
        sql2 = " INSERT INTO TECNICO_EQUIPAMENTO (id_equipamento, id_tecnico) VALUES ((SELECT MAX(id) FROM EQUIPAMENTO), " + atributos[4] + ")";
    }

    sql += values;

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    if(!sql2.empty()){
        rc = sqlite3_exec(db, sql2.c_str(), 0, 0, &err_msg);
        if(rc != SQLITE_OK ) {
            cerr << "SQL error: " << err_msg << endl;
            sqlite3_free(err_msg);
            sqlite3_close(db);
            exit(1);
        }
    }

    sqlite3_close(db);
    cout << "Objeto criado com sucesso!" << endl;
}


int searchByColumnsCallBack(void* data, int argc, char** argv, char** azColName){
    vector<string>* columns = reinterpret_cast<vector<string>*>(data);
    
    // Iterando sobre todas as colunas e adicionando seus nomes ao vetor de strings
    for(int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "name") == 0) {
            string col_name = argv[i];
            if(!col_name.empty()) {
                col_name[0] = toupper(col_name[0]);
                columns->push_back(argv[i]);
            }
        }
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
// Uma função para atualizar uma linha na tabela
void CRUD::updateObj(string classe, string id, vector<string> atributos, vector<string> valores){

    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    string sql = "UPDATE " + classe + " SET ";
    // cria um loop para iterar sobre os atributos
    for(int i=0; i<atributos.size(); i++){
        if(!atributos[i].empty()){
            sql += atributos[i] + " = '" + valores[i] + "', ";
        }
    }

    // remove a vírgula e o espaço no final da string de atualização
    sql = sql.substr(0, sql.length() - 2);

    sql += " WHERE id = " + id + ";";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg); // executa a query

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
    cout << "Objeto atualizado com sucesso!" << endl;
}

void CRUD::deleteObj(string classe, string id){
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
    cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    exit(1);
    }

    string sql = "DELETE FROM " + classe + " WHERE id = " + id + ";";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg); // executa a query

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
    cout << "Objeto deletado com sucesso!" << endl;
}

vector<string> CRUD::getColumnNames(string table_name){
    vector<string> columns;
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    string sql = "PRAGMA table_info(" + table_name + ");";
    rc = sqlite3_exec(db, sql.c_str(), searchByColumnsCallBack, &columns, &err_msg);
    
    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
    return columns;
}

vector<string> CRUD::readAll(string classe){
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    vector<string> result;
    string sql = "SELECT * FROM " + classe + ";";
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

vector<string> CRUD::getRelation(string classe, string id){
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }
    string relation;
    vector<string> result;

    if(classe == "PROJETO"){
        relation =  "SELECT DISTINCT nome, descricao, duracao FROM PROJETO "
                    "JOIN PROJETO_PESQUISADOR "
                    "ON PROJETO.id = PROJETO_PESQUISADOR.id_projeto "
                    "WHERE PROJETO_PESQUISADOR.id_projeto IN "
                    "(SELECT id_projeto FROM PROJETO_PESQUISADOR WHERE id_pesquisador = " + id + ");";

    } else if(classe == "EQUIPAMENTO"){
        
        relation =  "SELECT DISTINCT nome, num_serie, modelo, disponivel FROM EQUIPAMENTO "
                    "JOIN TECNICO_EQUIPAMENTO "
                    "ON EQUIPAMENTO.id = TECNICO_EQUIPAMENTO.id_equipamento "
                    "WHERE TECNICO_EQUIPAMENTO.id_equipamento IN "
                    "(SELECT id_equipamento FROM TECNICO_EQUIPAMENTO WHERE id_tecnico = " + id + ");";
    }

    rc = sqlite3_exec(db, relation.c_str(), searchByNameCallBack, &result, &err_msg);

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    
    sqlite3_close(db);

    return result;
}

string CRUD::getIdFromName(string classe, string nome){
    rc = sqlite3_open("mydb.db", &db);

    if(rc != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return ""; // retorna uma string vazia em caso de erro
    }

    string result;
    string sql = "SELECT id FROM " + classe + " WHERE nome = '" + nome + "';";
   
    rc = sqlite3_exec(db, sql.c_str(), getIdFromNameCallback, &result, &err_msg);

    if(rc != SQLITE_OK ) {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return ""; // retorna uma string vazia em caso de erro
    }

    sqlite3_close(db);

    return result;
}