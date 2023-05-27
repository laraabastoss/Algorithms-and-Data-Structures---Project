#ifndef HORARIO_BLOCO_H
#define HORARIO_BLOCO_H

#include <string>
#include <iostream>

using namespace std;

class Bloco {
private:
    ///day of the week
    string diasemana;
    ///starting hour
    string horainicio;
    ///duration
    string duracao;
    ///type of class
    string tipo;
public:
    /// constructor
    /// \param ds diasemana
    /// \param hi horainicio
    /// \param du duracao
    /// \param ti tipo
    Bloco(string ds, string hi, string du, string ti);
    ///
    /// \return diasemana
    string getDiaSemana() const;
    ///
    /// \return horainicio
    string getHoraInicio() const;
    ///
    /// \return duracao
    string getDuracao() const;
    ///
    /// \return tipo
    string getTipo() const;
    /// override of operator '<<' for class Bloco
    friend ostream& operator<<(ostream& os, const Bloco& dt);
    /// calculates class ending hour
    /// \return ending hour
    string getHoraFim() const;
};


#endif //HORARIO_BLOCO_H
