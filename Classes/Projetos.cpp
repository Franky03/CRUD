#include "Projetos.h"

Projeto::Projeto() : Projeto("", "", 0){}

Projeto::Projeto(string titulo, string descricao, int duracao){
    setTitulo(titulo);
    setDescricao(descricao);
    setDuracao(duracao);
}

string Projeto::getTitulo(){
    return titulo;
}

string Projeto::getDescricao(){
    return descricao;
}

int Projeto::getDuracao(){
    return duracao;
}

void Projeto::setTitulo(string titulo){
    this->titulo = titulo;
}

void Projeto::setDescricao(string descricao){
    this->descricao = descricao;
}

void Projeto::setDuracao(int duracao){
    this->duracao = duracao;
}