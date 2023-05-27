//
// Created by Lara Bastos on 26/12/2022.
//

#ifndef UNTITLED3_GESTAOVOOS_H
#define UNTITLED3_GESTAOVOOS_H
#include <iostream>
#include "Airport.h"
#include "Airline.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include "Graph.h"
#include <set>


using namespace std;

class GestaoVoos {
private:
    /// Hash table with Airport code and a pair with Airport city and country
    unordered_map<string, pair<string,string>> airportPerCity;
    /// Hash table with Airport code and a pair with Airport latitude and longitude
    unordered_map<string, pair<string,string>> airports_lat_long;
    /// Set with all airports
    set<Airport> airports;
    /// Set with all airlines
    set<Airline> airlines;
    /// Vector with all flights associated with a different Airline Graph
    vector<Graph> flights;
    /// Graph with every single flight of all airlines
    Graph mergedFligths;
    /// bool values to check departure position and arrival position
    bool posicaopartida = false, posicaochegada = false;
    /// radius used in Haversine formula
    double radPartida, radChegada;

public:
    /// default constructor
    GestaoVoos()=default;
    /// set posicaodepartida to true
    void setPosicaopartida(){posicaopartida = true;}
    /// set posicaodechegada to true
    void setPosicaochegada(){posicaochegada = true;}
    /// set radPartida to given radius
    /// \param rad radius on departure
    void setRadPartida(string rad){this->radPartida = stod(rad);}
    /// set radChegada to given radius
    /// \param rad radius on arrival
    void setRadChegada(string rad){this->radChegada = stod(rad);}
    /// reads the csv files and creates de necessary objects
    ///
    /// O(n^2)
    /// \param path path of file
    void LerFicheiros(string path);
    /// given the departure and arrival coordinates it searches for the best/shortest path between the two using the airports of the net we built
    /// if given a list of airlines with will filter that search using only edges/connections belonging to that airlines
    ///
    /// O(n^2)
    /// \param partida departure coordinates
    /// \param chegada arrival coordinates
    /// \param companhia airlines vector to filter path
    void MelhorViagem(string partida, string chegada, vector<string> companhia);
    /// Breadth-first Search
    ///
    /// O(|E| + |V|)
    /// \param airport starting Airport Node
    /// \param airlinegraph Graph associated with specific airline
    /// \param aeroportochegada arrival airport code
    /// \param companhia airlines vector to filter path
    /// \return vector with path of nodes from starting airport to arrival airport
    vector<Graph::Node> bfs(Graph::Node airport, Graph airlinegraph,string aeroportochegada, vector<string> companhia);
    /// Finds shortest distance from given airport source and destination with given graph and filtered airlines
    ///
    /// O(n^2)
    /// \param src airport node source
    /// \param dest expected destination
    /// \param airlinegraph specific airline graph
    /// \param companhia airlines vector to filter path
    /// \return vector of string with path with shortest distance
    vector<string> findShortestDistance( Graph::Node src, string dest, Graph airlinegraph,vector<string> companhia);
    /// search in airportPerCity for the country given a spot
    ///
    /// O(n)
    /// \param local string of request spot (city or airport)
    /// \return set with all countries found
    set<string> Find_Countries(string local);
    /// search in airlines for the given airline code
    ///
    /// O(n)
    /// \param airline airline code
    /// \return bool value true if found false if not
    bool Find_Airlines(string airline);
    /// Find airports using Haversine Formula
    ///
    /// O(n)
    /// \param lat latitude
    /// \param lng longitude
    /// \param r radius
    /// \return list of all airports found
    list<string> Find_Airports(double lat, double lng, double r);
    /// return all airlines that have edges that connect the source to the destination
    ///
    /// O(n^2)
    /// \param src source
    /// \param dest destination
    /// \param voos specific graph with flights
    /// \param companhias vector with airlines
    /// \return vector with found airlines
    vector<string> FlighAirline(string src, string dest, Graph voos,vector<string> companhias);
    /// prints on the screen useful information about a certain airport
    ///
    /// O(n^2)
    /// \param airportCode Airport code
    /// \param informationToGet number representing an option selected
    /// \param max max number of flights
    void getAirportInformation(string airportCode, int informationToGet, int max = 0);
    /// Breadth-First Search with an additional parameter that is max number of flights
    ///
    /// O(|E| + |V|)
    /// \param airport starting airport
    /// \param airlinegraph specific airline graph
    /// \param max max number of flights
    /// \return set of strings with path of the bfs
    set<string> bfsWithMax(string airport, Graph airlinegraph, int max);
    /// prints on the screen useful information about a certain country
    ///
    /// O(n^2)
    /// \param country country name
    /// \param informationToGet number representing an option selected
    /// \param top number of airports you want to obtain
    void getCountryInformation(string country, int informationToGet, int top = 0);
    /// prints on the screen useful information about a certain airline
    ///
    /// O(n^2)
    /// \param airline airline code
    /// \param informationToGet number representing an option selected
    void getAirlineInformation(string airline, int informationToGet);
    /// compare function of two pairs
    ///
    /// O(1)
    /// \param a pair a
    /// \param b pair b
    /// \return comparison bool
    static bool cmp(pair<string, int>& a, pair<string, int>& b);
    /// finds diameter of graph using bfs
    ///
    /// O(n(|E| + |V|))
    /// \param airport starting airport
    /// \param airlinegraph specific airline graph
    /// \return diameter found
    int bfsDiameter(string airport, Graph airlinegraph);
    /// prints on the screen useful information about the global net of flights
    ///
    /// O(n^2)
    /// \param informationToGet number representing an option selected
    /// \param top number of airports you want to obtain
    void getRedeGlobalInformation(int informationToGet, int top = 0);
    /// search to see if given string is in given vector
    ///
    /// O(n)
    /// \param vec given vector
    /// \param s given string
    /// \return true if found else false
    bool in(vector<string> vec, string s);
    /// search to see if given string is in given vector
    ///
    /// O(n)
    /// \param vec given vector
    /// \param s given string
    /// \return true if found else false
    bool stringInVec(string str,vector<string> vec);

};


#endif //UNTITLED3_GESTAOVOOS_H
