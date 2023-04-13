#include "Pessoa.h"

Pessoa::Pessoa() : Pessoa("", 0, "", ""){}

Pessoa::Pessoa(string nome, int idade, string cpf, string telefone){
    setNome(nome);
    setIdade(idade);
    setCpf(cpf);
    setTelefone(telefone);
}

string Pessoa::getNome(){
    return nome;
}

void Pessoa::setNome(string nome){
    this->nome = nome;
}

int Pessoa::getIdade(){
    return idade;
}

void Pessoa::setIdade(int idade){
    this->idade = idade;
}

string Pessoa::getCpf(){
    return cpf;
}

void Pessoa::setCpf(string cpf){
    this->cpf = cpf;
}

string Pessoa::getTelefone(){
    return telefone;
}

void Pessoa::setTelefone(string telefone){
    this->telefone = telefone;
}
