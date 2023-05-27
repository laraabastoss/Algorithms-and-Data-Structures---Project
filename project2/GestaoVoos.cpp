//
// Created by Lara Bastos on 26/12/2022.
//

#include "GestaoVoos.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;


 void GestaoVoos::LerFicheiros(string path) {

    ifstream infile(path+ "airports.csv");

    string line;

    getline(infile, line);

    while(getline(infile,line)){

        istringstream iss(line);

        string substring;

        vector<string> substrings{};

        while (getline(iss, substring,',')){

            substrings.push_back(substring);

        }

        Airport airport(substrings[0],substrings[1], substrings[3], substrings[2], substrings[4], substrings[5]);
        airportPerCity.insert(make_pair(substrings[0], make_pair(substrings[2], substrings[3])));
        airports_lat_long.insert(make_pair(substrings[0], make_pair(substrings[4], substrings[5])));
        airports.insert(airport);

    }

     ifstream infile2(path+ "airlines.csv");

     getline(infile2, line);

     while(getline(infile2,line)){

         istringstream iss(line);

         string substring;

         vector<string> substrings{};

         while (getline(iss, substring,',')){

             substrings.push_back(substring);

         }

         Airline airline(substrings[0],substrings[1], substrings[3], substrings[2]);

         airlines.insert(airline);


     }

     ifstream infile3(path+ "flights.csv");

     getline(infile3, line);

     while(getline(infile3,line)){
         istringstream iss(line);

         string substring;

         vector<string> substrings{};

         while (getline(iss, substring,',')){

             substrings.push_back(substring);

         }

         bool inserted = false;
         if (!flights.empty()){
             for (Graph &graph : flights){
                 if (graph.getAirline() == substrings[2]){
                     graph.addEdge(substrings[0], substrings[1]);
                     inserted = true;
                 }
             }
         }
         if (!inserted){
             Graph newgraph = Graph(substrings[2]);
             newgraph.addEdge(substrings[0], substrings[1]);
             flights.push_back(newgraph);
         }
         mergedFligths.addEdgeWithAirline(substrings[0],substrings[1] , substrings[2]);
     }

 }

vector<Graph::Node> GestaoVoos::bfs(Graph::Node airport, Graph airlinegraph, string aeroportochegada, vector<string> companhias){
    queue<Graph::Node> unvisited;
    airport.distance = 0;
    airport.visited = true;
    list<string> options;
    vector<Graph::Node> nodes_airline = airlinegraph.getNodes();
    for (Graph::Node & n : nodes_airline) {
        n.visited = false;
        n.distance = INT_MAX;
        n.prev = "";
        if (n.src==airport.src){
            n.visited = true;
            n.distance = 0;
            unvisited.push(n);
        }

    }


    while (!unvisited.empty()){
        Graph::Node curr = unvisited.front();
        unvisited.pop();
        for (Graph::Edge chegada : curr.adj){
            for (Graph::Node & n : nodes_airline){
                if (chegada.dest == n.src & !n.visited & companhias.size()<=1){
                    n.visited = true;
                    n.distance = curr.distance + 1;
                    n.prev = curr.src;
                    unvisited.push(n);
                    if (n.src==aeroportochegada) return nodes_airline;
                }
                if (chegada.dest == n.src & !n.visited & companhias.size()>1 & stringInVec(chegada.airline, companhias)){
                    n.visited = true;
                    n.distance = curr.distance + 1;
                    n.prev = curr.src;
                    unvisited.push(n);
                    if (n.src==aeroportochegada) return nodes_airline;
                }
            }
        }


    }
    return nodes_airline;

}
set<string> GestaoVoos::bfsWithMax(string airport, Graph airlinegraph, int max){
    queue<Graph::Node> unvisited;
    set<string> string_airports;
    list<string> options;
    vector<Graph::Node> nodes_airline = airlinegraph.getNodes();
    for (Graph::Node & n : nodes_airline) {
        n.visited = false;
        n.prev = "";
        n.distance = INT_MAX;

    }

    for (Graph::Node & n : nodes_airline) {
        if (n.src==airport){
            n.visited = true;
            n.distance = 0;
            unvisited.push(n);
        }
    }

    bool reachedMax=false;
    while (!unvisited.empty()){
        Graph::Node curr = unvisited.front();
        unvisited.pop();
        for (Graph::Edge chegada : curr.adj){
            for (Graph::Node & n : nodes_airline){
                if (chegada.dest == n.src & !n.visited){
                    n.visited = true;
                    n.distance = curr.distance + 1;
                    n.prev = curr.src;
                    unvisited.push(n);
                    if (n.distance>max) reachedMax=true;
                    else string_airports.insert(chegada.dest);
                }

                if (reachedMax) break;

            }

            if (reachedMax) break;

        }

        if (reachedMax) break;

    }

    return string_airports;

}
int GestaoVoos::bfsDiameter(string airport, Graph airlinegraph){
    queue<Graph::Node> unvisited;
    int max=0;
    vector<Graph::Node> nodes_airline = airlinegraph.getNodes();
    for (Graph::Node & n : nodes_airline) {
        n.visited = false;
        n.distance = INT_MAX;
        if (n.src == airport) {
            n.visited = true;
            n.distance = 0;
            unvisited.push(n);
        }
    }

    while (!unvisited.empty()){
        Graph::Node curr = unvisited.front();
        unvisited.pop();
        for (Graph::Edge chegada : curr.adj){
            for (Graph::Node & n : nodes_airline){
                if (chegada.dest == n.src & !n.visited){
                    n.visited = true;
                    n.distance = curr.distance + 1;
                    n.prev = curr.src;
                    unvisited.push(n);
                    if (n.distance>max) max=n.distance;
                }
            }
        }
    }
    return max;

}
vector<string> GestaoVoos::findShortestDistance( Graph::Node src,string dest,  Graph airlinegraph, vector<string> companhias){
    vector<string> path;
    Graph::Node curr;
    vector<Graph::Node> nodes_airline = bfs(src, airlinegraph, dest, companhias);
    if (nodes_airline.size()==0) return {};
    for (Graph::Node n : nodes_airline){
        if (n.src==dest){
            curr=n;
            break;
        }
    }
    path.push_back(curr.src);
    while (curr.prev!="") {
        path.push_back(curr.prev);
        for (Graph::Node n : nodes_airline){
            if (n.src==curr.prev){
                curr=n;
                break;
            }
        }
    }
    reverse(path.begin(),path.end());
    if (*path.begin()==src.src and *(path.end()-1)==dest) return path;
    else return {};
}





