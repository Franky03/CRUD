#include "Fl_All.h"

using namespace std;

// Janela principal
MyWindow *window = new MyWindow(600,400, "BioLab");
MyWindow *last_window = nullptr;


// Banco de dados e CRUD
sqlite3 *db;
CRUD *crud = new CRUD(db);

// Structs para passar argumentos para o callback
struct CallbackArgs {
  MyWindow* window;
  string classe;
  bool create;
  bool from_ro;
  string id;
};
struct InputArgs {
  MyWindow* wdw;
  Fl_Input* input;
  string classe;
};

struct CreateArgs {
  MyWindow* wdw;
  string classe;
  vector<Fl_Input*> inputs;
  string id;
};

struct PersonArgs {
  MyWindow* wdw;
  string classe;
  Pessoa *pessoa;
};

struct DeleteArgs {
  Fl_Window* wdw;
  string classe;
  string id;
};

void CreateCallBack(Fl_Widget *w, void *data);

void addImage(const char* file){
  MyBox *imageBox = new MyBox(180, 70, 250, 250);
  Fl_PNG_Image *image = new Fl_PNG_Image(file);
  imageBox->image(image);
}

// Funções de callback

void backCallBack(Fl_Widget *w, void *data) {
  last_window->show();
  Fl_Window *new_window = static_cast<Fl_Window*>(data);
  new_window->hide();
}

void backStartCallBack(Fl_Widget *w, void *data) {
  window->show();
  Fl_Window *new_window = static_cast<Fl_Window*>(data);
  new_window->hide();
}

void delete_callback(Fl_Widget* widget, void* data) {
  DeleteArgs* args = static_cast<DeleteArgs*>(data);
  Fl_Window* wdw = args->wdw;
  string classe = args->classe;
  string id = args->id;

  crud->deleteObj(classe, id);
  wdw->hide();
  window->show();
}

void backButton(void *data){
  MyWindow *new_window = static_cast<MyWindow*>(data);

  MyBtn *backBtn = new MyBtn(10, 360, 120, 30, "Back");
  backBtn->callback(backCallBack, new_window);
}

// verificar quall classe é e transformar no objeto da classe, depois fazer o cout
void out_callback(Fl_Widget* widget, void*data){
  string* str_ptr = reinterpret_cast<string*>(data);
  string str_value = *str_ptr;
  cout << str_value << endl;
}

void set_callback(Fl_Widget* widget, void*data){

}

void get_any_callback(Fl_Widget* widget, void*data){
  CallbackArgs* args = static_cast<CallbackArgs*>(data);
  string classe = args->classe;
  string id = args->id;

  vector<string> relations = crud->getRelation(classe, id);
  if(relations.size() == 0) {
    cout << "Nenhuma relação encontrada" << endl;
    return;
  }
  for(int i = 0; i < relations.size(); i++) {
    cout << relations[i] << endl;
  }
}

void remove_any_callback(Fl_Widget* widget, void*data){
  cout << "Nome para remover: ";
  string nome;
  getline(cin, nome);
  cout << nome << " foi removido" << endl;
}

