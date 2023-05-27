#include "Pedido.h"

Pedido::Pedido(Student& es, UcTurma turma): estudante(es), novaturma(turma) {}

UcTurma Pedido::getUc() const {
    return novaturma;
}

Student Pedido::getStudent() const {
    return estudante;
}

void Pedido::setEstado(string state) {
    estado = state;
}

string Pedido::getEstado() const {
    return estado;
}