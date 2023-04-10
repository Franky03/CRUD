#include <iostream>
#include <string>
#include <sstream>

#include "Fl_All.h"

#include "MyBtn.h"
#include "MyWindow.h"
#include "MyBox.h"
#include "MyTable.h"


using namespace std;

MyWindow *window = new MyWindow(600,400, "Dados Proteicos");


void backCallBack(Fl_Widget *w, void *data) {
  window->show();
  Fl_Window *new_window = static_cast<Fl_Window*>(data);
  new_window->hide();
}

void search_callback(Fl_Widget* widget, void* data)
{
    Fl_Input* search_box = (Fl_Input*) data;
    const char* search_term = search_box->value();

    MyBox *result_box = new MyBox(100, 100, 300, 30, search_term);
    //Fl_Window *new_window = static_cast<Fl_Window*>(data[1]);
    //new_window->add(result_box);
  
    // Fazer algo com o termo de busca
    cout << "Termo de busca: " << search_term << endl;
}

void readCallBack(Fl_Widget *w, void *data) {
  int x_offset = 10;
  int y_offset = 50;
  int box_width = 290;
  int box_height = 30;
  int table_rows = 10;


  MyWindow* new_window = new MyWindow(600, 400, "Read All");
  new_window->show();
  window->hide();

  new_window->begin();
  
  MyBox *newBox = new MyBox(8, 0, 300, 60, "Proteínas", 24);
  MyBox *newBox2 = new MyBox(298, 0, 300, 60, "Aminoácidos", 24);

  for (int i = 0; i < table_rows; i++) {
    // Caixa da coluna 1

    MyBox *box1 = new MyBox(x_offset, y_offset, box_width, box_height, "Proteina" , 12);
    box1->box(FL_UP_BOX);
    box1->color(FL_WHITE);
    box1->labelsize(14);
    box1->labelcolor(FL_BLACK);
    box1->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    // Caixa da coluna 2
    MyBox *box2 = new MyBox(x_offset + box_width, y_offset, box_width, box_height, "Aminoacido", 12);
    box2->box(FL_UP_BOX);
    box2->color(FL_WHITE);
    box2->labelsize(14);
    box2->labelcolor(FL_BLACK);
    box2->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    y_offset += box_height;
}

  MyBtn *backBtn = new MyBtn(5, 360, 120, 30, "Voltar");
  backBtn->callback(backCallBack, new_window);
  
  new_window->end();
  new_window->show(); 

}

void readOneCallBack(Fl_Widget *w, void *data) {
  MyWindow* readOne_window = new MyWindow(600, 400, "Read One");
  readOne_window->show();
  window->hide();

  readOne_window->begin();

  Fl_Input * searchInput = new Fl_Input(150, 10, 300, 30);
  searchInput->box(FL_BORDER_BOX);
  searchInput->label("Procurar: ");
  searchInput->labelsize(14);
  searchInput->textcolor(FL_BLACK);
  searchInput->textsize(14);

  Fl_Button * searchButton = new Fl_Button(460, 10, 100, 30, "Procurar");
  searchButton->callback(search_callback, searchInput);

  MyBtn *backBtn = new MyBtn(5, 360, 120, 30, "Voltar");
  backBtn->callback(backCallBack, readOne_window);

  

  readOne_window->end();
  readOne_window->show();
}

void updateCallBack(Fl_Widget *w, void *data) {
  cout << "Update button pressed" << endl;
}

void createCallBack(Fl_Widget *w, void *data) {
  cout << "Create button pressed" << endl;
}


class Funcao {
    
}

 MyBox *newBox = new MyBox(8, 0, 300, 60, "Proteínas", 24);
  MyBox *newBox2 = new MyBox(298, 0, 300, 60, "Aminoácidos", 24);

  for (int i = 0; i < table_rows; i++) {
    // Caixa da coluna 1

    MyBox *box1 = new MyBox(x_offset, y_offset, box_width, box_height, "Proteina" , 12);
    box1->box(FL_UP_BOX);
    box1->color(FL_WHITE);
    box1->labelsize(14);
    box1->labelcolor(FL_BLACK);
    box1->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    // Caixa da coluna 2
    MyBox *box2 = new MyBox(x_offset + box_width, y_offset, box_width, box_height, "Aminoacido", 12);
    box2->box(FL_UP_BOX);
    box2->color(FL_WHITE);
    box2->labelsize(14);
    box2->labelcolor(FL_BLACK);
    box2->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    y_offset += box_height;
}


// PESQUSAR
Fl_Input * searchInput = new Fl_Input(150, 10, 300, 30);
  searchInput->box(FL_BORDER_BOX);
  searchInput->label("Procurar: ");
  searchInput->labelsize(14);
  searchInput->textcolor(FL_BLACK);
  searchInput->textsize(14);

  Fl_Button * searchButton = new Fl_Button(460, 10, 100, 30, "Procurar");
  searchButton->callback(search_callback, searchInput);