void search_callback(Fl_Widget* widget, void* data)
{
  // Aqui eu estou pegando os argumentos passados como um struct
  // que vai ter um Fl_Input* e uma string como data

  InputArgs* args = static_cast<InputArgs*>(data);
  // Aqui eu só estraí o input e a classe  

  Fl_Input* search_box = args->input;
  string classe = args->classe;

  vector<string> column_names = crud->getColumnNames(classe);  
  string search_term = search_box->value();
  
  // Fazer algo com o termo de busca 
  // Se o o tamanho do termo de busca for maior que 0
  if(search_term.size() > 0){
      
      vector<string> result = crud->readObj(classe, search_term);  
      vector<MyBtn*> methodBtns;

      // apagar o resultado do número de colunas até o final do vetor result
      if(result.size()>column_names.size()){
        result.erase(result.begin()+column_names.size(), result.end());
      }
      
      Fl_Window* wdw = search_box->window();
      
      MyTable *table = new MyTable(20, 60, 560, 300);
      if(result.size() == 0){
          cout << "Nenhum resultado encontrado" << endl; 
          
          wdw->remove(table);
          table = new MyTable(20, 60, 560, 300, 11, 7); 
          table->set_data(result, column_names, false);
          wdw->add(table);
          
          wdw->redraw();

          return;
      }


      table->set_data(result, column_names, false);   
      table->col_width_all(100);
      table->col_width(1, 200);
      if(classe==PROJETO){
        table->col_width(2,300);
      }
      
      vector<string> method_names; 

      if(classe==FUNCIONARIO){
        Funcionario *funcionario = new Funcionario(result[1], stoi(result[2]), result[3], result[4], result[5], result[6], stof(result[7]));
        method_names = funcionario->getMethods();
        
        MyBtn *salarioAnual = new MyBtn(40, 270, 120, 30, method_names[0].c_str());
        
        wdw->add(salarioAnual);
        MyBtn *trabalharBtn = new MyBtn(170, 270, 120, 30, method_names[1].c_str());
        
        wdw->add(trabalharBtn);
        MyBtn *descansarBtn = new MyBtn(300, 270, 120, 30, method_names[2].c_str());
        
        wdw->add(descansarBtn);
        MyBtn *isTrabalhando =  new MyBtn(430, 270, 120, 30, method_names[3].c_str());
  
        string *working = new string("Funcionário Trabalhando ?: " + funcionario->isTrabalhando()); 
        isTrabalhando->callback(out_callback, working);
        
        wdw->add(isTrabalhando);
        MyBtn *aumentarSalario = new MyBtn(40, 310, 120, 30, method_names[4].c_str());
        
        wdw->add(aumentarSalario);
        

      }
      else if(classe==CLIENTE){
        // "Reclamar", "Elogiar", "Esperar" 
        Cliente *cliente = new Cliente(result[1], stoi(result[2]), result[3], result[4], result[5], result[6], stof(result[7]));
        method_names = cliente->getMethods();
        MyBtn *reclamarBtn = new MyBtn(40, 270, 120, 30, method_names[0].c_str());
        wdw->add(reclamarBtn);
        MyBtn *elogiarBtn = new MyBtn(170, 270, 120, 30, method_names[1].c_str());
        wdw->add(elogiarBtn);
        MyBtn *esperarBtn = new MyBtn(300, 270, 120, 30, method_names[2].c_str());
        wdw->add(esperarBtn);
        
      }
      else if(classe==PESQUISADOR){
  
        Pesquisador *pesquisador = new Pesquisador(result[1], stoi(result[2]), result[3], result[4], result[5], result[6], stof(result[7]), result[8]);
        
        method_names = pesquisador->getMethods();
        MyBtn *areaBtn = new MyBtn(40, 270, 120, 30, method_names[0].c_str());

        string *area = new string("Área: " + pesquisador->getArea());
        
        areaBtn->callback(out_callback, area);
        wdw->add(areaBtn);
        MyBtn *projetosBtn = new MyBtn(170, 270, 120, 30, method_names[1].c_str());
        // resul[0]-> id do pesquisador 
        CallbackArgs *args = new CallbackArgs{static_cast<MyWindow*>(wdw), PROJETO, false, false,result[0]};
        projetosBtn->callback(get_any_callback, args);
        wdw->add(projetosBtn);
        MyBtn *adicionarProjetoBtn = new MyBtn(300, 270, 120, 30, method_names[2].c_str());
        adicionarProjetoBtn->callback(CreateCallBack, new CallbackArgs{static_cast<MyWindow*>(wdw), PROJETO, true, true,result[0]});
        wdw->add(adicionarProjetoBtn);
        MyBtn *removerProjetoBtn = new MyBtn(430, 270, 120, 30, method_names[3].c_str());
        removerProjetoBtn->callback(remove_any_callback, NULL);
        wdw->add(removerProjetoBtn);
        

      }

      else if(classe==TECNICO){
        Tecnico *tecnico = new Tecnico(result[1], stoi(result[2]), result[3], result[4], result[5], result[6], stof(result[7]), result[8]);
        method_names = tecnico->getMethods();
        //"Area", "Equipamentos", "AddEquipamento", "RemoveEquipamento"
        MyBtn *areaBtn = new MyBtn(40, 270, 120, 30, method_names[0].c_str());
        string *area = new string("Área: " + tecnico->getArea());
        areaBtn->callback(out_callback, area);
        MyBtn *equipamentosBtn = new MyBtn(170, 270, 120, 30, method_names[1].c_str());
        CallbackArgs *args = new CallbackArgs{static_cast<MyWindow*>(wdw), EQUIPAMENTO, false, false, result[0]};
        equipamentosBtn->callback(get_any_callback, args);
        wdw->add(equipamentosBtn);
        MyBtn *addEquipamentoBtn = new MyBtn(300, 270, 120, 30, method_names[2].c_str());
        addEquipamentoBtn->callback(CreateCallBack, new CallbackArgs{static_cast<MyWindow*>(wdw), EQUIPAMENTO, true, true,result[0]});
        wdw->add(addEquipamentoBtn);

        MyBtn *removeEquipamentoBtn = new MyBtn(430, 270, 120, 30, method_names[3].c_str());
        removeEquipamentoBtn->callback(remove_any_callback, NULL);
        wdw->add(removeEquipamentoBtn);
        
        wdw->add(areaBtn);

      }


      MyBtn *updateBtn = new MyBtn(320 , 360, 120, 30, "Update");
      updateBtn->callback(CreateCallBack, new CallbackArgs{static_cast<MyWindow*>(wdw), classe, false, false,result[0]});
      MyBtn *deleteBtn = new MyBtn(460, 360, 120, 30, "Delete"); 
      deleteBtn->callback(delete_callback, new DeleteArgs{wdw, classe, result[0]});
      
      
      wdw->add(table);
      wdw->add(updateBtn);
      wdw->add(deleteBtn);

      wdw->redraw();
  }
  else
      cout << "Digite um termo de busca" << endl;
  
}

