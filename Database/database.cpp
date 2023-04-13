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

    const char *func_table = "CREATE TABLE IF NOT EXISTS FUNCIONARIO("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "nome TEXT NOT NULL,"
                             "idade INTEGER NOT NULL,"
                             "cpf TEXT NOT NULL,"
                             "telefone TEXT NOT NULL,"
                             "codigo TEXT NOT NULL,"
                             "cargo TEXT NOT NULL,"
                             "salario REAL NOT NULL);";
                             

    Executar(func_table, db, err_msg, result);

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

    Executar(research_table, db, err_msg, result);

    //Tabela de Projetos

    const char *project_table = "CREATE TABLE IF NOT EXISTS PROJETO("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "titulo TEXT NOT NULL,"
                                "descricao TEXT NOT NULL,"
                                "duracao INTEGER NOT NULL);";
    
    Executar(project_table, db, err_msg, result);

    //Tabela de Relacionamento

    const char *project_researcher = "CREATE TABLE IF NOT EXISTS PROJETO_PESQUISADOR("
                                     "id_projeto INTEGER NOT NULL,"
                                     "id_pesquisador INTEGER NOT NULL,"
                                     "FOREIGN KEY (id_projeto) REFERENCES PROJETO(id),"
                                     "FOREIGN KEY (id_pesquisador) REFERENCES PESQUISADOR(id));";
    
    Executar(project_researcher, db, err_msg, result);

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

    Executar(tech_table, db, err_msg, result);  

    // Tabela de Equipamentos

    const char *equip_table = "CREATE TABLE IF NOT EXISTS EQUIPAMENTO("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "nome TEXT NOT NULL,"
                               "num_serie INTEGER NOT NULL,"
                               "modelo TEXT NOT NULL,"
                               "disponivel BOOL NOT NULL);";
    
    Executar(equip_table, db, err_msg, result);

    // Tabela de Relacionamento

    const char *tech_equip = "CREATE TABLE IF NOT EXISTS TECNICO_EQUIPAMENTO("
                             "id_tecnico INTEGER NOT NULL,"
                             "id_equipamento INTEGER NOT NULL,"
                             "FOREIGN KEY (id_tecnico) REFERENCES TECNICO(id),"
                             "FOREIGN KEY (id_equipamento) REFERENCES EQUIPAMENTO(id));";
    
    Executar(tech_equip, db, err_msg, result);

    const char *cliente_table = "CREATE TABLE IF NOT EXISTS CLIENTE("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "nome TEXT NOT NULL,"
                                "idade INTEGER NOT NULL,"
                                "cpf TEXT NOT NULL,"
                                "telefone TEXT NOT NULL,"
                                "encomenda TEXT NOT NULL,"
                                "data TEXT NOT NULL);";

    Executar(cliente_table, db, err_msg, result);

    cout << "Opened database successfully" << endl;

    CRUD myCrud = CRUD(db);
    vector<string> data = {"Joao", "20", "065335874", "123456789", "000012456", "Faxineiro", "1000.34"};
    myCrud.createObj("FUNCIONARIO", data);
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
    
    sqlite3_close(db);

    cout << "Closed database successfully" << endl;
    
    return 0;
}