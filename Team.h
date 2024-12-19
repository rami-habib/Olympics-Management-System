#ifndef WET1_WINTER_TEAMINFO_H
#define WET1_WINTER_TEAMINFO_H

#include "AVLtree.h"
#include "wet1util.h"
#include "intObject.h"
#include "Contestant.h"
#include "ModifyKey.h"
#include "Olympicsa1.h"

class Team {

public:
    int teamId;
    Sport sport;
    int teamStrength;
    int numOfContestants;
    int maxTeamStrength;
    Country* country;
    //int firstMin,secondMin,thirdMin,firstMax,secondMax,thirdMax;
    AVL_Tree<intObject, Contestant> firstGroup_id;
    AVL_Tree<intObject, Contestant> secondGroup_id;
    AVL_Tree<intObject, Contestant> thirdGroup_id;
    AVL_Tree<ModifyKey, Contestant> firstGroup_strength;
    AVL_Tree<ModifyKey, Contestant> secondGroup_strength;
    AVL_Tree<ModifyKey, Contestant> thirdGroup_strength;

    Team(int teamId, Country &country, Sport sport) : teamId(teamId),sport(sport),teamStrength(0),numOfContestants(0),maxTeamStrength(0), country(&country),
          firstGroup_id(), secondGroup_id(),thirdGroup_id(), firstGroup_strength(),secondGroup_strength(), thirdGroup_strength() {}

    void updateSize() {
        numOfContestants = firstGroup_id.getSize() + secondGroup_id.getSize() + thirdGroup_id.getSize();
    }

   void numModulo3is0AfterAdding(){
       if(firstGroup_id.getSize() == secondGroup_id.getSize() && secondGroup_id.getSize() == thirdGroup_id.getSize()){
           return;
       } else{
           if(firstGroup_id.getSize()==(numOfContestants/3)+1 && secondGroup_id.getSize()==(numOfContestants/3) && thirdGroup_id.getSize()==(numOfContestants/3)-1){
               Contestant temp1=*(firstGroup_id.getMax()->data);
               secondGroup_id.insert(temp1.getKey(),temp1);
               secondGroup_strength.insert(temp1.getModifyKey(),temp1);
               firstGroup_id.remove(temp1.getKey());
               firstGroup_strength.remove(temp1.getModifyKey());

               Contestant temp2=*(secondGroup_id.getMax()->data);
               thirdGroup_id.insert(temp2.getKey(),temp2);
               thirdGroup_strength.insert(temp2.getModifyKey(),temp2);
               secondGroup_id.remove(temp2.getKey());
               secondGroup_strength.remove(temp2.getModifyKey());
               return;
           } else if(firstGroup_id.getSize()==(numOfContestants/3) && secondGroup_id.getSize()==(numOfContestants/3)+1 && thirdGroup_id.getSize()==(numOfContestants/3)-1){
                   Contestant temp=*(secondGroup_id.getMax()->data);
                   thirdGroup_id.insert(temp.getKey(),temp);
                   thirdGroup_strength.insert(temp.getModifyKey(),temp);
                   secondGroup_id.remove(temp.getKey());
                   secondGroup_strength.remove(temp.getModifyKey());
               }

       }

   }
    void numModulo3is1AfterAdding(){
        if(firstGroup_id.getSize()==(numOfContestants/3)+1 && secondGroup_id.getSize() == thirdGroup_id.getSize()){
            return;
        } else {
            if(secondGroup_id.getSize()==(numOfContestants/3)+1 && firstGroup_id.getSize() == thirdGroup_id.getSize()){
                Contestant temp=*(secondGroup_id.getMin()->data);
                firstGroup_id.insert(temp.getKey(),temp);
                firstGroup_strength.insert(temp.getModifyKey(),temp);
                secondGroup_id.remove(temp.getKey());
                secondGroup_strength.remove(temp.getModifyKey());
            } else {
                if(thirdGroup_id.getSize()==(numOfContestants/3)+1 && firstGroup_id.getSize() == secondGroup_id.getSize()){
                    Contestant temp1=*(thirdGroup_id.getMin()->data);
                    secondGroup_id.insert(temp1.getKey(),temp1);
                    secondGroup_strength.insert(temp1.getModifyKey(),temp1);
                    thirdGroup_id.remove(temp1.getKey());
                    thirdGroup_strength.remove(temp1.getModifyKey());

                    Contestant temp2=*(secondGroup_id.getMin()->data);
                    firstGroup_id.insert(temp2.getKey(),temp2);
                    firstGroup_strength.insert(temp2.getModifyKey(),temp2);
                    secondGroup_id.remove(temp2.getKey());
                    secondGroup_strength.remove(temp2.getModifyKey());
                }
            }
        }


    }
    void numModulo3is2AfterAdding(){
        if(firstGroup_id.getSize() == (numOfContestants/3)+1 && secondGroup_id.getSize() == (numOfContestants/3)+1 && thirdGroup_id.getSize() == (numOfContestants/3)){
            return;
        } else {
            if(firstGroup_id.getSize() == (numOfContestants/3)+2 && secondGroup_id.getSize() == thirdGroup_id.getSize()){
                Contestant temp=*(firstGroup_id.getMax()->data);
                secondGroup_id.insert(temp.getKey(),temp);
                secondGroup_strength.insert(temp.getModifyKey(),temp);
                firstGroup_id.remove(temp.getKey());
                firstGroup_strength.remove(temp.getModifyKey());
            } else {
                if(firstGroup_id.getSize() == thirdGroup_id.getSize() &&  secondGroup_id.getSize() == (numOfContestants/3)){
                    Contestant temp=*(thirdGroup_id.getMin()->data);
                    secondGroup_id.insert(temp.getKey(),temp);
                    secondGroup_strength.insert(temp.getModifyKey(),temp);
                    thirdGroup_id.remove(temp.getKey());
                    thirdGroup_strength.remove(temp.getModifyKey());
                }
            }
        }
    }
    void balanceTreesAfterAdding(){
       updateSize();
        if(numOfContestants % 3 == 0) numModulo3is0AfterAdding();
        if(numOfContestants % 3 == 1) numModulo3is1AfterAdding();
        if(numOfContestants % 3 == 2) numModulo3is2AfterAdding();
    }
    void addContestantAux(Contestant &contestant) {
        if (contestant.contestId > secondGroup_id.getMax()->data->contestId) {
            thirdGroup_id.insert(contestant.getKey(), contestant);
            thirdGroup_strength.insert(contestant.getModifyKey(), contestant);
        } else {
            if (contestant.contestId > firstGroup_id.getMax()->data->contestId) {
                secondGroup_id.insert(contestant.getKey(), contestant);
                secondGroup_strength.insert(contestant.getModifyKey(), contestant);
            } else {
                firstGroup_id.insert(contestant.getKey(), contestant);
                firstGroup_strength.insert(contestant.getModifyKey(), contestant);
            }
        }
        updateSize();  //////////
        balanceTreesAfterAdding();
    }

