#ifndef HORARIO_UCTURMA_H
#define HORARIO_UCTURMA_H

using namespace std;

#include <string>
#include <iostream>
#include <set>


class UcTurma {
private:
    ///uc of UcTurma
    string codeuc;
    ///class of UcTurma
    string codeturma;
    ///number of people in UcTurma
    int lotacao = 1;

public:
    ///default constructor
    UcTurma() = default;
    /// creates UcTurma with the given codeuc and codeturma with an initial lotacao of 1
    /// \param cuc uc of UcTurma
    /// \param ct codeturma of UcTurma
    UcTurma(string cuc , string ct);
    ///
    /// \return codeuc
    string getCodeuc() const;
    ///
    /// \return codeturma
    string getCodeturma() const;
    ///
    /// \return lotacao
    int getLotacao() const;
    ///
    /// \param a new lotacao
    void setLotacao(int a);
    /// override of operator '==' for class UcTurma
    bool operator==(const UcTurma& lhs)
    {
        return lhs.getCodeuc() == codeuc  && lhs.getCodeturma() == codeturma;
    }
    /// override of operator '<<' for class UcTurma
    friend ostream& operator<<(ostream& os, const UcTurma& dt);
    /// override of operator '<' for class UcTurma
    bool operator<(const UcTurma& rhs) const;

};


#endif //HORARIO_UCTURMA_H
