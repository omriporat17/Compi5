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
    vector<reg> availableRegisters;
    vector<reg> usedRegisters;
    vector<reg> allRegisters;

public:
     Registers();
    reg RegisterAlloc();
    void freeRegister(reg reg1);
    vector<reg>& getAvailReg();
    vector<reg>& getUsedReg();
    vector<reg>& getAllReg();

     static reg loadImmToReg(string string1);
     static string boolImmToStr(string imm_val);
     static void addUsedRegistersToStack();
     static void removeUsedRegistersFromStack();

};

static Registers register_alloc=Registers();

#endif //COMPI5_REGISTERS_HPP