void GestaoVoos::MelhorViagem(std::string partida, std::string chegada, vector<string> companhias) {
    Graph vooscompanhia;
    list<string> aeroportospartida, aeroportoschegada;
    vector<vector<string>> paths;
    bool resultsfound=false;

    istringstream iss1(partida), iss2(chegada);
    string substring;
    vector<string> partidas{}, chegadas{};
    while (getline(iss1, substring,',')){
        partidas.push_back(substring);
    }
    while (getline(iss2, substring, ',')){
        chegadas.push_back(substring);
    }

    if (companhias.size()==0 || companhias.size()>1){
        vooscompanhia=mergedFligths;
    }


    else for (Graph voo: flights) {
            if (voo.getAirline() == companhias.at(0)) {
                vooscompanhia = voo;
                break;
            }
        }


    for (Airport airport: airports) {
        if (airport.getCode() == partidas[0]) {
            aeroportospartida.push_back(partidas[0]);
        }
        if (airport.getCode() == chegadas[0]) {
            aeroportoschegada.push_back(chegadas[0]);
        }
    }


    if (posicaochegada){
        double a = stod(chegadas[0]);
        double b = stod(chegadas[1]);
        aeroportoschegada = Find_Airports(a, b, radChegada);
        if (aeroportoschegada.empty()) {
            cout << "Nao existe nenhum aeroporto na area de chegada pretendida.\n";
            return;
        }
    }
    else if (aeroportoschegada.empty()) {
        for (pair<string, pair<string,string>> airport_city: airportPerCity) {
            if (airport_city.second.first == chegadas[0] && airport_city.second.second == chegadas[1]) aeroportoschegada.push_back(airport_city.first);
        }
    }


    if (posicaopartida){
        double a = stod(partidas[0]);
        double b = stod(partidas[1]);
        aeroportospartida = Find_Airports(a, b, radPartida);
        if (aeroportospartida.empty()) {
            cout << "Nao existe nenhum aeroporto na area de partida pretendida.\n";
            return;
        }
    }
    else if (aeroportospartida.empty()) {
        for (pair<string, pair<string,string>> airport_city: airportPerCity) {
            if (airport_city.second.first == partidas[0] && airport_city.second.second == partidas[1]) aeroportospartida.push_back(airport_city.first);
        }
    }

    if (aeroportospartida.empty()) {
        cout << "There are not any flights departing from " << partida << " with this airline." << endl;
        return;
    }


    if (aeroportoschegada.empty()) {
        cout << "There are not any flights arriving to " << chegada << " with this airline." << endl;
        return;
    }

    list<pair<string, pair<string, int>>> nrvoos_partida_chegada;

    int sizemin = INT16_MAX;
    for (string nomeaeroporto: aeroportospartida) {
        Graph::Node voos_aeroporto;
        bool exitsflights=false;
        for (Graph::Node voos_aeroportos_companhia: vooscompanhia.getNodes()) {
            if (voos_aeroportos_companhia.src == nomeaeroporto) {
                resultsfound=true;
                voos_aeroporto = voos_aeroportos_companhia;
                exitsflights=true;

                break;
            }
        }
        if (!exitsflights) continue;



        for (string aeroportochegada: aeroportoschegada) {
            vector<string> path = findShortestDistance(voos_aeroporto, aeroportochegada, vooscompanhia,companhias);

            if ( path.size() != 0) {
                paths.push_back(path);
                if (path.size()<=sizemin){
                    sizemin=path.size();
                }
            }
        }

    }
    list<vector<string>> finalpaths;
    for (vector<string> path :paths){
        if (path.size()==sizemin) finalpaths.push_back(path);
    }

    cout << "--------------------" << endl;

    noflighs: if (finalpaths.size() == 0) {
    cout << "Nao existem voos a conectar " << partida << " e "<<chegada;
    if (companhias.size()>1 ) cout<< " com "<<companhias.at(0)<<", ";
    if (companhias.size()==1){
        cout<< " com "<<companhias.at(0)<<".";
        return;
    }
    if (companhias.size()==1){
        cout<< ".";
        return;
    }
    for (int i=1;i<companhias.size();i++){
        cout<< companhias.at(i)<< ".";
        return;
    }
} else {
    if (companhias.size()==1){
        for (vector<string> path: finalpaths) {
            for (int i = 0; i < path.size() - 1; i++) {
                auto i1 = airportPerCity.find(path.at(i));
                auto i2 = airportPerCity.find(path.at(i + 1));
                cout << path.at(i) << ", " << i1->second.first << ", " << i1->second.second << " -> " << path.at(i + 1) << ", " << i2->second.first << ", " << i2->second.second<<endl;
            }
            cout<<"---------------------" << endl;
        }
    }
    else{
        for (vector<string> path: finalpaths) {
            for (int i = 0; i < path.size() - 1; i++) {
                auto i1 = airportPerCity.find(path.at(i));
                auto i2 = airportPerCity.find(path.at(i + 1));
                cout << path.at(i) << ", " << i1->second.first << ", " << i1->second.second << " -> " << path.at(i + 1) << ", " << i2->second.first << ", " << i2->second.second;
                vector<string> comps= FlighAirline(path.at(i),path.at(i+1),vooscompanhia,companhias);
                if (comps.size()==0) goto noflighs;
                cout << " : " << comps[0];
                for (int i = 1; i < comps.size(); i++){
                    cout <<","<<comps[i];
                }
                cout<<endl;
            }

            cout<<"---------------------" << endl;
        }

    }
}
    if (!resultsfound){
        cout<< "Não existem voos a conectar " << partida << " e " << chegada;
        if (companhias.size()>0) cout<< " com "<<companhias.at(0)<<", ";
        for (int i=1;i<companhias.size();i++){
            cout<< companhias.at(i)<< ", ";
            return;
        }
    }


    posicaopartida = posicaochegada = false;
}