void create_callback(Fl_Widget* widget, void* data)
{
  cout << "Create callback" << endl;
  CreateArgs* args = static_cast<CreateArgs*>(data);
  MyWindow* wdw = args->wdw;
  string classe = args->classe;  
  vector<Fl_Input*> inputs = args->inputs;

  // pegar os valores dos inputs e adicionar no vetor de string, daí passar para o crud create object
  vector<string> values;
  for(int i=0; i<inputs.size(); i++)
  {
    string val = inputs[i]->value();
    values.push_back(val);
  }

  crud->createObj(classe, values);
}

void cancel_callback(Fl_Widget* widget, void* data)
{
  MyWindow* wdw = static_cast<MyWindow*>(data);
  wdw->hide();
  window->show();
}

void update_callback(Fl_Widget* widget, void* data)
{

  CreateArgs* args = static_cast<CreateArgs*>(data);
  MyWindow* wdw = args->wdw;
  string classe = args->classe;
  vector<Fl_Input*> inputs = args->inputs;

  string id = args->id;
  
  vector<string> values;
  vector<string> column_names = crud->getColumnNames(classe);
  // tirei o primeiro elemento da lista, pois é o id
  column_names.erase(column_names.begin());

  for(int i = 0; i < inputs.size(); i++)
  {
    string val = inputs[i]->value();
    if(strlen(val.c_str()) != 0)
      values.push_back(val);
    else
      values.push_back("NULL");
  }
  //Uma solução seria percorrer os vetores de trás para frente e remover os elementos "NULL". 
  //Dessa forma, você não terá problemas de índice, pois os elementos que já foram verificados não mudarão de posição.
  for(int i = values.size() - 1; i >= 0; i--)
  {
    if(values[i] == "NULL"){
      values.erase(values.begin() + i);
      column_names.erase(column_names.begin() + i);
    }
  }
  
  crud->updateObj(classe,id,column_names, values);
  
  wdw->hide();
  window->show();
}

void ReadAllCallBack(Fl_Widget*w, void *data){
  MyWindow* readAll_window = new MyWindow(600, 400, "Read All");
  CallbackArgs* args = static_cast<CallbackArgs*>(data);
  MyWindow *new_window = args->window;
  string classe = args->classe;

  readAll_window->show();
  last_window = new_window;
  new_window->hide();
  

  readAll_window->begin(); 

  vector<string> column_names = crud->getColumnNames(classe);
  vector<string> result = crud->readAll(classe);

  MyTable *table = new MyTable(20, 60, 560, 300, 11, 7);
  table->set_data(result, column_names);
  table->col_width_all(100);
  table->col_width(1, 200); 
   
  readAll_window->add(table); 
  readAll_window->redraw();
  

  backButton(readAll_window);

  readAll_window->end();
  readAll_window->show();

}

