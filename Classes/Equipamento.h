#include <iostream>
#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

using namespace std;

class Equipamento {
    public:
        Equipamento();
        Equipamento(string nome, int num_serie, string modelo, bool disponivel);
        
        string getNome();
        void setNome(string nome);
        int getNumSerie();
        void setNumSerie(int num_serie);
        string getModelo();
        void setModelo(string modelo);
        bool getDisponivel();
        void setDisponivel(bool disponivel);
    
    private:
        string nome;
        int num_serie;
        string modelo;
        bool disponivel;
};

#endif