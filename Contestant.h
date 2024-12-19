   #ifndef WET1_WINTER_CONTESTANT_H
   #define WET1_WINTER_CONTESTANT_H

#include "AVLtree.h"
#include "wet1util.h"
#include "Country.h"
#include "ModifyKey.h"
#include "intObject.h"

class Contestant {

public:
    int contestId;
    Country* country ;
    Sport sport ;
    int strength;
    int* teams;
    ModifyKey modifyKey;
    intObject objectId;
    Contestant(int contestId,Country& country,Sport sport,int strength): contestId(contestId),country(&country),
      sport(sport),strength(strength),teams(new int[3]()){
        modifyKey = ModifyKey(strength,contestId);
        objectId = intObject(contestId);
    }

    Contestant(const Contestant& other){
        contestId = other.contestId;
        country = other.country ;
        sport = other.sport ;
        strength = other.strength ;
        modifyKey=other.modifyKey;
        objectId = other.objectId;
        int* temp= new int[3]() ;
       for(int i = 0 ; i < 3 ; i++){
          temp[i]=other.teams[i];
       }
       teams = temp ;
    }

    Contestant():contestId(0),country(nullptr),sport(Sport::BOULDERING),strength(0),teams(new int[3]()),modifyKey(0,0),objectId(contestId){

    }

    ~Contestant(){
       delete []teams;
     //  teams = nullptr;
    }

    //this function is O(1) because the array length is constant
    //it returns how many teams the contestant is playing for
    int howManyTeams() const{
        int count = 0 ;
        for(int i = 0 ; i < 3 ; i++){
            if(teams[i] != 0){
                count++;
            }
        }
        return count ;
    }
    //Contestant(const Contestant& other)= delete ;
    //Contestant operator=(const Contestant& other) = delete ;

    ModifyKey& getModifyKey() {
         return modifyKey;
    }
    intObject& getKey() {
         return objectId;
    }

};



#endif