    void addContestant(Contestant contestant) {
        if (numOfContestants == 0) {
            firstGroup_id.insert(contestant.objectId, contestant);
            firstGroup_strength.insert(contestant.modifyKey, contestant);
        }
        if (numOfContestants == 1) {
            if (firstGroup_id.getMax() != nullptr && contestant.contestId < firstGroup_id.getMax()->data->contestId) {
                Contestant temp = *(firstGroup_id.getMax()->data);
                firstGroup_id.remove(temp.objectId);
                firstGroup_strength.remove(temp.modifyKey);
                firstGroup_id.insert(contestant.objectId, contestant);
                firstGroup_strength.insert(contestant.modifyKey, contestant);
                secondGroup_id.insert(temp.objectId, temp);
                secondGroup_strength.insert(temp.modifyKey, temp);

            } else if (firstGroup_id.getMax() != nullptr && contestant.contestId >= firstGroup_id.getMax()->data->contestId) {
                secondGroup_id.insert(contestant.objectId, contestant);
                secondGroup_strength.insert(contestant.modifyKey, contestant);

            } else if (secondGroup_id.getMax() != nullptr && contestant.contestId >= secondGroup_id.getMax()->data->contestId) {
                thirdGroup_id.insert(contestant.objectId, contestant);
                thirdGroup_strength.insert(contestant.modifyKey, contestant);

            } else if (secondGroup_id.getMax() != nullptr && contestant.contestId < secondGroup_id.getMax()->data->contestId) {
                firstGroup_id.insert(contestant.objectId, contestant);
                firstGroup_strength.insert(contestant.modifyKey, contestant);

            } else if (thirdGroup_id.getMax() != nullptr && contestant.contestId <= thirdGroup_id.getMax()->data->contestId) {
                secondGroup_id.insert(contestant.objectId, contestant);
                secondGroup_strength.insert(contestant.modifyKey, contestant);

            } else if (thirdGroup_id.getMax() != nullptr && contestant.contestId > thirdGroup_id.getMax()->data->contestId) {
                Contestant temp = *(thirdGroup_id.getMin()->data);
                thirdGroup_id.remove(temp.objectId);
                thirdGroup_strength.remove(temp.modifyKey);
                secondGroup_id.insert(temp.objectId, temp);
                secondGroup_strength.insert(temp.modifyKey, temp);
                thirdGroup_id.insert(contestant.objectId, contestant);
                thirdGroup_strength.insert(contestant.modifyKey, contestant);

            }
        } else if (numOfContestants == 2) {
            if(firstGroup_id.getSize()==2){
                if(contestant.contestId >= firstGroup_id.getMax()->data->contestId){
                    Contestant temp = *(firstGroup_id.getMax()->data);
                    firstGroup_id.remove(temp.objectId);
                    firstGroup_strength.remove(temp.modifyKey);
                    secondGroup_id.insert(temp.objectId,temp);
                    secondGroup_strength.insert(temp.modifyKey,temp);
                    thirdGroup_id.insert(contestant.objectId,contestant);
                    thirdGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId < firstGroup_id.getMax()->data->contestId && contestant.contestId >= firstGroup_id.getMin()->data->contestId ){
                    Contestant temp = *(firstGroup_id.getMax()->data);
                    firstGroup_id.remove(temp.objectId);
                    firstGroup_strength.remove(temp.modifyKey);
                    thirdGroup_id.insert(temp.objectId,temp);
                    thirdGroup_strength.insert(temp.modifyKey,temp);
                    secondGroup_id.insert(contestant.objectId,contestant);
                    secondGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId <= firstGroup_id.getMin()->data->contestId){
                    Contestant temp = *(firstGroup_id.getMax()->data);
                    Contestant min = *(firstGroup_id.getMin()->data);
                    firstGroup_id.remove(temp.objectId);
                    firstGroup_strength.remove(temp.modifyKey);
                    thirdGroup_id.insert(temp.objectId,temp);
                    thirdGroup_strength.insert(temp.modifyKey,temp);
                    firstGroup_id.remove(min.objectId);
                    firstGroup_strength.remove(min.modifyKey);
                    secondGroup_id.insert(min.objectId,min);
                    secondGroup_strength.insert(min.modifyKey,min);
                    firstGroup_id.insert(contestant.objectId,contestant);
                    firstGroup_strength.insert(contestant.modifyKey,contestant);
                }
            }
            else if(secondGroup_id.getSize()==2){
                if(contestant.contestId >= secondGroup_id.getMax()->data->contestId){
                    Contestant min = *(secondGroup_id.getMin()->data);
                    thirdGroup_id.insert(contestant.objectId,contestant);
                    thirdGroup_strength.insert(contestant.modifyKey,contestant);
                    secondGroup_id.remove(min.objectId);
                    secondGroup_strength.remove(min.modifyKey);
                    firstGroup_id.insert(min.objectId,min);
                    firstGroup_strength.insert(min.modifyKey,min);
                }
                else if(contestant.contestId <= secondGroup_id.getMin()->data->contestId){
                    Contestant temp = *(secondGroup_id.getMax()->data);
                    firstGroup_id.insert(contestant.objectId,contestant);
                    firstGroup_strength.insert(contestant.modifyKey,contestant);
                    secondGroup_id.remove(temp.objectId);
                    secondGroup_strength.remove(temp.modifyKey);
                    thirdGroup_id.insert(temp.objectId,temp);
                    thirdGroup_strength.insert(temp.modifyKey,temp);
                }
                else if(contestant.contestId < secondGroup_id.getMax()->data->contestId && contestant.contestId >= secondGroup_id.getMin()->data->contestId){
                    Contestant max = *(secondGroup_id.getMax()->data);
                    Contestant min = *(secondGroup_id.getMin()->data);
                    secondGroup_id.remove(max.objectId);
                    secondGroup_strength.remove(max.modifyKey);
                    secondGroup_id.remove(min.objectId);
                    secondGroup_strength.remove(min.modifyKey);
                    secondGroup_id.insert(contestant.objectId,contestant);
                    secondGroup_strength.insert(contestant.modifyKey,contestant);
                    firstGroup_id.insert(min.objectId,min);
                    firstGroup_strength.insert(min.modifyKey,min);
                    thirdGroup_id.insert(max.objectId,max);
                    thirdGroup_strength.insert(max.modifyKey,max);
                }
            }
            else if(thirdGroup_id.getSize() == 2){
                if(contestant.contestId >= thirdGroup_id.getMax()->data->contestId){
                    Contestant max = *(thirdGroup_id.getMax()->data);
                    Contestant min = *(thirdGroup_id.getMin()->data);
                    thirdGroup_id.remove(max.objectId);
                    thirdGroup_strength.remove(max.modifyKey);
                    thirdGroup_id.remove(min.objectId);
                    thirdGroup_strength.remove(min.modifyKey);
                    thirdGroup_id.insert(contestant.objectId,contestant);
                    thirdGroup_strength.insert(contestant.modifyKey,contestant);
                    firstGroup_id.insert(min.objectId,min);
                    firstGroup_strength.insert(min.modifyKey,min);
                    secondGroup_id.insert(max.objectId,max);
                    secondGroup_strength.insert(max.modifyKey,max);
                }
                else if(contestant.contestId <= thirdGroup_id.getMin()->data->contestId){
                    firstGroup_id.insert(contestant.objectId,contestant);
                    firstGroup_strength.insert(contestant.modifyKey,contestant);
                    Contestant temp = *(thirdGroup_id.getMin()->data);
                    thirdGroup_id.remove(temp.objectId);
                    thirdGroup_strength.remove(temp.modifyKey);
                    secondGroup_id.insert(temp.objectId,temp);
                    secondGroup_strength.insert(temp.modifyKey,temp);

                }
                else if(contestant.contestId > thirdGroup_id.getMin()->data->contestId){ // so its also smaller than the max because otherwise we would not be here
                    Contestant temp = *(thirdGroup_id.getMin()->data);
                    thirdGroup_id.remove(temp.objectId);
                    thirdGroup_strength.remove(temp.modifyKey);
                    firstGroup_id.insert(temp.objectId,temp);
                    firstGroup_strength.insert(temp.modifyKey,temp);
                    secondGroup_id.insert(contestant.objectId,contestant);
                    secondGroup_strength.insert(contestant.modifyKey,contestant);
                }
            }
            else if(firstGroup_id.getMax() == nullptr){
                if(contestant.contestId <= secondGroup_id.getMin()->data->contestId){
                    firstGroup_id.insert(contestant.objectId,contestant);
                    firstGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId >= thirdGroup_id.getMax()->data->contestId){
                    Contestant from_sec = *(secondGroup_id.getMax()->data);
                    Contestant from_Third = *(thirdGroup_id.getMax()->data);
                    secondGroup_id.remove(from_sec.objectId);
                    secondGroup_strength.remove(from_sec.modifyKey);
                    firstGroup_id.insert(from_sec.objectId,from_sec);
                    firstGroup_strength.insert(from_sec.modifyKey,from_sec);
                    thirdGroup_id.remove(from_Third.objectId);
                    thirdGroup_strength.remove(from_Third.modifyKey);
                    secondGroup_id.insert(from_Third.objectId,from_Third);
                    secondGroup_strength.insert(from_Third.modifyKey,from_Third);
                    thirdGroup_id.insert(contestant.objectId,contestant);
                    thirdGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId > secondGroup_id.getMin()->data->contestId){ // so it's also smaller than the max because otherwise we would not be here
                    Contestant temp = *(secondGroup_id.getMin()->data);
                    secondGroup_id.remove(temp.objectId);
                    secondGroup_strength.remove(temp.modifyKey);
                    secondGroup_id.insert(contestant.objectId,contestant);
                    secondGroup_strength.insert(contestant.modifyKey,contestant);
                    firstGroup_id.insert(temp.objectId,temp);
                    firstGroup_strength.insert(temp.modifyKey,temp);
                }
            }
            else if(secondGroup_id.getSize() == 0){
                if(contestant.contestId <= thirdGroup_id.getRoot()->data->contestId && contestant.contestId >= firstGroup_id.getRoot()->data->contestId){
                    secondGroup_id.insert(contestant.objectId , contestant);
                    secondGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId >= thirdGroup_id.getRoot()->data->contestId){
                    Contestant temp =*(thirdGroup_id.getRoot()->data);
                    thirdGroup_id.remove(temp.objectId);
                    thirdGroup_strength.remove(temp.modifyKey);
                    secondGroup_id.insert(temp.objectId,temp);
                    secondGroup_strength.insert(temp.modifyKey,temp);
                    thirdGroup_id.insert(contestant.objectId,contestant);
                    thirdGroup_strength.insert(contestant.modifyKey,contestant);
                }
                else if(contestant.contestId <= firstGroup_id.getRoot()->data->contestId){
                    Contestant temp =*(firstGroup_id.getRoot()->data);
                    firstGroup_id.remove(temp.objectId);
                    firstGroup_strength.remove(temp.modifyKey);
                    secondGroup_id.insert(temp.objectId,temp);
                    secondGroup_strength.insert(temp.modifyKey,temp);
                    firstGroup_id.insert(contestant.objectId,contestant);
                    firstGroup_strength.insert(contestant.modifyKey,contestant);
                }
            }
            else if(thirdGroup_id.getSize() == 0){
               if(contestant.contestId >= secondGroup_id.getRoot()->data->contestId){
                   thirdGroup_id.insert(contestant.objectId,contestant);
                   thirdGroup_strength.insert(contestant.modifyKey,contestant);
               }
               else if(contestant.contestId <= firstGroup_id.getRoot()->data->contestId){
                   Contestant from_Sec = *(secondGroup_id.getRoot()->data);
                   Contestant from_first = *(firstGroup_id.getRoot()->data);
                   secondGroup_id.remove(from_Sec.objectId);
                   secondGroup_strength.remove(from_Sec.modifyKey);
                   thirdGroup_id.insert(from_Sec.objectId,from_Sec);
                   thirdGroup_strength.insert(from_Sec.modifyKey,from_Sec);
                   firstGroup_id.remove(from_first.objectId);
                   firstGroup_strength.remove(from_first.modifyKey);
                   secondGroup_id.insert(from_first.objectId,from_first);
                   secondGroup_strength.insert(from_first.modifyKey,from_first);
                   firstGroup_id.insert(contestant.objectId,contestant);
                   firstGroup_strength.insert(contestant.modifyKey,contestant);
               }
               else{
                   Contestant temp = *(secondGroup_id.getRoot()->data);
                   secondGroup_id.remove(temp.objectId);
                   secondGroup_strength.remove(temp.modifyKey);
                   secondGroup_id.insert(contestant.objectId,contestant);
                   secondGroup_strength.insert(contestant.modifyKey,contestant);
                   thirdGroup_id.insert(temp.objectId,temp);
                   thirdGroup_strength.insert(temp.modifyKey,temp);
               }
           }
        }
        else if (numOfContestants >= 3){
        addContestantAux(contestant);
    }
   // numOfContestants++;

   // balanceTreesAfterAdding();
   updateSize();

    modifyStrength();
    modifyMaxStrength();
    }
    ~Team()=default ;

