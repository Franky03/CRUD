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
    vector<string> result = crud->readObj(classe, search_term);
    Fl_Window* wdw = search_box->window();
    MyTable *table = new MyTable(20, 60, 560, 300, 10, 7); 
   
      
    table->set_data(result, column_names);  
    table->col_width_all(100); 
    wdw->add(table);
    wdw->redraw();
    // Fl_Box* results_box = new Fl_Box(20, 30, 560, 300, "Resultados:");
    // results_box->box(FL_UP_BOX);
    // results_box->align(FL_ALIGN_TOP_LEFT);
    // results_box->labelsize(14);

    // for(int i = 0; i < result.size(); i++){
    //     results_box->copy_label((string(results_box->label()) + "\t" + result[i]).c_str());
    // }

}

void ReadAllCallBack(Fl_Widget*w, void *data){
  MyWindow* readAll_window = new MyWindow(600, 400, "Read All");
  MyWindow *new_window = static_cast<MyWindow*>(data);

  readAll_window->show();
  last_window = new_window;
  new_window->hide();
  

  readAll_window->begin();

  backButton(readAll_window);

  readAll_window->end();
  readAll_window->show();

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
  searchInput->box(FL_BORDER_BOX);
  searchInput->label("Procurar: ");
  searchInput->labelsize(14);
  searchInput->textcolor(FL_BLACK);
  searchInput->textsize(14);

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

  create_window->show();
  last_window = new_window;
  new_window->hide();

  create_window->begin();

  backButton(create_window);

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
  readAll->callback(ReadAllCallBack, new_window);
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

  crudBtns(projeto_window, "PROJETO");

  projeto_window->end();
  projeto_window->show();
}

int main(int argc, char **argv) {
  // Criar tables se não existirem
  //crud->CreateDB();
  
  //Window 

  //Box
  MyBox *viewBox = new MyBox(150, 20, 300, 60, "BioLab");

  //Image
  MyBox *imageBox = new MyBox(180, 70, 250, 250);
  Fl_PNG_Image *image = new Fl_PNG_Image("../src/rafik.png");
  imageBox->image(image);


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
  projetosBtn->callback(TecnicosCallBack, NULL);
 

  window->end();
  window->show(argc, argv);


  return Fl::run();

}