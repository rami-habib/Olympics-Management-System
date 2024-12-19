//
// 234218 Data Structures 1.
// Semester: 2024A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_
#include "AVLtree.h"
#include "intObject.h"
#include "Contestant.h"
#include "wet1util.h"
#include "Country.h"
#include "Team.h"

class Olympics {
private:
   AVL_Tree<intObject,Contestant> allContestants;
   AVL_Tree<intObject,Team> allTeams ;
   AVL_Tree<intObject,Country> allCountries ;

   void deleteDeep(AVL_Tree<intObject,Team>& root){
       if(root.getRoot() != nullptr){
          root.getRoot()->data->firstGroup_id.treeClear();
          root.getRoot()->data->secondGroup_id.treeClear();
          root.getRoot()->data->thirdGroup_id.treeClear();
          root.getRoot()->data->firstGroup_strength.treeClear();
          root.getRoot()->data->secondGroup_strength.treeClear();
          root.getRoot()->data->thirdGroup_strength.treeClear();
          root.remove(*(root.getRoot()->key));
           deleteDeep(root);
       }
   }

public:
    // <DO-NOT-MODIFY> {

    Olympics();

    virtual ~Olympics();

    StatusType add_country(int countryId, int medals);

    StatusType remove_country(int countryId);

    StatusType add_team(int teamId,int countryId,Sport sport);

    StatusType remove_team(int teamId);

    StatusType add_contestant(int contestantId ,int countryId,Sport sport,int strength);

    StatusType remove_contestant(int contestantId);

    StatusType add_contestant_to_team(int teamId,int contestantId);

    StatusType remove_contestant_from_team(int teamId,int contestantId);

    StatusType update_contestant_strength(int contestantId ,int change);

    output_t<int> get_strength(int contestantId);

    output_t<int> get_medals(int countryId);

    output_t<int> get_team_strength(int teamId);

    StatusType unite_teams(int teamId1,int teamId2);

    StatusType play_match(int teamId1,int teamId2);

    output_t<int> austerity_measures(int teamId);

    // } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