    void modifyStrength() {
        if (numOfContestants % 3 != 0) {
            teamStrength = 0;
        } else if (firstGroup_strength.getSize() != 0 && secondGroup_strength.getSize() != 0 &&
                   thirdGroup_strength.getSize() != 0) {
            teamStrength = firstGroup_strength.getMax()->data->strength + secondGroup_strength.getMax()->data->strength +
                    thirdGroup_strength.getMax()->data->strength;
        }
    }


    int removeThreeFromFirstTree(){
        if(firstGroup_id.getSize() <3)
            return 0;
        Contestant removed1=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed1.objectId);
        firstGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=(*(firstGroup_strength.getMin()->data));
        firstGroup_id.remove(removed2.objectId);
        firstGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed3.objectId);
        firstGroup_strength.remove(removed3.modifyKey);

        Contestant temp1=*(secondGroup_id.getMin()->data);
        secondGroup_id.remove(temp1.objectId);
        secondGroup_strength.remove(temp1.modifyKey);
        firstGroup_id.insert(temp1.objectId,temp1);
        firstGroup_strength.insert(temp1.modifyKey,temp1);

        Contestant temp2=*(secondGroup_id.getMin()->data);
        secondGroup_id.remove(temp2.objectId);
        secondGroup_strength.remove(temp2.modifyKey);
        firstGroup_id.insert(temp2.objectId,temp2);
        firstGroup_strength.insert(temp2.modifyKey,temp2);

        Contestant temp3=*(thirdGroup_id.getMin()->data);
        thirdGroup_id.remove(temp3.objectId);
        thirdGroup_strength.remove(temp3.modifyKey);
        secondGroup_id.insert(temp3.objectId,temp3);
        secondGroup_strength.insert(temp3.modifyKey,temp3);
        int strength= firstGroup_strength.getMax()->data->strength + secondGroup_strength.getMax()->data->strength + thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp1.objectId,temp1);
        secondGroup_strength.insert(temp1.modifyKey,temp1);
        secondGroup_id.insert(temp2.objectId,temp2);
        secondGroup_strength.insert(temp2.modifyKey,temp2);
        firstGroup_id.remove(temp1.objectId);
        firstGroup_strength.remove(temp1.modifyKey);
        firstGroup_id.remove(temp2.objectId);
        firstGroup_strength.remove(temp2.modifyKey);
        thirdGroup_id.insert(temp3.objectId,temp3);
        thirdGroup_strength.insert(temp3.modifyKey,temp3);
        secondGroup_id.remove(temp3.objectId);
        secondGroup_strength.remove(temp3.modifyKey);
        firstGroup_id.insert(removed1.objectId,removed1);
        firstGroup_id.insert(removed2.objectId,removed2);
        firstGroup_id.insert(removed3.objectId,removed3);
        firstGroup_strength.insert(removed1.modifyKey,removed1);
        firstGroup_strength.insert(removed2.modifyKey,removed2);
        firstGroup_strength.insert(removed3.modifyKey,removed3);
        return strength;
    }

    int removeThreeFromSecondTree(){
        if(secondGroup_id.getSize() <3){
            return 0;
        }
        Contestant removed1=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed1.objectId);
        secondGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed2.objectId);
        secondGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed3.objectId);
        secondGroup_strength.remove(removed3.modifyKey);

        Contestant temp1=*(firstGroup_id.getMax()->data);
        secondGroup_id.insert(temp1.objectId,temp1);
        secondGroup_strength.insert(temp1.modifyKey,temp1);
        firstGroup_id.remove(temp1.objectId);
        firstGroup_strength.remove(temp1.modifyKey);

        Contestant temp2=*(thirdGroup_id.getMin()->data);
        secondGroup_id.insert(temp2.objectId,temp2);
        secondGroup_strength.insert(temp2.modifyKey,temp2);
        thirdGroup_id.remove(temp2.objectId);
        thirdGroup_strength.remove(temp2.modifyKey);

        int strength= firstGroup_strength.getMax()->data->strength + secondGroup_strength.getMax()->data->strength + thirdGroup_strength.getMax()->data->strength;

        firstGroup_id.insert(temp1.objectId,temp1);
        firstGroup_strength.insert(temp1.modifyKey,temp1);
        secondGroup_id.remove(temp1.objectId);
        secondGroup_strength.remove(temp1.modifyKey);

        thirdGroup_id.insert(temp2.objectId,temp2);
        thirdGroup_strength.insert(temp2.modifyKey,temp2);
        secondGroup_id.remove(temp2.objectId);
        secondGroup_strength.remove(temp2.modifyKey);

        secondGroup_id.insert(removed1.objectId,removed1);
        secondGroup_strength.insert(removed1.modifyKey,removed1);
        secondGroup_id.insert(removed2.objectId,removed2);
        secondGroup_strength.insert(removed2.modifyKey,removed2);
        secondGroup_id.insert(removed3.objectId,removed3);
        secondGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int  removeThreeFromThirdTree(){
        if(thirdGroup_id.getSize()<3){
            return 0;
        }
        Contestant removed1=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed1.objectId);
        thirdGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed2.objectId);
        thirdGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed3.objectId);
        thirdGroup_strength.remove(removed3.modifyKey);

        Contestant temp1=*(secondGroup_id.getMax()->data);
        thirdGroup_id.insert(temp1.objectId,temp1);
        thirdGroup_strength.insert(temp1.modifyKey,temp1);
        secondGroup_id.remove(temp1.objectId);
        secondGroup_strength.remove(temp1.modifyKey);

        Contestant temp2=*(secondGroup_id.getMax()->data);
        thirdGroup_id.insert(temp2.objectId,temp2);
        thirdGroup_strength.insert(temp2.modifyKey,temp2);
        secondGroup_id.remove(temp2.objectId);
        secondGroup_strength.remove(temp2.modifyKey);

        Contestant temp3=*(firstGroup_id.getMax()->data);
        secondGroup_id.insert(temp3.objectId,temp3);
        secondGroup_strength.insert(temp3.modifyKey,temp3);
        firstGroup_id.remove(temp3.objectId);
        firstGroup_strength.remove(temp3.modifyKey);

        int strength= firstGroup_strength.getMax()->data->strength + secondGroup_strength.getMax()->data->strength + thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp1.objectId,temp1);
        secondGroup_strength.insert(temp1.modifyKey,temp1);
        thirdGroup_id.remove(temp1.objectId);
        thirdGroup_strength.remove(temp1.modifyKey);

        secondGroup_id.insert(temp2.objectId,temp2);
        secondGroup_strength.insert(temp2.modifyKey,temp2);
        thirdGroup_id.remove(temp2.objectId);
        thirdGroup_strength.remove(temp2.modifyKey);

        firstGroup_id.insert(temp3.objectId,temp3);
        firstGroup_strength.insert(temp3.modifyKey,temp3);
        secondGroup_id.remove(temp3.objectId);
        secondGroup_strength.remove(temp3.modifyKey);

        thirdGroup_id.insert(removed1.objectId,removed1);
        thirdGroup_strength.insert(removed1.modifyKey,removed1);
        thirdGroup_id.insert(removed2.objectId,removed2);
        thirdGroup_strength.insert(removed2.modifyKey,removed2);
        thirdGroup_id.insert(removed3.objectId,removed3);
        thirdGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromFirstTreeAndOneFromSecondTree(){
        if(firstGroup_id.getSize() <2 || secondGroup_id.getSize() <1){
            return 0;
        }
        Contestant removed1=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed1.objectId);
        firstGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed2.objectId);
        firstGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed3.objectId);
        secondGroup_strength.remove(removed3.modifyKey);

        Contestant temp1=*(secondGroup_id.getMin()->data);
        secondGroup_id.remove(temp1.objectId);
        secondGroup_strength.remove(temp1.modifyKey);
        firstGroup_id.insert(temp1.objectId,temp1);
        firstGroup_strength.insert(temp1.modifyKey,temp1);

        Contestant temp2=*(thirdGroup_id.getMin()->data);
        thirdGroup_id.remove(temp2.objectId);
        thirdGroup_strength.remove(temp2.modifyKey);
        secondGroup_id.insert(temp2.objectId,temp2);
        secondGroup_strength.insert(temp2.modifyKey,temp2);

        int strength=firstGroup_strength.getMax()->data->strength+secondGroup_strength.getMax()->data->strength+thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp1.objectId,temp1);
        secondGroup_strength.insert(temp1.modifyKey,temp1);
        firstGroup_id.remove(temp1.objectId);
        firstGroup_strength.remove(temp1.modifyKey);

        thirdGroup_id.insert(temp2.objectId,temp2);
        thirdGroup_strength.insert(temp2.modifyKey,temp2);
        secondGroup_id.remove(temp2.objectId);
        secondGroup_strength.remove(temp2.modifyKey);

        firstGroup_id.insert(removed1.objectId,removed1);
        firstGroup_strength.insert(removed1.modifyKey,removed1);
        firstGroup_id.insert(removed2.objectId,removed2);
        firstGroup_strength.insert(removed2.modifyKey,removed2);
        secondGroup_id.insert(removed3.objectId,removed3);
        secondGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromFirstTreeAndOneFromThirdTree(){
        if(firstGroup_id.getSize() <2 || thirdGroup_id.getSize() <1){
            return 0;
        }
        Contestant removed1=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed1.objectId);
        firstGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed2.objectId);
        firstGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed3.objectId);
        thirdGroup_strength.remove(removed3.modifyKey);

        Contestant temp=*(secondGroup_id.getMin()->data);
        firstGroup_id.insert(temp.objectId,temp);
        firstGroup_strength.insert(temp.modifyKey,temp);
        secondGroup_id.remove(temp.objectId);
        secondGroup_strength.remove(temp.modifyKey);

        int strength=firstGroup_strength.getMax()->data->strength + secondGroup_strength.getMax()->data->strength + thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp.objectId,temp);
        secondGroup_strength.insert(temp.modifyKey,temp);
        firstGroup_id.remove(temp.objectId);
        firstGroup_strength.remove(temp.modifyKey);

        firstGroup_id.insert(removed1.objectId,removed1);
        firstGroup_strength.insert(removed1.modifyKey,removed1);
        firstGroup_id.insert(removed2.objectId,removed2);
        firstGroup_strength.insert(removed2.modifyKey,removed2);
        thirdGroup_id.insert(removed3.objectId,removed3);
        thirdGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromSecondTreeAndOneFromThirdTree(){
        if(secondGroup_id.getSize()<2 || thirdGroup_id.getSize() <1){
            return 0;
        }
        Contestant removed1=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed1.objectId);
        secondGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed2.objectId);
        secondGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed3.objectId);
        thirdGroup_strength.remove(removed3.modifyKey);

        Contestant temp=*(firstGroup_id.getMax()->data);
        firstGroup_id.remove(temp.objectId);
        firstGroup_strength.remove(temp.modifyKey);
        secondGroup_id.insert(temp.objectId,temp);
        secondGroup_strength.insert(temp.modifyKey,temp);

        int strength=firstGroup_strength.getMax()->data->strength+secondGroup_strength.getMax()->data->strength+thirdGroup_strength.getMax()->data->strength;

        firstGroup_id.insert(temp.objectId,temp);
        firstGroup_strength.insert(temp.modifyKey,temp);
        secondGroup_id.remove(temp.objectId);
        secondGroup_strength.remove(temp.modifyKey);

        secondGroup_id.insert(removed1.objectId,removed1);
        secondGroup_strength.insert(removed1.modifyKey,removed1);
        secondGroup_id.insert(removed2.objectId,removed2);
        secondGroup_strength.insert(removed2.modifyKey,removed2);
        thirdGroup_id.insert(removed3.objectId,removed3);
        thirdGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromSecondTreeAndOneFromFirstTree(){
        if(secondGroup_id.getSize()<2 || firstGroup_id.getSize()<1){
            return 0;
        }
        Contestant removed1=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed1.objectId);
        secondGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed2.objectId);
        secondGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed3.objectId);
        firstGroup_strength.remove(removed3.modifyKey);

        Contestant temp=*(thirdGroup_id.getMin()->data);
        secondGroup_id.insert(temp.objectId,temp);
        secondGroup_strength.insert(temp.modifyKey,temp);
        thirdGroup_id.remove(temp.objectId);
        thirdGroup_strength.remove(temp.modifyKey);

        int strength=firstGroup_strength.getMax()->data->strength+secondGroup_strength.getMax()->data->strength+thirdGroup_strength.getMax()->data->strength;

        thirdGroup_id.insert(temp.objectId,temp);
        thirdGroup_strength.insert(temp.modifyKey,temp);
        secondGroup_id.remove(temp.objectId);
        secondGroup_strength.remove(temp.modifyKey);

        secondGroup_id.insert(removed1.objectId,removed1);
        secondGroup_strength.insert(removed1.modifyKey,removed1);
        secondGroup_id.insert(removed2.objectId,removed2);
        secondGroup_strength.insert(removed2.modifyKey,removed2);
        firstGroup_id.insert(removed3.objectId,removed3);
        firstGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromThirdTreeAndOneFromSecondTree(){
        if(thirdGroup_id.getSize() <2 || secondGroup_id.getSize() <1){
            return 0;
        }
        Contestant removed1=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed1.objectId);
        thirdGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed2.objectId);
        thirdGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(secondGroup_strength.getMin()->data);
        secondGroup_id.remove(removed3.objectId);
        secondGroup_strength.remove(removed3.modifyKey);

        Contestant temp1=*(secondGroup_id.getMax()->data);
        thirdGroup_id.insert(temp1.objectId,temp1);
        thirdGroup_strength.insert(temp1.modifyKey,temp1);
        secondGroup_id.remove(temp1.objectId);
        secondGroup_strength.remove(temp1.modifyKey);

        Contestant temp2=*(firstGroup_id.getMax()->data);
        secondGroup_id.insert(temp2.objectId,temp2);
        secondGroup_strength.insert(temp2.modifyKey,temp2);
        firstGroup_id.remove(temp2.objectId);
        firstGroup_strength.remove(temp2.modifyKey);

        int strength=firstGroup_strength.getMax()->data->strength+secondGroup_strength.getMax()->data->strength+thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp1.objectId,temp1);
        secondGroup_strength.insert(temp1.modifyKey,temp1);
        thirdGroup_id.remove(temp1.objectId);
        thirdGroup_strength.remove(temp1.modifyKey);

        firstGroup_id.insert(temp2.objectId,temp2);
        firstGroup_strength.insert(temp2.modifyKey,temp2);
        secondGroup_id.remove(temp2.objectId);
        secondGroup_strength.remove(temp2.modifyKey);


        thirdGroup_id.insert(removed1.objectId,removed1);
        thirdGroup_strength.insert(removed1.modifyKey,removed1);
        thirdGroup_id.insert(removed2.objectId,removed2);
        thirdGroup_strength.insert(removed2.modifyKey,removed2);
        secondGroup_id.insert(removed3.objectId,removed3);
        secondGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    int removeTwoFromThirdTreeAndOneFromFirstTree(){
        if(thirdGroup_id.getSize() < 2 || firstGroup_id.getSize() <1){
            return 0;
        }
        Contestant removed1=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed1.objectId);
        thirdGroup_strength.remove(removed1.modifyKey);
        Contestant removed2=*(thirdGroup_strength.getMin()->data);
        thirdGroup_id.remove(removed2.objectId);
        thirdGroup_strength.remove(removed2.modifyKey);
        Contestant removed3=*(firstGroup_strength.getMin()->data);
        firstGroup_id.remove(removed3.objectId);
        firstGroup_strength.remove(removed3.modifyKey);


        Contestant temp=*(secondGroup_id.getMax()->data);
        thirdGroup_id.insert(temp.objectId,temp);
        thirdGroup_strength.insert(temp.modifyKey,temp);
        secondGroup_id.remove(temp.objectId);
        secondGroup_strength.remove(temp.modifyKey);

        int strength=firstGroup_strength.getMax()->data->strength+secondGroup_strength.getMax()->data->strength+thirdGroup_strength.getMax()->data->strength;

        secondGroup_id.insert(temp.objectId,temp);
        secondGroup_strength.insert(temp.modifyKey,temp);
        thirdGroup_id.remove(temp.objectId);
        thirdGroup_strength.remove(temp.modifyKey);


        thirdGroup_id.insert(removed1.objectId,removed1);
        thirdGroup_strength.insert(removed1.modifyKey,removed1);
        thirdGroup_id.insert(removed2.objectId,removed2);
        thirdGroup_strength.insert(removed2.modifyKey,removed2);
        firstGroup_id.insert(removed3.objectId,removed3);
        firstGroup_strength.insert(removed3.modifyKey,removed3);

        return strength;
    }

    void modifyMaxStrength()
    {
        if(numOfContestants <=3 || numOfContestants % 3 != 0) {
            maxTeamStrength = 0;
            return;
        }
        else{
        int max=teamStrength;
        max=(max<removeThreeFromFirstTree())?removeThreeFromFirstTree():max;
        max=(max<removeThreeFromSecondTree())?removeThreeFromSecondTree():max;
        max=(max<removeThreeFromThirdTree())?removeThreeFromThirdTree():max;
        max=(max<removeTwoFromFirstTreeAndOneFromSecondTree())?removeTwoFromFirstTreeAndOneFromSecondTree():max;
        max=(max<removeTwoFromFirstTreeAndOneFromThirdTree())?removeTwoFromFirstTreeAndOneFromThirdTree():max;
        max=(max<removeTwoFromSecondTreeAndOneFromThirdTree())?removeTwoFromSecondTreeAndOneFromThirdTree():max;
        max=(max<removeTwoFromSecondTreeAndOneFromThirdTree())?removeTwoFromSecondTreeAndOneFromThirdTree():max;
        max=(max<removeTwoFromSecondTreeAndOneFromFirstTree())?removeTwoFromSecondTreeAndOneFromFirstTree():max;
        max=(max<removeTwoFromThirdTreeAndOneFromSecondTree())?removeTwoFromThirdTreeAndOneFromSecondTree():max;
        max=(max<removeTwoFromThirdTreeAndOneFromFirstTree())?removeTwoFromThirdTreeAndOneFromFirstTree():max;

        maxTeamStrength=max;
        }
    }

    void numModulo3is0AfterDeleting(Contestant &contestant){
        if(firstGroup_id.find(contestant.getKey()) != nullptr){
            firstGroup_id.remove(contestant.getKey());
            firstGroup_strength.remove(contestant.getModifyKey());
        } else {
            if(secondGroup_id.find(contestant.getKey()) != nullptr){
                secondGroup_id.remove(contestant.getKey());
                secondGroup_strength.remove(contestant.getModifyKey());

                Contestant temp=*(firstGroup_id.getMax()->data);
                secondGroup_id.insert(temp.getKey(),temp);
                secondGroup_strength.insert(temp.getModifyKey(),temp);
                firstGroup_id.remove(temp.getKey());
                firstGroup_strength.remove(temp.getModifyKey());
            } else {
                if(thirdGroup_id.find(contestant.getKey()) != nullptr){
                    thirdGroup_id.remove(contestant.getKey());
                    thirdGroup_strength.remove(contestant.getModifyKey());

                    Contestant temp1=*(firstGroup_id.getMax()->data);
                    secondGroup_id.insert(temp1.getKey(),temp1);
                    secondGroup_strength.insert(temp1.getModifyKey(),temp1);
                    firstGroup_id.remove(temp1.getKey());
                    firstGroup_strength.remove(temp1.getModifyKey());

                    Contestant temp2=*(secondGroup_id.getMax()->data);
                    thirdGroup_id.insert(temp2.getKey(),temp2);
                    thirdGroup_strength.insert(temp2.getModifyKey(),temp2);
                    secondGroup_id.remove(temp2.getKey());
                    secondGroup_strength.remove(temp2.getModifyKey());
                }
            }
        }

    }
    void numModulo3is1AfterDeleting(Contestant &contestant){
        if(firstGroup_id.find(contestant.getKey()) != nullptr){
            firstGroup_id.remove(contestant.getKey());
            firstGroup_strength.remove(contestant.getModifyKey());

            Contestant temp=*(secondGroup_id.getMin()->data);
            firstGroup_id.insert(temp.getKey(),temp);
            firstGroup_strength.insert(temp.getModifyKey(),temp);
            secondGroup_id.remove(temp.getKey());
            secondGroup_strength.remove(temp.getModifyKey());
        } else {
            if(thirdGroup_id.find(contestant.getKey()) != nullptr){
                thirdGroup_id.remove(contestant.getKey());
                thirdGroup_strength.remove(contestant.getModifyKey());

                Contestant temp=*(secondGroup_id.getMax()->data);
                thirdGroup_id.insert(temp.getKey(),temp);
                thirdGroup_strength.insert(temp.getModifyKey(),temp);
                secondGroup_id.remove(temp.getKey());
                secondGroup_strength.remove(temp.getModifyKey());
            } else {
                if(secondGroup_id.find(contestant.getKey()) != nullptr){
                    secondGroup_id.remove(contestant.getKey());
                    secondGroup_strength.remove(contestant.getModifyKey());
                }
            }

        }
    }
    void numModulo3is2AfterDeleting(Contestant &contestant){
        if(firstGroup_id.find(contestant.getKey()) != nullptr){
            firstGroup_id.remove(contestant.getKey());
            firstGroup_strength.remove(contestant.getModifyKey());

            Contestant temp1=*(secondGroup_id.getMin()->data);
            firstGroup_id.insert(temp1.getKey(),temp1);
            firstGroup_strength.insert(temp1.getModifyKey(),temp1);
            secondGroup_id.remove(temp1.getKey());
            secondGroup_strength.remove(temp1.getModifyKey());

            Contestant temp2=*(thirdGroup_id.getMin()->data);
            secondGroup_id.insert(temp2.getKey(),temp2);
            secondGroup_strength.insert(temp2.getModifyKey(),temp2);
            thirdGroup_id.remove(temp2.getKey());
            thirdGroup_strength.remove(temp2.getModifyKey());
        } else {
            if(secondGroup_id.find(contestant.getKey()) != nullptr){
                secondGroup_id.remove(contestant.getKey());
                secondGroup_strength.remove(contestant.getModifyKey());

                Contestant temp=*(thirdGroup_id.getMin()->data);
                secondGroup_id.insert(temp.getKey(),temp);
                secondGroup_strength.insert(temp.getModifyKey(),temp);
                thirdGroup_id.remove(temp.getKey());
                thirdGroup_strength.remove(temp.getModifyKey());
            } else {
                if(thirdGroup_id.find(contestant.getKey()) != nullptr){
                    thirdGroup_id.remove(contestant.getKey());
                    thirdGroup_strength.remove(contestant.getModifyKey());
                }
            }
        }
    }
    void removeContestantAux(Contestant &contestant){
        if(numOfContestants % 3 == 0) numModulo3is0AfterDeleting(contestant);
        if(numOfContestants % 3 == 1) numModulo3is1AfterDeleting(contestant);
        if(numOfContestants % 3 == 2) numModulo3is2AfterDeleting(contestant);
    }
    void removeContestant(Contestant &contestant){
        for (int i = 0; i < 3; ++i) {
            if(contestant.teams[i] == teamId)
                contestant.teams[i]=0;
        }
        numOfContestants --;
        removeContestantAux(contestant);
        modifyStrength();
        modifyMaxStrength();
    }
};

#endif