set<string> GestaoVoos::Find_Countries(string local){
    set<string> countries;
    for (pair<string, pair<string,string>> p: airportPerCity){
        if (local == p.first) {
            countries.insert("airport");
            return countries;
        }
        if (local == p.second.first) countries.insert(p.second.second);
    }
    return countries;
 }

 bool GestaoVoos::Find_Airlines(string airline){
     for (Airline ar : airlines){
         if (ar.getCode() == airline) return true;
     }
     cout << "\n " << airline << " is not a valid airline code.\n";
     return false;
 }

list<string> GestaoVoos::Find_Airports(double lat, double lng, double r){
     list<string> ans;
     for (pair<string,pair<string,string>> p : airports_lat_long){
         double temp_la = stod(p.second.first);
         double temp_lng = stod(p.second.second);

         double temp_lat = lat;
         double temp_lo = lng;


         double dLat = (temp_lat - temp_la) * M_PI / 180.0;
         double dLon = (temp_lo - temp_lng) * M_PI / 180.0;

         temp_la = (temp_la) * M_PI / 180.0;
         temp_lat = (temp_lat) * M_PI / 180.0;

         double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(temp_lat) * cos(temp_la);
         double rad = 6371;
         double c = 2 * asin(sqrt(a));
         if (rad * c <= r) ans.push_back(p.first);
     }
     return ans;
 }