void InputStyle(Fl_Input *input, const char * label){
  input->box(FL_BORDER_BOX);
  input->label(label);
  input->labelsize(14);
  input->textcolor(FL_BLACK);
  input->textsize(14);
}

void ReadOneCallBack(Fl_Widget*w, void *data){
  MyWindow* readOne_window = new MyWindow(600, 400, "Read One");

  CallbackArgs* args = static_cast<CallbackArgs*>(data);
  MyWindow *new_window = args->window;
  string classe = args->classe;

  readOne_window->show();
  last_window = new_window;
  new_window->hide();

  readOne_window->begin();

  Fl_Input * searchInput = new Fl_Input(150, 10, 300, 30);
  InputStyle(searchInput, "Procurar: ");

  Fl_Button * searchButton = new Fl_Button(460, 10, 100, 30, "Procurar");
  InputArgs *inputArgs = new InputArgs{readOne_window, searchInput ,classe};
  searchButton->callback(search_callback, inputArgs);

  backButton(readOne_window);

  readOne_window->end();
  readOne_window->show();
}

void CreateCallBack(Fl_Widget*w, void *data){
  MyWindow* create_window = new MyWindow(600, 400, "Create");
  CallbackArgs *args = static_cast<CallbackArgs*>(data);
  MyWindow *new_window = args->window;
  string classe = args->classe;
  bool create = args->create;
  string id = args->id;
  bool from_ro = args->from_ro;

  CreateArgs *createArgs = new CreateArgs{};
  createArgs->wdw = create_window;
  createArgs->classe = classe;


  create_window->show();
  last_window = new_window;
  new_window->hide();

  create_window->begin();

  if(classe != PROJETO && classe != EQUIPAMENTO){
    Fl_Input *nomeInput = new Fl_Input(150, 10, 300, 30);
    InputStyle(nomeInput, "Nome: ");
    createArgs->inputs.push_back(nomeInput);
    Fl_Input *idadeInput = new Fl_Input(150, 50, 300, 30);
    InputStyle(idadeInput, "Idade: ");
    createArgs->inputs.push_back(idadeInput);
    Fl_Input *cpfInput = new Fl_Input(150, 90, 300, 30);
    InputStyle(cpfInput, "CPF: ");
    createArgs->inputs.push_back(cpfInput);
    Fl_Input* telefoneInput = new Fl_Input(150, 130, 300, 30);
    InputStyle(telefoneInput, "Telefone: ");
    createArgs->inputs.push_back(telefoneInput);


    
    if(classe != CLIENTE){
      Fl_Input *codigoInput = new Fl_Input(150, 170, 300, 30);
      InputStyle(codigoInput, "Código: ");
      createArgs->inputs.push_back(codigoInput);
      Fl_Input *cargoInput = new Fl_Input(150, 210, 300, 30);
      InputStyle(cargoInput, "Cargo: ");
      createArgs->inputs.push_back(cargoInput);
      Fl_Input *salarioInput = new Fl_Input(150, 250, 300, 30);
      InputStyle(salarioInput, "Salário: ");
      createArgs->inputs.push_back(salarioInput);
      
      if(classe == PESQUISADOR || classe == TECNICO){
        Fl_Input *areaInput = new Fl_Input(150, 290, 300, 30);
        InputStyle(areaInput, "Área: ");
        createArgs->inputs.push_back(areaInput);
      }

    }
    else{
      Fl_Input *encomendaInput = new Fl_Input(150, 170, 300, 30);
      InputStyle(encomendaInput, "Encomenda: ");
      createArgs->inputs.push_back(encomendaInput);
      Fl_Input *dataInput = new Fl_Input(150, 210, 300, 30);
      InputStyle(dataInput, "Data: ");
      createArgs->inputs.push_back(dataInput);
      Fl_Input *aPagarInput = new Fl_Input(150, 250, 300, 30);
      InputStyle(aPagarInput, "A pagar: ");
      createArgs->inputs.push_back(aPagarInput);
    }
  }
  else {
    if(classe==PROJETO){
      Fl_Input *nomeInput = new Fl_Input(150, 10, 300, 30);
      InputStyle(nomeInput, "Titulo: ");
      createArgs->inputs.push_back(nomeInput);
      Fl_Input *descricaoInput = new Fl_Input(150, 50, 300, 30);
      InputStyle(descricaoInput, "Descrição: ");
      createArgs->inputs.push_back(descricaoInput); 
      Fl_Input *duracaoInput = new Fl_Input(150, 90, 300, 30);
      InputStyle(duracaoInput, "Duração: ");
      createArgs->inputs.push_back(duracaoInput);
      Fl_Input *pesquisadorResp = new Fl_Input(150, 130, 300, 30);
      if(from_ro){
        pesquisadorResp->value(id.c_str());
        pesquisadorResp->deactivate();
      }
      InputStyle(pesquisadorResp, "Pesquisador: ");
      createArgs->inputs.push_back(pesquisadorResp);
      
    }
    else{
      Fl_Input *nomeInput = new Fl_Input(150, 10, 300, 30);
      InputStyle(nomeInput, "Nome: ");
      createArgs->inputs.push_back(nomeInput);
      Fl_Input *numSerieInput = new Fl_Input(150, 50, 300, 30);
      InputStyle(numSerieInput, "Número de Série: ");
      createArgs->inputs.push_back(numSerieInput);
      Fl_Input *modelo = new Fl_Input(150, 90, 300, 30);  
      InputStyle(modelo, "Modelo: ");
      createArgs->inputs.push_back(modelo);
      Fl_Input *disponivelInput = new Fl_Input(150, 130, 300, 30);
      InputStyle(disponivelInput, "Disponível: ");
      createArgs->inputs.push_back(disponivelInput);
      Fl_Input *tecnicoResp = new Fl_Input(150, 170, 300, 30);
      if(from_ro){
        tecnicoResp->value(id.c_str());
        tecnicoResp->deactivate();
      }
      InputStyle(tecnicoResp, "Técnico(ID): ");
      createArgs->inputs.push_back(tecnicoResp);

    }
  }

  if(create){
    if(!from_ro){
      backButton(create_window);
    } else {
      MyBtn *cancelBtn = new MyBtn(10, 360, 100, 30, "Cancelar");
      cancelBtn->callback(cancel_callback, create_window);
    }
    
    MyBtn *createBtn = new MyBtn(460, 360, 100, 30, "Criar");
    createBtn->callback(create_callback, createArgs);
  }
  else{
    MyBtn *cancelBtn = new MyBtn(10, 360, 100, 30, "Cancelar");
    // criar uma função dentro da chamada do callback para esconder essa janela e abrir a window
    cancelBtn->callback(cancel_callback, create_window);
    MyBtn *updateBtn = new MyBtn(460, 360, 100, 30, "Atualizar");
    createArgs->id = id;
    updateBtn->callback(update_callback, createArgs);
  }
  

  create_window->end();
  create_window->show();
}

