#include <iostream>
#ifndef PROJETOS_H
#define PROJETOS_H

using namespace std;

class Projeto {
    public:
        Projeto();
        Projeto(string titulo, string descricao, int duracao);
        
        string getTitulo();
        string getDescricao();
        int getDuracao();
        void setTitulo(string titulo);
        void setDescricao(string descricao);
        void setDuracao(int duracao);
    
    private:
        string titulo;
        string descricao;
        int duracao;
};

#endif