vector<string> GestaoVoos::FlighAirline(string src, string dest, Graph voos,vector<string> companhias){
    vector<string> string_airlines;
    for (Graph::Node node:voos.getNodes()){
        if (src==node.src){
            for (Graph::Edge edge:node.adj){
                if (edge.dest==dest && companhias.size()==0) string_airlines.push_back(edge.airline);
                else if (edge.dest==dest && companhias.size()>1 && in(companhias,edge.airline))  string_airlines.push_back(edge.airline);
            }
        }
    }
    return string_airlines;
}


void GestaoVoos::getAirportInformation(string airportCode, int informationToGet, int max){
     set<string> string_airlines;
     set<pair<string,string>> toCities;
     set<string> fromCountries;
     set<string> fromCities;
     int numberFlights=0;

     if (informationToGet==8) cout<<"\n Pode chegar ate "<<airportCode<<" atraves de : \n\n";
     for (Graph::Node flight: mergedFligths.getNodes()){
         if (flight.src==airportCode){
             if (informationToGet==2) cout<<"\n Voos disponiveis a partir de "<<airportCode<<" : \n"<<endl;
             for (Graph::Edge edge: flight.adj){
                 auto it=airportPerCity.find(edge.dest);
                 toCities.insert(it->second);
                 numberFlights++;
                 if (informationToGet==2)cout<< " " << airportCode << " -> " << edge.dest<< " : " << edge.airline << endl;
                 string_airlines.insert(edge.airline);
             }

         }
         else{
             for (Graph::Edge edge: flight.adj){
                 if (edge.dest==airportCode){
                     auto it=airportPerCity.find(flight.src);
                     fromCountries.insert(it->second.second);
                     fromCities.insert(it->second.first);
                     if (informationToGet==8) cout<< " " << it->first << ", " << it->second.first<<", "<< it->second.second << endl;
                     break;
                 }
             }
         }

     }

     if (informationToGet==1 || informationToGet==2) cout<<"\n Numero de voos a partir de "<<airportCode<<" = "<<numberFlights;
     if (informationToGet==7 || informationToGet==8) cout<<"\n Pode chegar ate "<< airportCode<<" a partir de " <<fromCities.size()<<" cidades diferentes e "<<fromCountries.size()<<" paises diferentes";
     if (informationToGet==4){
         cout<<"\n A partir de "<<airportCode<<" pode ir ate : \n"<<endl;
         for (pair<string,string> city:toCities){
            cout<< " " << city.first<<", "<<city.second<<endl;
         }
     }

     if (informationToGet==4 || informationToGet==3) cout<<"\n A partir de "<<airportCode<<" pode chegar ate : "<<fromCities.size()<<" cidades diferentes";


     if (informationToGet==6){
         cout<<"\n Companhias aereas disponiveis a partir de "<<airportCode<<" : "<<endl;
         for (string airline:string_airlines){
             cout<< " " << airline<<", ";
             Airline temp_al = Airline(airline, " ", " ", " ");
             auto iter = airlines.find(temp_al);
             cout << iter->getName() << ", " << iter->getCountry() << endl;
         }
     }
     if (informationToGet==5 || informationToGet==6) {
         cout<<"\n Numero de companhias aereas disponiveis a partir de "<<airportCode<<" : "<<string_airlines.size();
     }

     if (informationToGet==9 || informationToGet==10){
        string v=max>1?" viagens":" viagem";
        set<string> airports=bfsWithMax(airportCode, mergedFligths,max);
        set<string> citiesWithMax;
        set<string> countriesWithMax;
        if (informationToGet==10) cout<<"\n Aeroportos alcancaveis com um maximo de "<<max<<v<<" :\n"<<endl;
        for (string airport: airports){
            auto it=airportPerCity.find(airport);
            citiesWithMax.insert(it->second.first);
            countriesWithMax.insert(it->second.second);
            if (informationToGet==10) cout<< " " << it->first<<", "<<it->second.first<<", "<<it->second.second<<endl;
        }
        cout<<"\n Com um maximo de "<<max<< v <<" e possivel atingir "<<airports.size()<<" aeroportos, "<< citiesWithMax.size()<<" cidades e "<<countriesWithMax.size()<<" paises.";
     }


 }

