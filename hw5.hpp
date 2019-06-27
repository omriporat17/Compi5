//
// Created by omri on 04/06/2019.
//

#ifndef COMPI5_HW5_HPP
#define COMPI5_HW5_HPP

#include "StackStruct.hpp"
#include "Registers.hpp"
#include "SymbolTable.hpp"
#include "bp.hpp"
#include "asmFunc.hpp"



void allocVar(StackType stackType=StackType());

void assignToVar(int offset, StackType stackType);

reg arithmetic_op(ari_op op, StackType stackType1, StackType stackType3);

reg loadRegister(VariableEntry* variableEntry);

reg loadImmediate(string number);

void logRelop(const string& relop, reg register1, reg register2, vector<int>& true_list, vector<int>& false_list);

void checkDivisionByZero(StackType stackType);

//Todo: this is never used, can delete
void defineFunc(string func_name);

bool isImmediate(string imm);

void callReturnFunc();

void addRegisterToFunc(reg register1);

void addVarToFunc(string varName);

//string boolImmToStr(string imm_val);

void returnValueFromFunc(StackType stackType);

void addImmToFunc(string imm_val);

void retFromFunc(StackType stackType);

reg createString(string string1);

string createPrecondString(string string1);

reg callFunc(string func_name, StackType stackType);

//void addRegToStack();

//void removeRegFromStack();

void startingText();

void endingText();

#endif //COMPI5_HW5_HPP