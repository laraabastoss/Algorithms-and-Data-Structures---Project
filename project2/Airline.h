//
// Created by Lara Bastos on 26/12/2022.
//

#ifndef UNTITLED3_AIRLINE_H
#define UNTITLED3_AIRLINE_H
#include <string>
using namespace std;

class Airline {
private:
    /// Airline code, name, country and it's callsign
    string code, name,country, callsign;

public:
    /// creates an Airline with the given code, name, country, callsign
    /// \param code airline code
    /// \param name airline name
    /// \param country airline country
    /// \param callsign airline callsign
    Airline(string code, string name, string country, string callsign):code(code), name(name), country(country),callsign(callsign){}
    ///
    /// \return Airline code
    string getCode() const;
    ///
    /// \return Airline name
    string getName() const;
    ///
    /// \return Airline callsign
    string getCallSign() const;
    ///
    /// \return Airline country
    string getCountry() const;
    /// override of the '<' operator for class Airline
    bool operator<(const Airline airline) const{
        return code<airline.code;
    }
    /// override of the '==' operator for class Airline
    bool operator==(const Airline airline) const{
        return code == airline.code;
    }

};


#endif //UNTITLED3_AIRLINE_H