void GestaoVoos::getCountryInformation(string country, int informationToGet, int top){

    int countAirports=0;
    int countAirlines=0;
    int countFlightsFrom=0;
    int countFlightsTo=0;
    map<string,int> aeroportos;

    if (informationToGet==1|| informationToGet==2){
        if (informationToGet==2) cout<<"\n Aeroportos disponiveis em " << country << ": \n\n";
        for (pair<string,pair<string,string>> airport:airportPerCity){
            if (airport.second.second==country){
                countAirports++;
                aeroportos[airport.first]=0;
                if (informationToGet==2) cout<< " " << airport.first<<", "<<airport.second.first<<endl;
            }
        }
        cout<<"\n Em "<<country<<" existem "<<countAirports<<" aeroportos disponiveis";
    }
    else if (informationToGet==3||informationToGet==4){
        if (informationToGet==4) cout<<"\n Companhias de "<<country<<" : \n"<<endl;
        for (auto airline:airlines){
            if (airline.getCountry()==country) {
                if (informationToGet==4) cout<< " " << airline.getCode()<<", "<<airline.getName()<< ", " << airline.getCountry()<<endl;
                countAirlines++;
            }
        }
        cout<<"\n " << country<<" tem "<<countAirlines<<" companhias aereas";
    }

    else {

        if (informationToGet==6) cout<<"\n Voos a partir de "<<country<< " :\n";
        if (informationToGet == 8) cout << "\n Voos com destino a "<<country<< " :\n\n";

        for (Graph::Node node : mergedFligths.getNodes()){

            for (Graph::Edge edge:node.adj){

                auto itSrc=airportPerCity.find(node.src);
                auto itEdg=airportPerCity.find(edge.dest);

                if (itSrc->second.second==country){
                    aeroportos[node.src]+=1;
                    countFlightsFrom++;

                    if (informationToGet==6) cout<< " " << node.src<<", "<< itSrc->second.first << ", " << country<< " -> "<<edge.dest<<", "<<itEdg->second.first << ", " << itEdg->second.second << " : " << edge.airline << endl;

                }

                if (itEdg->second.second==country){

                    countFlightsTo++;
                    if (informationToGet==8) cout<< " " << node.src << ", "<< itSrc->second.second << " -> " << edge.dest << ", "<< country << " : " << edge.airline << endl;

                }

            }
        }

        if (informationToGet==5||informationToGet==6) cout<<"\n Existem "<<countFlightsFrom<<" voos de "<<country;

        else if (informationToGet==7||informationToGet==8) cout<<"\n Existem "<<countFlightsTo<<" voos para "<<country;
        else if (informationToGet==9){
            vector<pair<string, int> > vec;

            for (auto& it : aeroportos) {
                vec.push_back(it);
            }
            sort(vec.begin(),vec.end(),cmp);

            cout<<"\n Top "<<top<<" aeroportos em "<<country<<" com mais voos: \n"<<endl;
            for (int i=0;i<top & i < vec.size();i++){
                cout<< " " << i+1<<" - "<<vec.at(i).first<< ", " << airportPerCity[vec[i].first].first << ", " << airportPerCity[vec[i].first].second << endl;
            }
        }

    }

}

