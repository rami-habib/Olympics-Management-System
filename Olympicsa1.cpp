#include "Olympicsa1.h"
#include "wet1util.h"


Olympics::Olympics(){
   allCountries = AVL_Tree<intObject,Country>();
   allTeams = AVL_Tree<intObject,Team>();
   allContestants = AVL_Tree<intObject,Contestant>();
}

Olympics::~Olympics(){
    //deleteDeep(allTeams);
}
	
StatusType Olympics::add_country(int countryId, int medals){
    intObject c_id(countryId);
    intObject c_medals(medals);
    Country new_country = Country(countryId , medals);
    if(medals < 0 || countryId <= 0){
        return StatusType::INVALID_INPUT ;
    }
    if(allCountries.find(c_id) == nullptr){
        try{
            allCountries.insert(c_id , new_country);
            return StatusType::SUCCESS;
        }catch (bad_alloc&){
            return StatusType::ALLOCATION_ERROR ;
        }
    }
	return StatusType::FAILURE;
}
	
StatusType Olympics::remove_country(int countryId){
    intObject c_id(countryId);
    if(countryId <= 0 ){
        return StatusType::INVALID_INPUT ;
    }
    if(allCountries.find(c_id) == nullptr) {
        return StatusType::FAILURE ;
    }
    int numOfContestants = allCountries.find(c_id)->data->numOfContestants ;
    int numOfTeams = allCountries.find(c_id)->data->numOfTeams ;
    if( numOfTeams > 0 || numOfContestants >0)
    {
        return StatusType::FAILURE ;
    }
    if(numOfTeams == 0 && numOfContestants == 0){
        try {
            allCountries.remove(c_id);
        }catch (bad_alloc&){
            return StatusType::ALLOCATION_ERROR ;
        }

        return StatusType::SUCCESS ;
    }
	return StatusType::FAILURE;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    intObject c_id = intObject(countryId);
    intObject t_id = intObject(teamId);
    if( countryId <= 0 || teamId <= 0){
        return StatusType::INVALID_INPUT ;
    }
    if(allCountries.find(c_id) == nullptr || allTeams.find(t_id) != nullptr){
        return StatusType::FAILURE ;
    }
    //Country* addTo = allCountries.find(c_id)->data;
    //shared_ptr<Country> addToCountry (allCountries.find(c_id)->data);
    Country& addToCountry=*(allCountries.find(c_id)->data);
    Team newTeam = Team(teamId , addToCountry , sport);
    try{
        allTeams.insert(t_id,newTeam);
        addToCountry.numOfTeams++;
        return StatusType::SUCCESS ;
    }catch(bad_alloc&){
        return StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::FAILURE;
}

StatusType Olympics::remove_team(int teamId){
    intObject t_id = intObject(teamId);
    if(teamId <= 0){
        return StatusType::INVALID_INPUT ;
    }
    if(allTeams.find(t_id) == nullptr){
        return StatusType::FAILURE ;
    }
    if(allTeams.find(t_id)->data->numOfContestants > 0){
        return StatusType::FAILURE ;
    }
    //shared_ptr<Country>* toRemoveFrom = new shared_ptr<Country>(allTeams.find(t_id)->data->country);
    Country& toRemoveFrom=*(allTeams.find(t_id)->data->country);
    try {
        allTeams.remove(t_id);
        toRemoveFrom.numOfTeams--;
        return StatusType::SUCCESS ;
    }catch (bad_alloc&){
        return  StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::FAILURE;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    intObject contest_id = intObject(contestantId);
    intObject country_id = intObject(countryId);
    if(contestantId <= 0 || countryId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT ;
    }
    if(allContestants.find(contest_id) != nullptr || allCountries.find(country_id) == nullptr){
        return StatusType::FAILURE ;
    }
    //shared_ptr<Country> add_to_country (allCountries.find(country_id)->data) ;
    Country& add_to_country=*(allCountries.find(country_id)->data);
    Contestant new_contestant = Contestant(contestantId,add_to_country,sport , strength);
    try{
        allContestants.insert(contest_id,new_contestant);
        add_to_country.numOfContestants++;
        return StatusType::SUCCESS ;
    }catch (bad_alloc&){
        return StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::FAILURE;
}
	
StatusType Olympics::remove_contestant(int contestantId){
    intObject contest_id = intObject(contestantId);
    if(contestantId <= 0 ){
        return StatusType::INVALID_INPUT ;
    }
    if(allContestants.find(contest_id) == nullptr || ((allContestants.find(contest_id)->data->howManyTeams()) > 0)){
        return StatusType::FAILURE ;
    }
    //shared_ptr<Country>* toRemoveFrom = new shared_ptr<Country>(allContestants.find(contest_id)->data->country);
    Country& toRemoveFrom=*(allContestants.find(contest_id)->data->country);
    try {
        allContestants.remove(contest_id);
        toRemoveFrom.numOfContestants--;
        return  StatusType::SUCCESS ;

    }catch (bad_alloc&){

        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::FAILURE;
}
	
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if(teamId <= 0 || contestantId <= 0) return StatusType::INVALID_INPUT;
    intObject contestantKey(contestantId),teamKey(teamId);
    if(allTeams.find(teamKey)== nullptr || allContestants.find(contestantKey)== nullptr){
        return StatusType::FAILURE;
    }
    Contestant& contestantTemp = *(allContestants.find(contestantKey)->data);
    Team& teamTemp=*(allTeams.find(teamKey)->data);
    bool checker= true;
    bool alreadyExist = false ;
    for (int i = 0; i < 3; i++) {
        if(contestantTemp.teams[i] == 0) {
            checker = false;
        }
        if(contestantTemp.teams[i] == teamId){
            alreadyExist = true ;
        }
    }
    if(contestantTemp.country->countryId != teamTemp.country->countryId || contestantTemp.sport != teamTemp.sport || checker || alreadyExist)
        return StatusType::FAILURE;

    //teamTemp.addContestant(contestantTemp);
    for (int i = 0; i < 3; i++) {
        if (contestantTemp.teams[i] == 0) {
            contestantTemp.teams[i] = teamId;
            break;
        }
    }
    teamTemp.addContestant(contestantTemp);
    teamTemp.updateSize();
  //  teamTemp.modifyStrength();
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    if(teamId <= 0 || contestantId <= 0) return StatusType::INVALID_INPUT;
    intObject contestantKey(contestantId),teamKey(teamId);
    GNode<intObject,Contestant>* contestantTemp=allContestants.find(contestantKey);
    GNode<intObject,Team>* teamTemp=allTeams.find(teamKey);
    if(contestantTemp == nullptr || teamTemp == nullptr) return StatusType::FAILURE;
    bool checker= true;
    for (int i = 0; i < 3; ++i) {
        if(contestantTemp->data->teams[i] == teamId)
            checker= false;
    }
    if(checker) return StatusType::FAILURE;
    teamTemp->data->removeContestant(*(contestantTemp->data));
    return StatusType::SUCCESS;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    if(contestantId <= 0 ){
        return StatusType::INVALID_INPUT ;
    }
    intObject key(contestantId);
    if(allContestants.find(key) == nullptr || ((allContestants.find(key)->data->strength)+change) < 0){
        return StatusType::FAILURE ;
    }
    Contestant temp = *(allContestants.find(key)->data);
    int* teams=new int[3];
    for (int i = 0; i < 3; ++i) {
       teams[i]=temp.teams[i];
       try {
           intObject t= intObject((teams[i]));
           if(t>0) {
               remove_contestant_from_team(teams[i], temp.contestId);
           }
       }catch (bad_alloc&){
           return StatusType::ALLOCATION_ERROR ;
       }
    }
    allContestants.find(key)->data->strength += change ;
    allContestants.find(key)->data->modifyKey.strength += change ;
    temp.strength += change;
    temp.modifyKey.strength += change;
    for (int i = 0; i < 3; ++i){
        try {
            intObject t= intObject((teams[i]));
            if(t>0) {
                add_contestant_to_team(teams[i], temp.contestId);
                //allTeams.find(t)->data->modifyStrength();
            }

        }catch (bad_alloc&){
            delete[] teams;
            return StatusType::ALLOCATION_ERROR ;
        }
    }
    delete[] teams;
    return StatusType::SUCCESS ;

	//return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId){

    intObject c_id = intObject(contestantId);
    if(contestantId <= 0){
        return {StatusType::INVALID_INPUT};
    }
    if(allContestants.find(c_id) == nullptr){
        return {StatusType::FAILURE};
    }
    return {allContestants.find(c_id)->data->strength};


}

output_t<int> Olympics::get_medals(int countryId){

    intObject country_id = intObject(countryId);
    if(countryId <= 0){
        return {StatusType::INVALID_INPUT};
    }
    if(allCountries.find(country_id) == nullptr){
        return {StatusType::FAILURE};
    }
    return {allCountries.find(country_id)->data->medals};

	return 0;
}

output_t<int> Olympics::get_team_strength(int teamId){
    if(teamId <= 0){

        return {StatusType::INVALID_INPUT};
    }
    intObject t_id = intObject(teamId);

    if(allTeams.find(t_id) == nullptr){

        return {StatusType::FAILURE};
    }
   // allTeams.find(t_id)->data->modifyStrength();
    return {allTeams.find(t_id)->data->teamStrength};
	return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){

    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    intObject t_id1 = intObject(teamId1);
    intObject t_id2 = intObject(teamId2);
    GNode<intObject,Team>* team1=allTeams.find(t_id1),*team2=allTeams.find(t_id2);
    if(team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }
    if(team1->data->sport != team2->data->sport || team1->data->country->countryId != team2->data->country->countryId){
        return StatusType::FAILURE ;
    }
    if(team2->data->numOfContestants == 0){// already United because there are no players in team2 to move to team1
        // team2->data->country->numOfTeams --;   //////////////////////////////////////////////////////////////
        remove_team(teamId2);
        return StatusType::SUCCESS;
    }

    auto* arr_key1=new intObject[team2->data->firstGroup_id.getSize()];
    auto* arr_key2=new intObject[team2->data->secondGroup_id.getSize()];
    auto* arr_key3=new intObject[team2->data->secondGroup_id.getSize()];
    int counter1=0,counter2=0,counter3=0;
    int* ct1=&counter1, *ct2=&counter2 ,*ct3=&counter3;
    team2->data->firstGroup_id.TreeKey_to_array(team2->data->firstGroup_id.getRoot(),arr_key1,ct1);
    team2->data->secondGroup_id.TreeKey_to_array(team2->data->secondGroup_id.getRoot(),arr_key2,ct2);
    team2->data->thirdGroup_id.TreeKey_to_array(team2->data->thirdGroup_id.getRoot(),arr_key3,ct3);

    for (int i = 0; i < *ct1; ++i) {
        remove_contestant_from_team(teamId2,int (arr_key1[i]));
        add_contestant_to_team(teamId1,int (arr_key1[i]));
    }
    for (int i = 0; i < *ct2; ++i) {
        remove_contestant_from_team(teamId2,int (arr_key2[i]));
        add_contestant_to_team(teamId1,int (arr_key2[i]));
    }
    for (int i = 0; i < *ct3; ++i) {
        remove_contestant_from_team(teamId2,int (arr_key3[i]));
        add_contestant_to_team(teamId1,int (arr_key3[i]));
    }
    team2->data->numOfContestants=0;
    remove_team(teamId2);
    delete [] arr_key1;
    delete [] arr_key2;
    delete [] arr_key3;
    return StatusType::SUCCESS;

}

StatusType Olympics::play_match(int teamId1,int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }

    intObject t_id1 = intObject(teamId1);
    intObject t_id2 = intObject(teamId2);

    if(allTeams.find(t_id1) == nullptr || allTeams.find(t_id2) == nullptr){
        return StatusType::FAILURE;
    }
    if(allTeams.find(t_id1)->data->sport != allTeams.find(t_id2)->data->sport){
        return StatusType::FAILURE ;
    }
    int team1_score = get_team_strength(teamId1).ans() + allTeams.find(t_id1)->data->country->medals;
    int team2_score = get_team_strength(teamId2).ans() + allTeams.find(t_id2)->data->country->medals;
    if(team1_score == team2_score){
        return StatusType::SUCCESS ;
    }
    if(team1_score > team2_score){
        (allTeams.find(t_id1)->data->country->medals)++;
        return  StatusType::SUCCESS ;
    }
    if(team1_score < team2_score){
        (allTeams.find(t_id2)->data->country->medals)++;
        return  StatusType::SUCCESS ;
    }
	return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    intObject t_id = intObject(teamId);
    if(allTeams.find(t_id) == nullptr || allTeams.find(t_id)->data->numOfContestants < 3){
        return StatusType::FAILURE;
    }
    //allTeams.find(t_id)->data->modifyMaxStrength();
    return allTeams.find(t_id)->data->maxTeamStrength;
}