// Botões de CRUD que estarão em todas as telas

void crudBtns(void* data, string classe){
  
  MyWindow *new_window = static_cast<MyWindow*>(data);
  // Aqui eu crio um struct que vai ter o ponteiro para a janela e a classe que eu quero
  CallbackArgs *args = new CallbackArgs{new_window, classe, true};

  MyBtn *backBtn = new MyBtn(10, 360, 120, 30, "Back");
  backBtn->callback(backStartCallBack, new_window);

  MyBtn *readAll = new MyBtn(160, 360, 120, 30, "Read All");
  readAll->callback(ReadAllCallBack, args);
  MyBtn *ReadOne = new MyBtn(310, 360, 120, 30, "Read One");
  ReadOne->callback(ReadOneCallBack, args);
  MyBtn *createButton = new MyBtn(470, 360, 120, 30, "Create");
  createButton->callback(CreateCallBack, args);   
}

// Funções de callback para as janelas de cada classe

void FuncionariosCallBack(Fl_Widget *w, void *data) {

  MyWindow* new_window = new MyWindow(600, 400, "Funcionários");
  new_window->show();
  last_window = window;
  window->hide();

  new_window->begin();

  addImage("../src/funcionario.png");
  

  crudBtns(new_window, FUNCIONARIO); 

  new_window->end();
  new_window->show(); 

}

