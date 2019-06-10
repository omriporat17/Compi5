//
// Created by omri on 04/06/2019.
//


#ifndef COMPI5_REGISTERS_HPP
#define COMPI5_REGISTERS_HPP

#include "StackStruct.hpp"
#include <cassert>
#include <algorithm>
#include <set>
#include <sstream>

#include "bp.hpp"

class Registers {
private:
    vector<registers> availableRegisters;
    vector<registers> allRegisters;

public:
     Registers();
    registers RegisterAlloc();
    void freeRegister(registers register1);
    vector<registers>& getAvailReg();
    vector<registers>& getUsedReg();
    vector<registers>& getAllReg();

     static registers loadImmToReg(string string1);
     static string boolImmToStr(string imm_val);
     static void addUsedRegistersToStack();
     static void removeUsedRegistersFromStack();

}register_alloc;


#endif //COMPI5_REGISTERS_HPP
