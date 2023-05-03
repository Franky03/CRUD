#include "Pessoa.h"

using namespace std;

class Cliente : public Pessoa {
    public:
        Cliente();
        Cliente(string nome, int idade, string cpf, string telefone, string encomenda, string data, float devendo);
        
        string getEncomenda();
        void setEncomenda(string encomenda);
        string getData();
        bool getSatisfacao();
        void setData(string data);
        void setDevendo(float devendo);
        float getDevendo();
        
        void reclamar();
        void elogiar();
        vector<string> getMethods();

    private: 
        string encomenda;
        string data;
        bool clienteFeliz;
        float devendo;
};
