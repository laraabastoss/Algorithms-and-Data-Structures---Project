#ifndef HORARIO_GESTAOHORARIO_H
#define HORARIO_GESTAOHORARIO_H

#include <map>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include "Student.h"
#include "TurmaH.h"
#include "Pedido.h"

using namespace std;

class GestaoHorario {
private:
    set<Student> estudantes;
    vector<TurmaH> turmas;
    queue<Pedido> listaespera;
    queue<Pedido> listaceites;
    queue<Pedido> listarecusados;
    list<UcTurma> ucturmas;
public:
    /// default constructor - initializes all atributes as empty
    GestaoHorario() = default;
    /// \return set of Student
    set<Student> getEstudantes() const;
    /// \return vector of TurmaH
    vector<TurmaH> getTurmas() const;
    /// \return list of UcTurma
    list<UcTurma> getUcturmas() const;
    ///
    /// \return queue of Pedido in the waiting state
    queue<Pedido> getListaespera() const;
    ///
    /// \return queue of refused Pedido
    queue<Pedido> getListarecusados() const;
    ///
    /// \return queue of accepted Pedido
    queue<Pedido> getListaaceites() const;
    /// reads the files and creates the necessary objects
    ///
    /// O(n^2)
    /// \param path path of file
    void lerFicheiros(string path);
    /// creates Pedido and saves it in listaespera
    ///
    /// O(n)
    /// \param up upcode of the Student making the request
    /// \param uc uccode of the UcTurma the Student wants to change
    /// \param classcode classcode of the UcTurma the Student wants to change
    void guardarPedidos(string up, string uc, string classcode);
    /// everyday at midnight it processes every Pedido waiting in listaespera and verifies if it can be accepted or not.
    ///
    /// if it satisfies all the requirements than it gets into listaaceites and the UcTurma in ucturmas of the Student is altered.
    ///
    ///otherwise Pedido will go to listarecusados.
    ///
    ///O(n^4)
    /// \param forcado indicates if the function is going to be executed at midnight, the way it's supposed to, in that case the parameter will be false, or if it was forced into being implemented, in which case the parameter will have the value true.
    void processarPedidos(bool forcado);
    /// searches in estudantes for the Student with the given up
    ///
    ///O(log n)
    /// \param up upcode of the Student we want to find
    /// \return Student with given up in estudantes
    Student findStudent(string up) const;
    ///creates a file with the students and their updated classes in each uc.
    ///
    /// O(n^2)
    void listagem() const;
};


#endif //HORARIO_GESTAOHORARIO_H
