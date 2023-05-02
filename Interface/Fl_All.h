#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "FL/fl_draw.H"
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Table.H>

#define RELATORIO_TXT "../Logs/relatorio.txt"
#define FUNCIONARIO "FUNCIONARIO"
#define CLIENTE "CLIENTE"
#define PESQUISADOR "PESQUISADOR"
#define TECNICO "TECNICO"
#define PROJETO "PROJETO"
#define EQUIPAMENTO "EQUIPAMENTO"

#include "MyBtn.h"
#include "MyWindow.h"
#include "MyBox.h"
#include "MyTable.h"

#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#include <fstream>

#include "../Database/Crud.h"  
#include "../Classes/allClass.h"