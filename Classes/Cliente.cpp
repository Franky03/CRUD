#include "Cliente.h"

Cliente::Cliente() : Cliente("", 0, "", "", "", "", 0.0){}

Cliente::Cliente(string nome, int idade, string cpf, string telefone, string encomenda, string data, float devendo)
: Pessoa(nome, idade, cpf, telefone){
    setEncomenda(encomenda);
    setData(data);
    setDevendo(devendo);
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

void Cliente::setDevendo(float devendo){
    this->devendo = devendo;
}

float Cliente::getDevendo(){
    return devendo;
}

vector<string> Cliente::getMethods()
{
    return {"Reclamar", "Elogiar", "Esperar"};
}

bool Cliente::getSatisfacao(){
    return clienteFeliz;
}

void Cliente::reclamar(){
    cout << "Cliente reclamando..." << endl;
    clienteFeliz = false;
}

void Cliente::elogiar(){
    cout << "Cliente elogiando..." << endl;
    clienteFeliz = true;
}
