
#ifndef WET1_MODIFYKEY_H
#define WET1_MODIFYKEY_H

class ModifyKey{

public:

    int strength;
    int id;

    ModifyKey(int strength, int id): strength(strength),id(id){}
    ModifyKey(){
        strength=0;
        id=0;
    }
    ~ModifyKey()=default;

    bool operator<(const ModifyKey& other) const{
        if (this->strength == other.strength) {
            return id < other.id;
        }
        return strength < other.strength;
    }

    bool operator>(const ModifyKey& other) const{
        if (strength == other.strength) {
            return id > other.id;
        }
        return strength > other.strength;
    }

    bool operator==(const ModifyKey& other) const{
        return strength == other.strength && id == other.id;
    }
    bool operator!=(const ModifyKey& other) const{
        return !(*this == other);
    }





/*
    bool operator<(const ModifyKey& other) const{
        if(strength < other.strength) return true;
        if (strength > other.strength) return false;
        return (id < other.id);
    }
    bool operator>(const ModifyKey& other) const{
        //return (other < *(this));
        if(strength > other.strength) return true;
        if (strength < other.strength) return false;
        return (id > other.id);
    }
    bool operator==(const ModifyKey& other) const{
        return (id == other.id && strength==other.strength);
    }
    bool operator!=(const ModifyKey& other) const{
        return !(*this == other);
    }
*/
 /*   bool operator>(const ModifyKey& other) const{
        if(strength > other.strength)
        {
            return true;
        } else {
            if(strength < other.strength)
            {
                return false;
            }
            else {
                return id > other.id;
            }
        }
    }
    bool operator==(const ModifyKey& other) const{
        return (id == other.id);
    }
    bool operator!=(const ModifyKey& other) const{
        return ( id != other.id);
    }
*/
};

#endif //WET1_MODIFYKEY_H
