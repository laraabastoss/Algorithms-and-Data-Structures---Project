//
// Created by liamm on 07/01/2023.
//

#ifndef TRABALHO_AED2_MENU_H
#define TRABALHO_AED2_MENU_H

#include "GestaoVoos.h"

class Menu {

private:
    GestaoVoos gestaovoos;
public:
    /// default constructor
    Menu() = default;
    /// menu/program executable
    void execute();
};


#endif //TRABALHO_AED2_MENU_H
