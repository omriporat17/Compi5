//
// Created by omri on 19/05/2019.
//

#ifndef COMPI3_STACKSTRUCT_H
#define COMPI3_STACKSTRUCT_H

#include "Pair.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

enum types
{
    IntType,BoolType,ByteType,VoidType,StringType,UndefinedType
};



static string typeToString(types types1)
{
    if(types1==IntType) {
        return "INT";
    }
    if(types1==BoolType)
    {
        return "BOOL";
    }
    if(types1==ByteType)
    {
        return "BYTE";
    }
    if(types1==VoidType)
    {
        return "VOID";
    }
    if(types1==StringType)
    {
        return "STRING";
    }
    return "undefined";
}

static types stringToType(string string1)
{
    if(string1=="INT"){ return IntType;}
    if(string1=="BOOL") { return BoolType;}
    if(string1=="BYTE") { return ByteType;}
    if(string1=="VOID") { return VoidType;}
    if(string1=="STRING") { return StringType;}
    return UndefinedType;
}
static string ari_to_string(ari_op op1)
{
    if(op1==add_op)
    {
        return "add";
    }
    if(op1==sub_op)
    {
        return "sub";
    }
    if(op1==mul_op)
    {
        return "mul";
    }
    if(op1==div_op)
    {
        return "div";
    }
    return "";

}
static string reg_to_string(reg register1)
{
    if(register1==noRegister)
    {
        return "";
    }
    if(register1==$t0)
    {
        return "$t0";
    }
    if(register1==$t1)
    {
        return "$t1";
    }
    if(register1==$t2)
    {
        return "$t2";
    }
    if(register1==$t3)
    {
        return "$t3";
    }
    if(register1==$t4)
    {
        return "$t4";
    }
    if(register1==$t5)
    {
        return "$t5";
    }
    if(register1==$t6)
    {
        return "$t6";
    }
    if(register1==$t7)
    {
        return "$t7";
    }
    if(register1==$t8)
    {
        return "$t8";
    }
    if(register1==$t9)
    {
        return "$t9";
    }
    if(register1==$v0)
    {
        return "$v0";
    }
    if(register1==$s0)
    {
        return "$s0";
    }
    if(register1==$s1)
    {
        return "$s1";
    }
    if(register1==$s2)
    {
        return "$s2";
    }
    if(register1==$s3)
    {
        return "$s3";
    }
    if(register1==$s4)
    {
        return "$s4";
    }
    if(register1==$s5)
    {
        return "$s5";
    }
    if(register1==$s6)
    {
        return "$s6";
    }
    if(register1==$s7)
    {
        return "$s7";
    }
    return "";

}

static bool isTypesEqual(string Type1, string Type2)
{
    if(Type1==typeToString(IntType) && Type2==typeToString(ByteType))///because we have cast between byte and int
    {
        return true;
    }
    return Type1==Type2;
}

struct StackType
{
private:

    vector<int> trueList;
    vector<int> falseList;
    vector<int> continueList;
    vector<int> breakList;
    vector<int> nextList;
public:
    int lineNum;
    types type;
    string str;
    vector<TypedVar> func_info;
    reg regist;
    ari_op oper;
    StackType(types type=UndefinedType, string str=""): type(type), str(str), lineNum(1),func_info(){}
    StackType(ari_op op,types type=IntType, string str="" ):  oper(op),type(type), str(str), lineNum(1),func_info(){}


    ///all the getters
    StackType getStackType()
    {
        return StackType();
    }
    vector<int>& getTrueList()
    {
        return this->trueList;
    }
    vector<int>& getFalseList()
    {
        return this->falseList;
    }
    vector<int>& getContinueList()
    {
        return this->continueList;
    }
    vector<int>& getNextList()
    {
        return this->nextList;
    }
    vector<int>& getBreakList()
    {
        return this->breakList;
    }
};

#define YYSTYPE StackType

#endif //COMPI3_STACKSTRUCT_H