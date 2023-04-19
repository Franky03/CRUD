#include <iostream>
#ifndef PROJETOS_H
#define PROJETOS_H

using namespace std;

class Projeto {
    public:
        Projeto();
        Projeto(string nome, string descricao, int duracao);
        
        string getNome();
        string getDescricao();
        int getDuracao();
        void setNome(string nome);
        void setDescricao(string descricao);
        void setDuracao(int duracao);
    
    private:
        string nome;
        string descricao;
        int duracao;
};

#endif