//
// Created by ahmad on 18/04/22.
//

#ifndef WET1_WINTER_INTOBJECT_H
#define WET1_WINTER_INTOBJECT_H
#include "iostream"


class intObject {
public:
    int num;

    intObject()
    {
        this->num = 0;
    }

     intObject(int num) : num(num) {}
     //  intObject(intObject& other)
    //   {
    //       other.num = this->num;
  //     }
    ~intObject() = default;

    bool operator>(intObject object)const {
        if (this->num > object.num)
            return true;

        return false;
    }

   explicit operator int()const{
        return num ;
    }

    bool operator<(intObject object) const {
        return !((*this) > object);
    }

    bool operator<=(intObject object) const {
        return (this->num) <= object.num;
    }


    bool operator==(const intObject object)const {

        return (this->num == object.num);
    }

    bool operator!=(intObject object)const {
        return !((*this) == object);
    }

    intObject &operator=(intObject  const& other)
    {
        if ((*this) == other)
            return (*this);

        this->num = other.num;
        return (*this);
    }

    friend std::ostream& operator<<(std::ostream& os, intObject const & object) {
        return os << object.num << std::endl;
    }


};



#endif //WET1_WINTER_INTOBJECT_H
