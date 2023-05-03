#include <iostream>

using namespace std;

void backCallBack(Fl_Widget *w, void *data) {
  last_window->show();
  Fl_Window *new_window = static_cast<Fl_Window*>(data);
  new_window->hide();
}