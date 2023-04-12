#include "Pessoa.h"

using namespace std;

class Cliente : public Pessoa {
    public:
        Cliente(string nome, int idade, string cpf, string telefone, string encomenda, string data);
        
        string getEncomenda();
        void setEncomenda(string encomenda);
        string getData();
        void setData(string data);

    private: 
        string encomenda;
        string data;
};
