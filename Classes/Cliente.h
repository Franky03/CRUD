#include "Pessoa.h"

using namespace std;

class Cliente : public Pessoa {
    private: 
        string encomenda;
        string data;
    public:
        Cliente(string nome, int idade, string cpf, string encomenda, string data);
        string getEncomenda();
        void setEncomenda(string encomenda);
        string getData();
        void setData(string data);
};
