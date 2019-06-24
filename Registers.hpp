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
#include "asmFunc.hpp"

#define REG_FILE_SIZE 19



class Registers {
private:
    /*
    vector<reg> availableRegisters;
    vector<reg> allRegisters;
    int capacity; //how many registers are currently free
*/
    bool allRegisters[REG_FILE_SIZE];

public:
    Registers();
    reg RegisterAlloc();
    void freeRegister(reg reg1);
    //Todo: maybe these will fuck off soon
    vector<reg> getAvailReg();
    vector<reg> getUsedReg();
    vector<reg> getAllReg();
    int getCapacity();

    reg intToReg(int reg_num);

    int regToInt(reg reg1);

    static reg loadImmToReg(string string1);
    static string boolImmToStr(string imm_val);
    void addUsedRegistersToStack();
    void removeUsedRegistersFromStack();



};

static Registers *register_alloc = new Registers();

#endif //COMPI5_REGISTERS_HPP