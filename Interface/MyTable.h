#include <iostream>
#include "FL/Fl_Table.H"
#include <vector>
#include <string>
#include "FL/Fl.H"

using namespace std;

string capitalize(string text) {

	for (int x = 0; x < text.length(); x++)
	{
		if (x == 0)
		{
			text[x] = toupper(text[x]);
		}
		else if (text[x - 1] == ' ')
		{
			text[x] = toupper(text[x]);
		}
	}

	return text;
}

class MyTable : public Fl_Table {
    public:
        MyTable(int x, int y, int w, int h, int c, int r,  const char *l = 0) : Fl_Table(x, y, w, h, l) {
            rows(r);             
            cols(c);          
               
            end();               
        }

        void set_data(vector<string> data, vector<string> column_names, bool readAll=true){
            this->data = data;
            this->column_names = column_names;
            rows(data.size());
            int total_height = table_size(1) + table_size(0) + rows() * table_size(2);
            if(readAll){
                size(w(), 270);
            }
            else {
                size(w(),100);
            }
            redraw();
}
    protected:
        void draw_cell(TableContext context, int row, int col, int x, int y, int w, int h) {
            switch ( context ) {
                case CONTEXT_STARTPAGE:                   // before page is drawn..
                    fl_font(FL_HELVETICA, 14);          // set the font for our drawing operations
                    return;
            
                case CONTEXT_CELL:  {
                    fl_push_clip(x, y, w, h);
                    fl_draw_box(FL_BORDER_BOX, x, y, w, h, col_header() ? row == 0 ? color() : FL_WHITE : color());
                    fl_color(FL_BLACK);
                    //é pra colocar o botão somente se a linha for maior que 0 e se tiver conteudo naquela linha
                    
                    if (row == 0) {
                        // Desenhe o cabeçalho da coluna a partir da Coluna 1
                        try {
                            if(column_names.at(col) != "")
                                fl_draw((capitalize(column_names.at(col))).c_str(), x+10, y, w-20, h, FL_ALIGN_LEFT);
                            else
                                fl_draw("", x+10, y, w-20, h, FL_ALIGN_LEFT);
                        } catch (const std::out_of_range& e) {
                            fl_draw("", x+10, y, w-20, h, FL_ALIGN_LEFT);
                        }
                        
                        
                    } else if (row == 1) {
                        // Desenhe os dados da coluna na segunda linha da tabela a partir da Coluna 1
                        int data_index = col ;
                        try {
                            fl_draw(data.at(data_index).c_str(), x+10, y, w-20, h, FL_ALIGN_LEFT);
                        } catch (const std::out_of_range& e) {
                            fl_draw("", x+10, y, w-20, h, FL_ALIGN_LEFT);
                        }
                        
                    } else {
                        // Desenhe um espaço vazio para todas as outras linhas da tabela a partir da Coluna 1
                        
                        fl_draw("", x+10, y, w-20, h, FL_ALIGN_LEFT);
                        
                    }
                    
                    
                    fl_pop_clip();
                    break;
                }
                default:
                    return;
            }
        }

        int table_size(int x){
            return x>0 ? 30 : 20;
        }   
    private:
        vector<string> data;
        vector<string> column_names;
};