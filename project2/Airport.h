//
// Created by Lara Bastos on 26/12/2022.
//

#ifndef UNTITLED3_AIRPORT_H
#define UNTITLED3_AIRPORT_H
#include <string>
using namespace std;

class Airport {
private:
    /// Airport code, name, city , country , latitude coordinates and longitude coordinates
    string code, name, city, country, latitude, longitude;
public:
    /// default airport constructor
    Airport() = default;
    /// creates an Airport with the given code, name, country, city, latitude and longitude
    /// \param code Airport code
    /// \param name Airport name
    /// \param country Airport country
    /// \param city Airport city
    /// \param latitude Airport latitude
    /// \param longitude Airport longitude
    Airport(string code, string name, string country, string city, string latitude, string longitude):code(code), name(name), country(country),city(city),latitude(latitude), longitude(longitude){}
    ///
    /// \return Airport code
    string getCode();
    ///
    /// \return Airport name
    string getName();
    ///
    /// \return Airport city
    string getCity();
    ///
    /// \return Aiport country
    string getCountry();
    ///
    /// \return Airport latitude
    string getLatitude();
    ///
    /// \return Airport longitude
    string getLongitude();
    /// override of the '<' operator for class Airport
    bool operator<(const Airport airport) const{
        return code<airport.code;
    }
    /// override of the '==' operator for class Airport
    bool operator == (const Airport airport) const{
        return code == airport.code;
    }
};


#endif //UNTITLED3_AIRPORT_H
