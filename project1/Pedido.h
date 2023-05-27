#ifndef HORARIO_PEDIDO_H
#define HORARIO_PEDIDO_H

#include <stdio.h>
#include <string>
#include <set>
#include "Student.h"

using namespace std;

class Pedido {
private:
    /// Student who made Pedido
    Student estudante;
    /// UcTurma that estudante would like to enroll
    UcTurma novaturma;
    /// State of Pedido
    string estado;
public:
    /// creates Pedido with the given Student and UcTurma in an empty estado
    /// \param es Student who made Pedido
    /// \param turma UcTurma that estudante would like to enroll
    Pedido(Student& es, UcTurma turma);
    ///
    /// \return UcTurma that estudante would like to enroll
    UcTurma getUc() const;
    ///
    /// \return Student who made Pedido
    Student getStudent() const;
    ///
    /// \param state new estado of Pedido
    void setEstado(string state);
    ///
    /// \return estado of Pedido
    string getEstado() const;

};


#endif //HORARIO_PEDIDO_H
