#ifndef HW3_PAIR_HPP
#define HW3_PAIR_HPP

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Registers.hpp"

using namespace std;
///This is basically a way to connect a variable's name with it's type.
class TypedVar{

public:
    ///Fields
    int lineNum;
    string Id;
    string Type;
    registers reg;


    ///Methods
    TypedVar(){};
    TypedVar(string Id, string Type, int lineNum=0):Id(Id),Type(Type),lineNum(lineNum), reg(reg){};

    bool operator==(const TypedVar& other) const
    {
        return this->Type.compare(other.Type) != 0;
    }
    bool operator!=(const TypedVar& other) const
    {
        return (!(other==*this));
    }
};



#endif //HW3_PAIR_HPP
