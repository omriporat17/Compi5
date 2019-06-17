#ifndef HW3_PAIR_HPP
#define HW3_PAIR_HPP

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>


using namespace std;
///This is basically a way to connect a variable's name with it's type.

enum ari_op
{
    add_op,mul_op,sub_op,div_op,no_op
};

enum reg
{
    noRegister, $v0,$t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $t8, $t9
};

class TypedVar{

public:
    ///Fields
    int lineNum;
    string Id;
    string Type;
    reg regist;


    ///Methods
    TypedVar(){};
    TypedVar(string Id, string Type, int lineNum=0):Id(Id),Type(Type),lineNum(lineNum){};

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
