//
// Created by omri on 04/06/2019.
//

#ifndef COMPI5_HW5_HPP
#define COMPI5_HW5_HPP

#include "Registers.hpp"
#include "symbolTable.hpp"
#include "bp.hpp"



void allocVar(StackType stackType=StackType());

void assignToVar(int offset, StackType stackType);

registers ari_op(ari_op op, StackType stackType1, StackType stackType3);

registers loadRegister(VariableEntry* variableEntry);

registers loadImmidiate(string number);

void logRelop(const string& relop, registers register1, registers register2, vector<int>& true_list, vector<int>& false_list);

void checkDivisionByZero(StackType stackType);

void defineFunc(string func_name);

bool isImmediate(string imm);

void callReturnFunc();

void addRegisterToFunc(registers register1);

void addVarToFunc(string varName);

//string boolImmToStr(string imm_val);

void returnValueFromFunc(StackType stackType);

void addImmToFunc(string imm_val);

void retFromFunc(StackType stackType);

registers createString(string string1);

registers callFunc(string func_name, StackType stackType=StackType());

//void addRegToStack();

//void removeRegFromStack();

void startingText();

#endif //COMPI5_HW5_HPP
