#ifndef HORARIO_STUDENT_H
#define HORARIO_STUDENT_H

#include <string>
#include <iostream>
#include "UcTurma.h"
#include <list>

using namespace std;

class Student {
private:
    ///up code of the Student
    string code;
    ///name of the Student
    string name;
    list<UcTurma> ucturmas;
public:
    ///default constructor
    Student() = default;
    ///creates a Student with the given code and the other attributes as empty
    /// \param c up code of the Student
    Student(string c);
    ///creates a Student with the given code and name and with an empty list of UcTurma
    /// \param c up code of the Student
    /// \param n name of the Student
    Student(string c, string n);
    ///
    /// \return Student code
    string getCode() const;
    ///
    /// \return Student name
    string getName() const;
    ///
    /// \return list of UcTurma in which the Student is enrolled
    list<UcTurma> getUcturma() const;
    /// adds a given UcTurma to ucturmas
    /// \param uc UcTurma to be added
    void addUcturma(UcTurma& uc);
    /// removes a given UcTurma from ucturmas
    /// \param uc UcTurma to be removed
    void removeUcturma(UcTurma& uc);
    /// override of the operator '<' for class Student
    bool operator<(const Student& rhs) const;
    /// override of the operator '==' for class Student
    bool operator==(const Student& lhs)
    {
        return lhs.getCode() == code;
    }

};


#endif //HORARIO_STUDENT_H
