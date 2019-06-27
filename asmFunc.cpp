//
// Created by omri on 19/06/2019.
//

#include "asmFunc.hpp"

int check_div_by_zero(reg src)
{
    std::ostringstream ostringstream1;
    ostringstream1 << "beq " << reg_to_string(src) << ", $zero DivisionByZero";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int convert_to_byte(reg src)
{
    std::ostringstream ostringstream1;
    ostringstream1 << "and " << reg_to_string(src) << ", " << reg_to_string(src) << ", 0xff";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int add(reg dst, reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "addu "<< reg_to_string(dst) << ", "<<reg_to_string(src1) << ", "<<reg_to_string(src2);
    return CodeBuffer::instance().emit(ostringstream1.str());


}

int addB(reg dst, reg src1, reg src2)
{
    int location=add(dst,src1,src2);
    convert_to_byte(dst);
    return location;
}

/*
int addi(reg dst, reg src1, int imm)
{
}
*/
int sub(reg dst, reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "subu "<< reg_to_string(dst) << ", "<<reg_to_string(src1) << ", "<<reg_to_string(src2);
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int subB(reg dst, reg src1, reg src2)
{
    int location=sub(dst,src1,src2);
    convert_to_byte(dst);
    return location;
}

int mul(reg dst, reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "mul "<< reg_to_string(dst) << ", "<<reg_to_string(src1) << ", "<<reg_to_string(src2);
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int mulB(reg dst, reg src1, reg src2)
{
    int location=mul(dst,src1,src2);
    convert_to_byte(dst);
    return location;
}

int div(reg dst, reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    check_div_by_zero(src2);
    ostringstream1<< "div "<< reg_to_string(dst) << ", "<<reg_to_string(src1) << ", "<<reg_to_string(src2);
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int divB(reg dst, reg src1, reg src2)
{
    check_div_by_zero(src2);
    int location=div(dst,src1,src2);
    convert_to_byte(dst);
    return location;
}

int mov(reg dst, reg src)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "move "<< reg_to_string(dst) << ", "<<reg_to_string(src);
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int mov_imm(reg dst, int imm)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "li "<< reg_to_string(dst) << ", "<<imm;
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int bge(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "bge "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int ble(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "ble "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int bgt(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "bgt "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int blt(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "blt "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int beq(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "beq "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int bne(reg src1, reg src2)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "bne "<< reg_to_string(src1) << ", "<<reg_to_string(src2)<<", ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int jmp(string& lbl)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "j "<< lbl;
    return CodeBuffer::instance().emit(ostringstream1.str());
}

int jmp()
{
    std::ostringstream ostringstream1;
    ostringstream1<< "j ";
    return CodeBuffer::instance().emit(ostringstream1.str());
}

void pushReg(reg src)
{
    //TODO: add protection to reg_to_string
    std::ostringstream ostringstream1;
    ostringstream1<<"sub $sp, $sp, 4\n";
    ostringstream1<< "sw "<< reg_to_string(src)<< ", ($sp) "<<endl;
    CodeBuffer::instance().emit(ostringstream1.str());
}

void pushImm(int imm)
{
    reg reg1=register_alloc->RegisterAlloc();
    mov_imm(reg1,imm);
    pushReg(reg1);
    register_alloc->freeRegister(reg1);
    CodeBuffer::instance().emit("\n");
}

void popReg(reg src)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "lw "<< reg_to_string(src)<< ", ($sp) "<< endl;
    ostringstream1<<"addu $sp, $sp, 4"<<endl;
    CodeBuffer::instance().emit(ostringstream1.str());
}

void pop()
{
    std::ostringstream ostringstream1;
    ostringstream1<<"addu $sp, $sp, 4";
    CodeBuffer::instance().emit(ostringstream1.str());
}

void pushOffset(reg src, int offset)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "sw "<< reg_to_string(src)<< ", "<< -offset <<"($fp)";
    CodeBuffer::instance().emit(ostringstream1.str());
}

void popOffset(reg src, int offset)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "lw "<< reg_to_string(src)<< ", "<< -offset <<"($fp)";
    CodeBuffer::instance().emit(ostringstream1.str());
}

void loadImm(reg src, string imm)
{
    std::ostringstream ostringstream1;
    ostringstream1<< "li "<< reg_to_string(src)<< ", "<< imm;
    CodeBuffer::instance().emit(ostringstream1.str());
}

void change_frame()
{
    std::ostringstream ostringstream1;
    ostringstream1<<"move $sp, $fp";
    ostringstream1<<"jr $ra";
    CodeBuffer::instance().emit(ostringstream1.str());
}



//reg callFunc(string& func_label);

//reg returnFromFunc();