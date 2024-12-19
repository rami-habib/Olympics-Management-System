#ifndef WET1_WINTER_COUNTRYINFO_H
#define WET1_WINTER_COUNTRYINFO_H

#include "AVLtree.h"
#include "wet1util.h"

class Country {

public:
    int countryId;
    int medals;
    int numOfContestants;
    int numOfTeams;
    //shared_ptr<Country> ptr;

    ~Country()=default;
    Country(int countryId, int medals) : countryId(countryId), medals(medals), numOfContestants(0), numOfTeams(0){
    }
};

 #endif