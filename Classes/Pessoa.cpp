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
    if(nome.empty()){
        this->nome = "Sem nome";
        return;
    }
    this->nome = nome;
}

int Pessoa::getIdade(){
    return idade;
}

void Pessoa::setIdade(int idade){
    if(idade < 0 || idade > 100){
        this->idade = 18;
        return;
    }
    this->idade = idade;
}

string Pessoa::getCpf(){
    return cpf;
}

void Pessoa::setCpf(string cpf){
    if(cpf.empty()){
        this->cpf = "Sem CPF";
        return;
    }
    this->cpf = cpf;
}

string Pessoa::getTelefone(){
    return telefone;
}

void Pessoa::setTelefone(string telefone){
    if(telefone.empty()){
        this->telefone = "Sem telefone";
        return;
    }
    this->telefone = telefone;
}