void GestaoVoos::getAirlineInformation(string comp, int informationToGet){

    for (auto it = airlines.begin(); it != airlines.end(); it++){
        if (it->getCode() == comp) goto search;
    }

    cout << "\n O codigo introduzido nao e valido";
    return;

    search:
    int countFlights=0;
    set<string> aeroportos;
    Graph airlineGraph;
    for (Graph voo: flights) {
        if (voo.getAirline() == comp) {
            airlineGraph = voo;
            break;
        }
    }


    if(informationToGet==4) cout<<"\n Viagens disponiveis com "<<comp<<" : "<<endl;

    for (auto node : airlineGraph.getNodes()){
        countFlights+=node.adj.size();
        for (auto edge:node.adj){
            if(informationToGet==4) cout<< " " << node.src<< ", " << airportPerCity[node.src].first<< ", " << airportPerCity[node.src].second <<" -> "<<edge.dest<< ", " << airportPerCity[edge.dest].first << ", " << airportPerCity[edge.dest].second <<endl;
            aeroportos.insert(edge.dest);
        }
    }
    if(informationToGet==3 || informationToGet==4) cout<<"\n Existem "<<countFlights<<" viagens disponiveis com "<<comp;
    if(informationToGet==1 || informationToGet==2){
        if(informationToGet==2) {
            cout << "\n Aeroportos alcancaveis com " << comp << " : \n" << endl;

            for (string aeroporto: aeroportos) {
                cout << " " << aeroporto << ", " << airportPerCity[aeroporto].first << ", " << airportPerCity[aeroporto].second << endl;
            }
        }
        cout<<"\n Existem "<<aeroportos.size()<<" aeroportos alcancaveis";
    }
    else if (informationToGet == 5) {
        int diameter = 0;

        for (Graph::Node node: airlineGraph.getNodes()) {
            int maxForCurrNode = bfsDiameter(node.src, airlineGraph);
            if (maxForCurrNode > diameter)
                diameter = maxForCurrNode;
        }

        cout << "\n O diametro da rede de voos da " << comp << " e " << diameter;
    }
    else if (informationToGet == 6){
        set<string> li = airlineGraph.articulationPoints();
        int count = 0;
        cout << "\n Aeroportos essenciais para as escalas da companhia " << comp << ":\n\n";
            for (string ap : li){
                for (Airport a : airports){
                    if (a.getCode() == ap){
                        count ++;
                        cout << " " << ap << ", " << a.getName() << endl;
                    }
                }
            }
            if (count == 1) cout << "\n Existe " << count << " aeroporto que serve como ponto de articulacao para a companhia " << comp;
            else cout << "\n Existem " << count << " aeroportos que servem como pontos de articulacao para a companhia " << comp;

    }


}

void GestaoVoos::getRedeGlobalInformation( int informationToGet, int top){

    map<string,int> aeroportos;

    if (informationToGet==2){
        for (Airport aeroporto : airports){
            aeroportos[aeroporto.getCode()]=0;
            cout<< " " << aeroporto.getCode()<<", "<<aeroporto.getName()<<endl;
        }
    }
    if (informationToGet==2||informationToGet==1) cout<<"\n Existem "<<airports.size()<<" aeroportos na rede global";
    if (informationToGet==6){
        for (Airline companhia : airlines){
            cout << " " << companhia.getCode( )<< ", "<< companhia.getName() << endl;
        }
    }
    if (informationToGet==6||informationToGet==5) cout<<"\n Existem "<<airlines.size()<<" companhias na rede global";
    else if (informationToGet==7){

        for (auto const flight : mergedFligths.getNodes()){
            aeroportos[flight.src] = flight.adj.size();
        }
        vector<pair<string, int> > vec;

        for (auto& it : aeroportos) {
            vec.push_back(it);
        }
        sort(vec.begin(),vec.end(),cmp);

        cout<<"\n Top "<<top<<" aeroportos na rede global com mais voos: \n"<<endl;
        for (int i=0;i<top & i < vec.size(); i++){
            cout<< " " << i+1<<" - "<<vec.at(i).first<< ", " << airportPerCity[vec[i].first].first << ", " << airportPerCity[vec[i].first].second << endl;
        }

    }
    if(informationToGet==4) cout<<"\n Viagens disponiveis: "<<endl;
    int countFlights;

    for (auto node : mergedFligths.getNodes()){
        countFlights+=node.adj.size();
        for (auto edge:node.adj){
            if(informationToGet==4) cout<< " " << node.src<< ", " << airportPerCity[node.src].first << ", " << airportPerCity[node.src].second << " -> "<<edge.dest<< ", " << airportPerCity[edge.dest].first << ", " << airportPerCity[edge.dest].second << " : " << edge.airline << endl;
        }
    }
    if(informationToGet==3 || informationToGet==4) cout<<"\n Existem "<<countFlights<<" viagens disponiveis";


}


bool GestaoVoos::cmp(pair<string, int>& a, pair<string, int>& b){
    return a.second>b.second;
}

bool GestaoVoos::in(vector<string> vec, string s){
    for (string str:vec){
        if (str==s) return true;
    }
    return false;
}

bool GestaoVoos::stringInVec(string str,vector<string> vec){
    for (auto s:vec){
        if (s==str) return true;
    }
    return false;
}

