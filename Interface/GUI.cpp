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


void search_callback(Fl_Widget* widget, void* data)
{
    // Aqui eu estou pegando os argumentos passados como um struct
    // que vai ter um Fl_Input* e uma string como data

    InputArgs* args = static_cast<InputArgs*>(data);
    // Aqui eu só estraí o input e a classe 

    Fl_Input* search_box = args->input;
    string classe = args->classe;

    vector<string> column_names = crud->getColumnNames(classe);  
    const char* search_term = search_box->value();

    // Fazer algo com o termo de busca 
    // Se o o tamanho do termo de busca for maior que 0
    if(strlen(search_term) > 0){
        vector<string> result = crud->readObj(classe, search_term);  
        
        Fl_Window* wdw = search_box->window();
        
        if(result.size() == 0){
            cout << "Nenhum resultado encontrado" << endl;
            return;
        }

        MyTable *table = new MyTable(20, 60, 560, 300, 11, 7);  
        
            
        table->set_data(result, column_names, false);   
        table->col_width_all(100);
        table->col_width(1, 200);
        

        Pessoa *pessoa = new Pessoa(result[1], stoi(result[2]), result[3], result[4]);
        vector<MyBtn*> methodBtns;

        vector<string> method_names; 

        if(classe=="FUNCIONARIO"){
          pessoa = static_cast<Funcionario*>(pessoa);
          method_names = static_cast<Funcionario*>(pessoa)->getMethods();
        }
        else if(classe=="CLIENTE"){
          pessoa = static_cast<Cliente*>(pessoa);
          method_names = static_cast<Cliente*>(pessoa)->getMethods(); 
        }
        else if(classe=="PESQUISADOR"){
          pessoa = static_cast<Pesquisador*>(pessoa);
          method_names = static_cast<Pesquisador*>(pessoa)->getMethods();
        }

        for(int i = 0; i < method_names.size(); i++){
          //colocar um do lado do outro, mudando apenas x a partir do 30,270
          //mudar apenas o primeiro valor, colocando um do lado do outro
          MyBtn *mthodBtn = new MyBtn(40 + (i*130), 270, 120, 30, method_names[i].c_str());
          cout << method_names[i] << endl;
          methodBtns.push_back(mthodBtn); 

        }

        MyBtn *updateBtn = new MyBtn(320 , 360, 120, 30, "Update");
        MyBtn *deleteBtn = new MyBtn(460, 360, 120, 30, "Delete"); 
        deleteBtn->callback(delete_callback, new DeleteArgs{wdw, classe, result[0]});
        
       
        wdw->add(table);
        wdw->add(updateBtn);
        wdw->add(deleteBtn);
        for(int i = 0; i < methodBtns.size(); i++){
          wdw->add(methodBtns[i]);
        }

        wdw->redraw();
    }
    else {
        cout << "Digite um termo de busca" << endl;
    }
    
}

void create_callback(Fl_Widget* widget, void* data)
{
    cout << "Create callback" << endl;
    CreateArgs* args = static_cast<CreateArgs*>(data);
    MyWindow* wdw = args->wdw;
    string classe = args->classe;
    vector<Fl_Input*> inputs = args->inputs;

    // pegar os valores dos inputs e adicionar no vetor de string, daí passar para o crud create object 

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

  CreateArgs *createArgs = new CreateArgs{};
  createArgs->wdw = create_window;
  createArgs->classe = classe;


  create_window->show();
  last_window = new_window;
  new_window->hide();

  create_window->begin();

  if(classe != "PROJETO" && classe != "EQUIPAMENTO"){
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


    
    if(classe != "CLIENTE"){
      Fl_Input *codigoInput = new Fl_Input(150, 170, 300, 30);
      InputStyle(codigoInput, "Código: ");
      createArgs->inputs.push_back(codigoInput);
      Fl_Input *cargoInput = new Fl_Input(150, 210, 300, 30);
      InputStyle(cargoInput, "Cargo: ");
      createArgs->inputs.push_back(cargoInput);
      Fl_Input *salarioInput = new Fl_Input(150, 250, 300, 30);
      InputStyle(salarioInput, "Salário: ");
      createArgs->inputs.push_back(salarioInput);
      
      if(classe == "PESQUISADOR" || classe == "TECNICO"){
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
    }
  }
  else {
    if(classe=="PROJETO"){
      Fl_Input *nomeInput = new Fl_Input(150, 10, 300, 30);
      InputStyle(nomeInput, "Titulo: ");
      createArgs->inputs.push_back(nomeInput);
      Fl_Input *descricaoInput = new Fl_Input(150, 50, 300, 30);
      InputStyle(descricaoInput, "Descrição: ");
      createArgs->inputs.push_back(descricaoInput); 
      Fl_Input *duracaoInput = new Fl_Input(150, 90, 300, 30);
      InputStyle(duracaoInput, "Duração: ");
      createArgs->inputs.push_back(duracaoInput);
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

    }
  }

  backButton(create_window);
  MyBtn *createBtn = new MyBtn(460, 360, 100, 30, "Criar");
  createBtn->callback(create_callback, createArgs);

  create_window->end();
  create_window->show();
}

// Botões de CRUD que estarão em todas as telas

void crudBtns(void* data, string classe){
  
  MyWindow *new_window = static_cast<MyWindow*>(data);
  // Aqui eu crio um struct que vai ter o ponteiro para a janela e a classe que eu quero
  CallbackArgs *args = new CallbackArgs{new_window, classe};

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
  

  crudBtns(new_window, "FUNCIONARIO");

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
  crudBtns(readOne_window, "PESQUISADOR");


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

  crudBtns(tecnicos_window, "TECNICO");

  tecnicos_window->end();
  tecnicos_window->show();
}

void ClienteCallBack(Fl_Widget *w, void *data) {
  MyWindow* clientes_window = new MyWindow(600, 400, "Clientes");
  clientes_window->show();
  last_window = window;
  window->hide();

  clientes_window->begin();

  addImage("../src/clientes.png");

  crudBtns(clientes_window, "CLIENTE");

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

  crudBtns(equipamento_window, "EQUIPAMENTO");

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
  crudBtns(projeto_window, "PROJETO");

  projeto_window->end();
  projeto_window->show();
}

int main(int argc, char **argv) { 
  // Criar tables se não existirem
  //crud->CreateDB();

  //Criar um objeto para funcionario
  //vector<string> data = {"Maria", "20", "065335874", "123456789", "000012456", "Faxineiro", "1000.34"};
  //crud->createObj("FUNCIONARIO", data);
  
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

  MyBtn *equipamentosBtn = new MyBtn(160, 360, 120, 30, "Equipamentos");
  equipamentosBtn->callback(EquipamentoCallBack, NULL);
  MyBtn *projetosBtn = new MyBtn(310, 360, 120, 30, "Projetos");
  projetosBtn->callback(ProjetoCallBack, NULL);
 

  window->end();
  window->show(argc, argv);


  return Fl::run();

}