void PesquisadoresCallBack(Fl_Widget *w, void *data) {
  MyWindow* readOne_window = new MyWindow(600, 400, "Pesquisadores");
  readOne_window->show();
  last_window = window;
  window->hide();

  readOne_window->begin();

  
  addImage("../src/pesquisador.png");
  crudBtns(readOne_window, PESQUISADOR);


  readOne_window->end();
  readOne_window->show();
}

void TecnicosCallBack(Fl_Widget *w, void *data) {
  MyWindow* tecnicos_window = new MyWindow(600, 400, "Tecnicos");
  tecnicos_window->show();
  last_window = window;
  window->hide();

  tecnicos_window->begin();

  addImage("../src/tecnicos.png");

  crudBtns(tecnicos_window, TECNICO);

  tecnicos_window->end();
  tecnicos_window->show();
}

void ClienteCallBack(Fl_Widget *w, void *data){
  MyWindow* clientes_window = new MyWindow(600, 400, "Clientes");
  clientes_window->show();
  last_window = window;
  window->hide();

  clientes_window->begin();

  addImage("../src/clientes.png");

  crudBtns(clientes_window, CLIENTE);

  clientes_window->end();
  clientes_window->show();
}

void EquipamentoCallBack(Fl_Widget *w, void *data){
  MyWindow* equipamento_window = new MyWindow(600, 400, "Equipamentos");
  equipamento_window->show();
  last_window = window;
  window->hide();

  equipamento_window->begin();

  addImage("../src/equipamentos.png");

  crudBtns(equipamento_window, EQUIPAMENTO);

  equipamento_window->end();
  equipamento_window->show();
}

void ProjetoCallBack(Fl_Widget *w, void *data){
  MyWindow* projeto_window = new MyWindow(600, 400, "Projetos");
  projeto_window->show();
  last_window = window;
  window->hide();

  projeto_window->begin();


  addImage("../src/projetos.png");
  crudBtns(projeto_window, PROJETO);

  projeto_window->end();
  projeto_window->show();
}


