//
// Created by omri on 19/06/2019.
//
#include "Registers.hpp"
#include "StackStruct.hpp"
#include "bp.hpp"
#ifndef COMPI5_ASMFUNC_HPP
#define COMPI5_ASMFUNC_HPP

int convert_to_byte(reg src);

int add(reg dst, reg src1, reg src2);

int addB(reg dst, reg src1, reg src2);

//int addi(reg dst, reg src1, int imm);

int sub(reg dst, reg src1, reg src2);

int subB(reg dst, reg src1, reg src2);

int mul(reg dst, reg src1, reg src2);

int mulB(reg dst, reg src1, reg src2);

int div(reg dst, reg src1, reg src2);

int divB(reg dst, reg src1, reg src2);

int mov(reg dst, reg src);

int mov_imm(reg dst, int imm);

int bge(reg src1, reg src2);

int ble(reg src1, reg src2);

int bgt(reg src1, reg src2);

int blt(reg src1, reg src2);

int beq(reg src1, reg src2);

int bne(reg src1, reg src2);

int jmp(string& lbl);

int jmp();

void pushReg(reg src);

void pushImm(int imm);

void popReg(reg src);

void pop();

void change_frame();



//reg callFunc(string& func_label);

//reg returnFromFunc();

//void move_sp();

void pushOffset(reg src, int offset);

void popOffset(reg src, int offset);

void loadImm(reg src, string imm);


//reg lwStack(reg dst, int offset);

//reg swImmStack(reg dst, int offset);








#endif //COMPI5_ASMFUNC_HPP