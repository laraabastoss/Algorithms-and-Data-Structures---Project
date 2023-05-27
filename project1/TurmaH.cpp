#include "TurmaH.h"

TurmaH::TurmaH(UcTurma turma): ucturma(turma) {}

UcTurma TurmaH::getUcturma() const  {
    return ucturma;
}

list<Bloco> TurmaH::getBlocos() const {
    return blocos;
}

void TurmaH::setUcTurma(UcTurma uc){
    ucturma = uc;
}

void TurmaH::addBlock(Bloco &b) {
    blocos.push_back(b);
}
