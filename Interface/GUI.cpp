#include "Fl_All.h"

using namespace std;

MyWindow *window = new MyWindow(600,400, "BioLab");


void backCallBack(Fl_Widget *w, void *data) {
  window->show();
  Fl_Window *new_window = static_cast<Fl_Window*>(data);
  new_window->hide();
}

void search_callback(Fl_Widget* widget, void* data)
{
    Fl_Input* search_box = (Fl_Input*) data;
    const char* search_term = search_box->value();

    //MyBox *result_box = new MyBox(100, 100, 300, 30, search_term);
  
    // Fazer algo com o termo de busca
    cout << "Termo de busca: " << search_term << endl;
}

void ReadAllCallBack(Fl_Widget*w, void *data){
  MyWindow* readAll_window = new MyWindow(600, 400, "Read All");
  MyWindow *new_window = static_cast<MyWindow*>(data);

  readAll_window->show();
  new_window->hide();
  

  readAll_window->begin();

  readAll_window->end();
  readAll_window->show();

}

void ReadOneCallBack(Fl_Widget*w, void *data){
  MyWindow* readOne_window = new MyWindow(600, 400, "Read One");
  MyWindow *new_window = static_cast<MyWindow*>(data);

  readOne_window->show();
  new_window->hide();

  readOne_window->begin();

  Fl_Input * searchInput = new Fl_Input(150, 10, 300, 30);
  searchInput->box(FL_BORDER_BOX);
  searchInput->label("Procurar: ");
  searchInput->labelsize(14);
  searchInput->textcolor(FL_BLACK);
  searchInput->textsize(14);

  Fl_Button * searchButton = new Fl_Button(460, 10, 100, 30, "Procurar");
  searchButton->callback(search_callback, searchInput);

  readOne_window->end();
  readOne_window->show();
}

void CreateCallBack(Fl_Widget*w, void *data){
  MyWindow* create_window = new MyWindow(600, 400, "Create");
  create_window->show();
  window->hide();

  create_window->begin();

  create_window->end();
  create_window->show();
}

void crudBtns(void* data){
  MyWindow *new_window = static_cast<MyWindow*>(data);

  MyBtn *backBtn = new MyBtn(10, 360, 120, 30, "Back");
  backBtn->callback(backCallBack, new_window);

  MyBtn *readOneButton = new MyBtn(160, 360, 120, 30, "Read All");
  readOneButton->callback(ReadAllCallBack, new_window);
  MyBtn *updateButton = new MyBtn(310, 360, 120, 30, "Read One");
  updateButton->callback(ReadOneCallBack, new_window);
  MyBtn *createButton = new MyBtn(470, 360, 120, 30, "Create");
  createButton->callback(CreateCallBack, NULL);   
}

void FuncionariosCallBack(Fl_Widget *w, void *data) {

  MyWindow* new_window = new MyWindow(600, 400, "Funcionários");
  new_window->show();
  window->hide();

  new_window->begin();

  crudBtns(new_window);

  new_window->end();
  new_window->show(); 

}

void PesquisadoresCallBack(Fl_Widget *w, void *data) {
  MyWindow* readOne_window = new MyWindow(600, 400, "Pesquisadores");
  readOne_window->show();
  window->hide();

  readOne_window->begin();

  

  crudBtns(readOne_window);


  readOne_window->end();
  readOne_window->show();
}

void TecnicosCallBack(Fl_Widget *w, void *data) {
  cout << "Update button pressed" << endl;
}

void ClienteCallBack(Fl_Widget *w, void *data) {
  cout << "Create button pressed" << endl;
}

void mouseMoveCallback(void* data)
{
    Fl_Window* window = (Fl_Window*)data;
    int mouseX = Fl::event_x();
    int mouseY = Fl::event_y();
    int windowX = window->x();
    int windowY = window->y();
    cout << "Coordenadas do mouse na janela: (" << mouseX - windowX << ", " << mouseY - windowY << ")" << endl;
    Fl::repeat_timeout(0.1, mouseMoveCallback, data);
}



int main(int argc, char **argv) {
  //Window

  //Box
  MyBox *viewBox = new MyBox(150, 20, 300, 60, "BioLab");

  MyBtn *amostrasBtn = new MyBtn(10, 300, 120, 30, "Amostras");
  amostrasBtn->callback(FuncionariosCallBack, NULL);
  MyBtn *equipamentosBtn = new MyBtn(160, 300, 120, 30, "Equipamentos");
  equipamentosBtn->callback(PesquisadoresCallBack, NULL);
  MyBtn *projetosBtn = new MyBtn(310, 300, 120, 30, "Projetos");
  projetosBtn->callback(TecnicosCallBack, NULL);
  MyBtn *relatoriosBtn = new MyBtn(470, 300, 120, 30, "Relatórios");
  relatoriosBtn->callback(ClienteCallBack, NULL);
  

  MyBtn *readButton = new MyBtn(10, 360, 120, 30, "Funcionários");
  readButton->callback(FuncionariosCallBack, NULL);
  MyBtn *readOneButton = new MyBtn(160, 360, 120, 30, "Pesquisadores");
  readOneButton->callback(PesquisadoresCallBack, NULL);
  MyBtn *updateButton = new MyBtn(310, 360, 120, 30, "Técnicos");
  updateButton->callback(TecnicosCallBack, NULL);
  MyBtn *createButton = new MyBtn(470, 360, 120, 30, "Clientes");
  createButton->callback(ClienteCallBack, NULL);

  window->end();
  window->show(argc, argv);


  return Fl::run();

}