void RelatorioCallBack(Fl_Widget *w, void *data){ 
  // criar um arquivo para colocar o relatório nele
  ofstream relatorio(RELATORIO_TXT);  
  float despesas = 0;

  if(!relatorio.is_open()){
    cout << "Não foi possível abrir o arquivo" << endl;
    return;
  }

  relatorio << "Relatório do Laboratório" << endl;
  relatorio << "------------------------" << endl;

  // cria um objeto template para cada classe

  Relatorio<Funcionario> templateFuncionario = Relatorio<Funcionario>();
  Relatorio<Pesquisador> templatePesquisador = Relatorio<Pesquisador>();
  Relatorio<Tecnico> templateTecnico = Relatorio<Tecnico>();
  Relatorio<Cliente> templateCliente = Relatorio<Cliente>();

  vector<Funcionario> funcionarios;
  vector<Pesquisador> pesquisadores;
  vector<Tecnico> tecnicos;
  vector<Cliente> clientes;
  vector<Equipamento> equipamentos;
  vector<Projeto> projetos;

  vector<string> result;
  
  result = crud->readAll(FUNCIONARIO);

  // ele começa no 1, vai até o 8, daí ele começa no 9 e assim por diante
  for(int i = 1; i < result.size(); i+=8){
    Funcionario funcionario = Funcionario(result[i], stoi(result[i+1]), result[i+2], result[i+3], result[i+4], result[i+5], stof(result[i+6]));
    funcionarios.push_back(funcionario);
  }

  templateFuncionario.toFile(funcionarios, relatorio, FUNCIONARIO, &despesas);

  result = crud->readAll(PESQUISADOR);  

  for(int i = 1; i < result.size(); i+=9){
      Pesquisador pesquisador = Pesquisador(result[i], stoi(result[i+1]), result[i+2], result[i+3], result[i+4], result[i+5], stof(result[i+6]), result[i+7]);
      pesquisadores.push_back(pesquisador);
  }
  
  templatePesquisador.toFile(pesquisadores, relatorio, PESQUISADOR, &despesas); 
  

  result = crud->readAll(TECNICO);  

  for(int i = 1; i < result.size(); i+=9){
    Tecnico tecnico = Tecnico(result[i], stoi(result[i+1]), result[i+2], result[i+3], result[i+4], result[i+5], stof(result[i+6]), result[i+7]);
    tecnicos.push_back(tecnico);
  }

  templateTecnico.toFile(tecnicos, relatorio, TECNICO, &despesas);

  result = crud->readAll(CLIENTE);
  
  for(int i = 1; i < result.size(); i+=7){
    Cliente cliente = Cliente(result[i], stoi(result[i+1]), result[i+2], result[i+3], result[i+4], result[i+5], stof(result[i+6]));
    clientes.push_back(cliente);
  }
  
  relatorio << CLIENTE << endl;
  relatorio << "------------------------" << endl;
  relatorio << "Total: " << clientes.size() << endl;
  int clienteFeliz=0;
  float totalGanho = 0;
  for(int i = 0; i < clientes.size(); i++){
    if(clientes[i].getSatisfacao()){
      clienteFeliz++;
    }
    totalGanho += clientes[i].getDevendo();
  }
  relatorio << "Clientes satisfeitos: " << clienteFeliz << endl;
  relatorio << "Clientes insatisfeitos: " << clientes.size() - clienteFeliz << endl;
  relatorio << "Total ganho: R$ " << totalGanho << endl;
  relatorio << "------------------------" << endl;

  result = crud->readAll(PROJETO);
  relatorio << PROJETO << endl;
  relatorio << "------------------------" << endl;

  for(int i = 1; i < result.size(); i+=4){
    Projeto projeto = Projeto(result[i], result[i+1], stoi(result[i+2]));
    projetos.push_back(projeto);
  }

  relatorio << "Total: " << projetos.size() << endl;
  relatorio << "------------------------" << endl;

  result = crud->readAll(EQUIPAMENTO);

  for(int i = 1; i < result.size(); i+=5){
    Equipamento equipamento = Equipamento(result[i], stoi(result[i+1]), result[i+2], stoi(result[i+3]));
    equipamentos.push_back(equipamento);
  }

  relatorio << EQUIPAMENTO << endl;
  relatorio << "------------------------" << endl;
  relatorio << "Total: " << equipamentos.size() << endl;
  int disponiveis = 0;
  for(int i = 0; i < equipamentos.size(); i++){
    if(equipamentos[i].getDisponivel()){
      disponiveis++;
    }
  }
  relatorio << "Equipamentos disponíveis: " << disponiveis << endl;
  relatorio << "------------------------" << endl;

  relatorio << "Despesas totais: R$ " << despesas << endl;
  relatorio << "Lucro do laboratório: R$ " << totalGanho - despesas << endl;

  relatorio.close();

  cout << "Relatório gerado com sucesso!" << endl;
}


int main(int argc, char **argv) { 
  // Criar tables se não existirem
  //crud->CreateDB(); 

  //Window

  //Box
  MyBox *viewBox = new MyBox(150, 20, 300, 60, "BioLab");

  //Image
  addImage("../src/rafik.png"); 

  MyBtn *readButton = new MyBtn(10, 300, 120, 30, "Funcionários");
  readButton->callback(FuncionariosCallBack, NULL);
  MyBtn *readOneButton = new MyBtn(160, 300, 120, 30, "Pesquisadores");
  readOneButton->callback(PesquisadoresCallBack, NULL);
  MyBtn *updateButton = new MyBtn(310, 300, 120, 30, "Técnicos");
  updateButton->callback(TecnicosCallBack, NULL);
  MyBtn *createButton = new MyBtn(470, 300, 120, 30, "Clientes");
  createButton->callback(ClienteCallBack, NULL);

  MyBtn *equipamentosBtn = new MyBtn(90, 350, 120, 30, "Equipamentos");
  equipamentosBtn->callback(EquipamentoCallBack, NULL);
  MyBtn *projetosBtn = new MyBtn(240, 350, 120, 30, "Projetos");
  projetosBtn->callback(ProjetoCallBack, NULL);
 
  MyBtn *relatorioBtn = new MyBtn(390, 350, 120, 30, "Relatório"); 
  relatorioBtn->callback(RelatorioCallBack, NULL); 

  window->end();
  window->show(argc, argv);


  return Fl::run();
 
}