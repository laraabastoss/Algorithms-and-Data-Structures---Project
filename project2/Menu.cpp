//
// Created by liamm on 07/01/2023.
//

#include "Menu.h"

using namespace std;

void Menu::execute() {


    cout << "\n\nCarregando Ficheiros ...\n\n";

    gestaovoos.LerFicheiros("../CSV/");

    cout << "Ficheiros totalmente carregados \n\n";

    string filtrobuffer, partida, destino, mainchoice;
    vector<string> companhias;
    int i;

    bool filtro;

    main_menu:
    cout << "\n Escolha uma das seguintes opcoes:\n";

    cout << " 1 - Pesquisar uma viagem\n";
    cout << " 2 - Pesquisar informacoes\n";
    cout << " 3 - Sair\n\n";

    getline(cin, mainchoice);
    int imainchoice = stoi(mainchoice);

    switch (imainchoice) {
        case 1: {
            cout << "\n\n\n\n-----------------------------------------------\n|                  TRIP FINDER                |\n-----------------------------------------------\n";
            cout << "\n Insira o local de partida e destino da sua viagem de sonho !";
            start:
            string pch;
            cout << "\n\n Local de Partida:  \n";
            cout << " 1 - Escolher um aeroporto\n";
            cout << " 2 - Escolher uma cidade\n";
            cout << " 3 - Escolher um ponto de partida\n\n";
            getline(cin, pch);
            if (pch == "1" || pch == "2"){

                if (pch == "1") cout << "\n Indique o nome do aeroporto pretendido: ";
                else cout << " Indique o nome da cidade pretendida:";

                getline(cin, partida);
                set<string> paisespartida = gestaovoos.Find_Countries(partida);
                if (paisespartida.size() == 0) {
                    cout << "\n O local introduzido nao e valido";
                    goto start;
                }
                if (*(paisespartida.begin()) != "airport") {
                    cout << " Possiveis paises:\n\n";

                    int numeropais = 1;
                    for (auto it = paisespartida.begin(); it != paisespartida.end(); it++) {
                        cout << " " << numeropais << " - " << *it << endl;
                        numeropais++;
                    }

                    pp:
                    cout << "\n Selecione o pais correspondente:  ";
                    int choicepartida;
                    string chp;
                    getline(cin, chp);

                    for (int b = 0; b < chp.size(); b++) {
                        if (!isdigit(chp[b])) {
                            cout << "\n Selecione uma opcao valida\n";
                            goto pp;
                        }
                    }

                    choicepartida = stoi(chp);
                    if (choicepartida < 1 || choicepartida > paisespartida.size()) {
                        cout << "\n Selecione uma opcao valida" << endl;
                        goto pp;
                    }
                    auto iter = paisespartida.begin();
                    for (int x = 0; x < choicepartida - 1; x++) {
                        iter++;
                    }
                    partida += ',' + *iter;
                }
            }
            else if (pch == "3"){

                string lat, lng, rad;

                gestaovoos.setPosicaopartida();
                cout << "\n Indique a latitude do local de onde pretende partir: ";
                getline(cin, lat);
                cout << "Indique a longitude do local de onde pretende partir: ";
                getline(cin, lng);
                cout << "Indique, em kilometros, qual o raio que pretende para a pesquisa de aeroportos: ";
                getline(cin, rad);
                gestaovoos.setRadPartida(rad);
                partida = lat + "," + lng;
            }
            else { cout << "\nIntroduza uma opcao valida\n"; goto start;}

            des:
            string dch;
            cout << "\n\n Local do Destino:  \n";
            cout << " 1 - Escolher um aeroporto\n";
            cout << " 2 - Escolher uma cidade\n";
            cout << " 3 - Escolher um ponto de chegada\n\n";
            getline(cin, dch);

            if (dch == "1" || dch == "2") {

                if (dch == "1") cout << "\n Indique o nome do aeroporto pretendido: ";
                else cout << " Indique o nome da cidade pretendida:";

                getline(cin, destino);
                set<string> paisesdestino = gestaovoos.Find_Countries(destino);
                if (paisesdestino.size() == 0) {
                    cout << "\n O local introduzido nao e valido";
                    goto des;
                }
                if (*(paisesdestino.begin()) != "airport") {
                    cout << " Possiveis paises:\n\n";
                    int numeropais = 1;
                    for (auto it = paisesdestino.begin(); it != paisesdestino.end(); it++) {
                        cout << " " << numeropais << " - " << *it << endl;
                        numeropais++;

                    }

                    pc:
                    cout << "\n Selecione o pais correspondente:  ";
                    int choicedestino;
                    string chd;
                    getline(cin, chd);

                    for (int b = 0; b < chd.size(); b++) {
                        if (!isdigit(chd[b])) {
                            cout << "\n Selecione uma opcao valida" << endl;
                            goto pc;
                        }
                    }

                    choicedestino = stoi(chd);
                    if (choicedestino < 1 || choicedestino > paisesdestino.size()) {
                        cout << "\n Selecione uma opcao valida\n";
                        goto pc;
                    }
                    auto id = paisesdestino.begin();
                    for (int x = 0; x < choicedestino - 1; x++) {
                        id++;
                    }
                    destino += ',' + *id;
                }
            }
            else if (dch == "3"){
                string lat_c, lng_c, rad_c;

                gestaovoos.setPosicaochegada();
                cout << "\n Indique a latitude do local onde pretende chegar: ";
                getline(cin, lat_c);
                cout << " Indique a longitude do local onde pretende chegar: ";
                getline(cin, lng_c);
                cout << " Indique, em kilometros, qual o raio que pretende para a pesquisa de aeroportos: ";
                getline(cin, rad_c);
                gestaovoos.setRadChegada(rad_c);
                destino = lat_c + "," + lng_c;
            }
            filtrar:
            cout << "\n Filtrar Companhias Aereas para a viagem (Y/N):";
            getline(cin, filtrobuffer);
            if (filtrobuffer == "Y" or filtrobuffer == "y") filtro = true;
            else if (filtrobuffer == "N" or filtrobuffer == "n") {
                filtro = false;
            } else goto filtrar;

            add_filtro:
            if (filtro) {
                bool exists = false;
                string companhia;

                airline_error:
                cout << " Insira o codigo da companhia em que pretende viajar: ";
                getline(cin, companhia);
                exists = gestaovoos.Find_Airlines(companhia);
                if (!exists){ cout << " Insira uma companhia valida\n\n"; goto airline_error;}
                companhias.push_back(companhia);

                choice_endalfilter:
                cout << "\n Escolha uma das seguintes opcoes: ";
                cout << "\n 1 - Adicionar outra companhia aerea aos filtros";
                cout << "\n 2 - Filtrar\n\n";

                string choice_more;
                getline(cin, choice_more);
                if (choice_more == "1") goto add_filtro;
                else if (choice_more == "2") goto processar_pedido;
                else { cout << "\n Escolha uma opcao valida"; goto choice_endalfilter;}
            }


            processar_pedido:
            cout << "\n A processar pedido ... \n\n";

            gestaovoos.MelhorViagem(partida, destino, companhias);
            companhias.clear();

            choice_end_search:
            string tempchoice;
            cout << "\n 1 - Pesquisar outra viagem";
            cout << "\n 2 - Voltar ao menu principal";
            cout << "\n 3 - Sair";
            cout << "\n\n Selecione uma das opcoes: ";

            getline(cin, tempchoice);

            if (tempchoice == "1") goto start;
            else if (tempchoice == "2") goto main_menu;
            else if (tempchoice == "3") return;
            else { cout << "\n Escolha uma opcao valida"; goto choice_end_search;}
        }
        case 2:{

            cout << "\n\n\n\n---------------------------------------------------\n|                  TRIP INFORMATION               |\n---------------------------------------------------\n";

            information_choice:
            cout << "\n Escolha uma das seguintes opcoes:";
            cout << "\n\n 1 - Obter informacoes sobre um determinado aeroporto";
            cout << "\n 2 - Obter informacoes sobre um determinado pais";
            cout << "\n 3 - Obter informacoes sobre uma determinada companhia aerea";
            cout << "\n 4 - Obter informacoes sobre a rede geral de voos\n\n";

            string scdchoice;
            getline(cin, scdchoice);

            if (scdchoice == "1"){
                airport_choice:
                cout << "\n Qual a informacao que pretende obter:";
                cout << "\n\n 1 - Numero de voos que partem de um determinado aeroporto";
                cout << "\n 2 - Listar voos que partem de um determinado aeroporto";
                cout << "\n 3 - Numero de cidades possiveis de alcancar a partir de um determinado aeroporto";
                cout << "\n 4 - Listar cidades possiveis de alcancar a partir de um determinado aeroporto";
                cout << "\n 5 - Numero de companhias aereas disponiveis num determinado aeroporto";
                cout << "\n 6 - Listar companhias aereas disponiveis num determinado aeroporto";
                cout << "\n 7 - Numero de cidades com voos que chegam a um determinado aeroporto";
                cout << "\n 8 - Listar cidades com voos que chegam a um determinado aeroporto";
                cout << "\n 9 - Numero de distinos alcancaveis a partir de um determinado aeroporto com um numero maximo de voos";
                cout << "\n 10 - Listar distinos alcancaveis a partir de um determinado aeroporto com um numero maximo de voos\n\n";

                string achoice;
                getline(cin, achoice);
                string information_airport;

                if (achoice == "1" || achoice == "2" || achoice == "3" || achoice == "4" || achoice == "5" || achoice == "6" || achoice == "7" || achoice == "8"){
                    cout << "\n Indique o codigo do aeroporto sobre o qual pretende obter esta informacao: ";
                    getline(cin, information_airport);

                    gestaovoos.getAirportInformation(information_airport, stoi(achoice));

                }
                else if (achoice == "9" || achoice == "10"){
                    cout << "\n Indique o codigo do aeroporto de partida:";
                    getline(cin, information_airport);

                    cout << " Indique o numero maximo de voos: ";
                    string nm;
                    getline(cin, nm);

                    gestaovoos.getAirportInformation(information_airport, stoi(achoice), stoi(nm));
                }
                else{
                    cout << "\n Selecione uma opcao valida"; goto airport_choice;
                }

                cout << "\n----------------------------------------------------------------------------";

                eac:
                cout << "\n Escolha uma das seguintes opcoes: ";
                cout << "\n 1 - Obter outras informacoes sobre um determinado aeroporto";
                cout << "\n 2 - Obter outras informacoes";
                cout << "\n 3 - Voltar ao menu principal";
                cout << "\n 4 - Sair\n\n";

                string endachoice;
                getline(cin, endachoice);

                if (endachoice == "1") goto airport_choice;
                else if (endachoice == "2") goto information_choice;
                else if (endachoice == "3") goto main_menu;
                else if (endachoice == "4") return;
                else {
                    cout << "\n Escolha uma opcao valida";
                    goto eac;
                }
            }

            else if (scdchoice == "2"){
                country_choice:
                cout << "\n Qual a informacao que pretende obter: \n";
                cout << "\n 1 - Numero de aeroportos disponiveis num determinado pais";
                cout << "\n 2 - Listar aeroportos disponiveis num determinado pais";
                cout << "\n 3 - Numero de companhias aereas dum determinado pais";
                cout << "\n 4 - Listar companhias aereas dum determinado pais";
                cout << "\n 5 - Numero de voos que partem dum determinado pais";
                cout << "\n 6 - Listar voos que partem de um determinado pais";
                cout << "\n 7 - Numero de voos com destino a um determinado pais";
                cout << "\n 8 - Listar voos com destino a um determinado pais";
                cout << "\n 9 - Top aeroportos com mais voos\n\n";

                string conchoice;
                getline(cin, conchoice);
                string aeroporto_escolhido;

                if (conchoice == "1" || conchoice == "2" || conchoice == "3" || conchoice == "4" || conchoice == "5" || conchoice == "6" || conchoice == "7" || conchoice == "8"){
                    cout << "\n Indique o nome do pais do qual pretende obter a informacao pedida: ";
                    getline(cin, aeroporto_escolhido);

                    gestaovoos.getCountryInformation(aeroporto_escolhido, stoi(conchoice));
                }
                else if(conchoice == "9"){
                    cout << "\n Indique o nome do pais do qual pretende obter a informacao pedida:";
                    getline(cin, aeroporto_escolhido);

                    cout << " Indique o numero de aeroportos que pretende obter:";
                    string t;
                    getline(cin, t);

                    gestaovoos.getCountryInformation(aeroporto_escolhido, stoi(conchoice), stoi(t));
                }
                else {
                    cout << "\n Selecione uma opcao valida"; goto country_choice;
                }

                cout << "\n----------------------------------------------------------------------------";

                ecc:
                cout << "\n Escolha uma das seguintes opcoes: ";
                cout << "\n 1 - Obter outras informacoes sobre um determinado pais";
                cout << "\n 2 - Obter outras informacoes";
                cout << "\n 3 - Voltar ao menu principal";
                cout << "\n 4 - Sair\n\n";

                string endcchoice;
                getline(cin, endcchoice);

                if (endcchoice == "1") goto country_choice;
                else if (endcchoice == "2") goto information_choice;
                else if (endcchoice == "3") goto main_menu;
                else if (endcchoice == "4") return;
                else {
                    cout << "\n Escolha uma opcao valida";
                    goto ecc;
                }
            }

            else if (scdchoice == "3"){

                airline_choice:
                cout << "\n Qual a informacao que pretende obter: \n";

                cout << "\n 1 - Numero de aeroportos cobertos por uma determinada companhia";
                cout << "\n 2 - Listar os aeroportos cobertos por um adeterminada companhia";
                cout << "\n 3 - Numero de voos de uma determinada companhia";
                cout << "\n 4 - Listar voos de uma determinada companhia";
                cout << "\n 5 - Maior distancia percorrida por uma determinada companhia (diametro)";
                cout << "\n 6 - Aeroportos essenciais para escalas de uma determinada companhia (pontos de articulacao)\n\n";

                string alchoice;
                getline(cin, alchoice);
                int ialchoice = stoi(alchoice);

                switch (ialchoice){
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:{
                        cout << "\n Indique o codigo da companhia da qual pretende obter a informacao pedida: ";
                        string airline_escolhida;
                        getline(cin, airline_escolhida);

                        gestaovoos.getAirlineInformation(airline_escolhida, ialchoice);

                        cout << "\n----------------------------------------------------------------------------";

                        ealc:
                        cout << "\n Escolha uma das seguintes opcoes: \n";
                        cout << "\n 1 - Obter outras informacoes sobre uma determinada companhia aerea";
                        cout << "\n 2 - Obter outras informacoes";
                        cout << "\n 3 - Voltar ao menu principal";
                        cout << "\n 4 - Sair\n\n";

                        string endalchoice;
                        getline(cin, endalchoice);

                        if (endalchoice == "1") goto airline_choice;
                        else if (endalchoice == "2") goto information_choice;
                        else if (endalchoice == "3") goto main_menu;
                        else if (endalchoice == "4") return;
                        else {
                            cout << "\n Escolha uma opcao valida";
                            goto ealc;
                        }

                    }
                    default: {
                        cout << "\n Escolha uma opcao valida";
                        goto airline_choice;
                    }
                }
            }

            else if (scdchoice == "4"){

                rede_choice:
                cout << "\n Qual a informacao que pretende obter: \n";
                cout << "\n 1 - Numero de aeroportos";
                cout << "\n 2 - Listagem dos aeroportos";
                cout << "\n 3 - Numero de voos";
                cout << "\n 4 - Listagem dos voos";
                cout << "\n 5 - Numero de companhias aereas";
                cout << "\n 6 - Listagem das companhias aereas";
                cout << "\n 7 - Top aeroportos com mais voos\n\n";

                string rchoice;
                getline(cin, rchoice);

                if (rchoice == "1" || rchoice == "2" || rchoice == "3" || rchoice == "4" || rchoice == "5" || rchoice == "6"){

                    gestaovoos.getRedeGlobalInformation( stoi(rchoice));

                }
                else if(rchoice == "7"){
                    string t;
                    cout << " Indique o numero de aeroportos que pretende obter: ";
                    getline(cin, t);

                    gestaovoos.getRedeGlobalInformation(stoi(rchoice), stoi(t));
                }
                else {
                    cout << "\n Selecione uma opcao valida"; goto rede_choice;
                }

                cout << "\n----------------------------------------------------------------------------";

                erc:
                cout << "\n Escolha uma das seguintes opcoes: ";
                cout << "\n 1 - Obter outras informacoes sobre a rede";
                cout << "\n 2 - Obter outras informacoes";
                cout << "\n 3 - Voltar ao menu principal";
                cout << "\n 4 - Sair\n\n";

                string endrchoice;
                getline(cin, endrchoice);

                if (endrchoice == "1") goto rede_choice;
                else if (endrchoice == "2") goto information_choice;
                else if (endrchoice == "3") goto main_menu;
                else if (endrchoice == "4") return;
                else {
                    cout << "\n Escolha uma opcao valida";
                    goto erc;
                }
            }

            else{
                cout << "\n Escolha uma opcao valida"; goto information_choice;
            }
        }
        case 3: return;
        default: cout << "\n Escolha uma opcao valida \n"; goto main_menu;
    }
}
