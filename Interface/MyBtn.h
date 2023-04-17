#include <FL/Fl_Button.H>

class MyBtn : public Fl_Button {
    public:
        MyBtn(int x, int y, int w, int h, const char *label = 0) : Fl_Button(x, y, w, h, label) {
        color(FL_WHITE);
        labelcolor(FL_BLACK);
        clear_visible_focus();
        }

        void draw() override {
            Fl_Button::draw(); 
    }
};
