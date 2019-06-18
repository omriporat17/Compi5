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

#define REG_FILE_SIZE $t9
class Registers {
private:
    vector<reg> availableRegisters;
    vector<reg> allRegisters;
    int capacity; //how many registers are currently free


public:
    Registers();
    reg RegisterAlloc();
    void freeRegister(reg reg1);
    vector<reg>& getAvailReg();
    vector<reg> getUsedReg();
    vector<reg>& getAllReg();
    int getCapacity();

    static reg loadImmToReg(string string1);
    static string boolImmToStr(string imm_val);
    static void addUsedRegistersToStack();
    static void removeUsedRegistersFromStack();

};

static Registers *register_alloc = new Registers();

#endif //COMPI5_REGISTERS_HPP