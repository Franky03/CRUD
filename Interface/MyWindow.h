#include <FL/Fl_Window.H>


class MyWindow : public Fl_Window {
    
// Definir a posição da janela para ficar centralizada na tela
    public:
        MyWindow(int w, int h, const char *title = 0) : Fl_Window(w, h, title) {
            color(0x62CDFF);
            position(600, 300);
        }
};