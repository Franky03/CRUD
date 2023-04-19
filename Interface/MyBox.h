#include <FL/Fl_Box.H>

class MyBox : public Fl_Box {
    public:
        MyBox(int x, int y, int w, int h, const char *label = 0, const int lsize=36) : Fl_Box(x, y, w, h, label) {
            labelcolor(FL_WHITE);
            labelsize(lsize);
            labelfont(FL_HELVETICA_BOLD);
        }
};