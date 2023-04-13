#include "Equipamento.h"

Equipamento::Equipamento() : Equipamento("", 0, "", false){}

Equipamento::Equipamento(string nome, int num_serie, string modelo, bool disponivel){
    setNome(nome);
    setNumSerie(num_serie);
    setModelo(modelo);
    setDisponivel(disponivel);
}

string Equipamento::getNome(){
    return nome;
}

void Equipamento::setNome(string nome){
    this->nome = nome;
}

int Equipamento::getNumSerie(){
    return num_serie;
}

void Equipamento::setNumSerie(int num_serie){
    this->num_serie = num_serie;
}

string Equipamento::getModelo(){
    return modelo;
}

void Equipamento::setModelo(string modelo){
    this->modelo = modelo;
}

bool Equipamento::getDisponivel(){
    return disponivel;
}

void Equipamento::setDisponivel(bool disponivel){
    this->disponivel = disponivel;
}
