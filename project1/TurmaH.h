#ifndef HORARIO_TURMAH_H
#define HORARIO_TURMAH_H

#include<string>
#include <list>
#include "UcTurma.h"
#include "Bloco.h"

using namespace std;

class TurmaH {
private:
    UcTurma ucturma;
    list<Bloco> blocos;
public:
    ///creates TurmaH for the given UcTurma - initializes with an empty schedule (blocos)
    TurmaH(UcTurma turma);
    ///
    /// \return ucturma
    UcTurma getUcturma() const;
    ///
    /// \return blocos
    list<Bloco> getBlocos() const;
    void setUcTurma(UcTurma uc);
    /// adds new Bloco to blocos
    /// \param b new Bloco to be added to the schedule
    void addBlock(Bloco &b);
    ///override of operator '==' for class TurmaH
    bool operator==(const TurmaH& turmah){
        return turmah.getUcturma() == ucturma;
    }

};


#endif //HORARIO_TURMAH_H
