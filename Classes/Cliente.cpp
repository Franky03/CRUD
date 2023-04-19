#include "Cliente.h"

Cliente::Cliente() : Cliente("", 0, "", "", "", ""){}

Cliente::Cliente(string nome, int idade, string cpf, string telefone, string encomenda, string data)
: Pessoa(nome, idade, cpf, telefone){
    setEncomenda(encomenda);
    setData(data);
}

string Cliente::getEncomenda(){
    return encomenda;
}

void Cliente::setEncomenda(string encomenda){
    this->encomenda = encomenda;
}

string Cliente::getData(){
    return data;
}

void Cliente::setData(string data){
    this->data = data;
}

vector<string> Cliente::getMethods()
{
    return {"Reclamar", "Elogiar", "Esperar"};
}