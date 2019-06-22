//
// Created by omri on 04/06/2019.
//

#include "Registers.hpp"


///// FALSE if the register is free, true if not

Registers::Registers()
{
    /*
    this->capacity = 0;
    for(int i=$t0;i<=$t9;i++)
    {
        this->availableRegisters.push_back((reg)i);
        this->capacity++;
        this->allRegisters.push_back((reg)i);
    }
     */
    for(int i=0;i<REG_FILE_SIZE;i++)
    {
        this->allRegisters[i]=false;
    }
}
reg Registers::RegisterAlloc()
{
    for(int i=0;i<REG_FILE_SIZE;i++)
    {
        if(this->allRegisters[i]==false)
        {
            this->allRegisters[i]=true;
            return intToReg(i);
        }
    }
    return noRegister;

    /*
    if(!this->capacity == 0)
    {
        reg registers1=this->availableRegisters[0];
        this->availableRegisters.erase(this->availableRegisters.begin());
        this->capacity--;
        return registers1;
    }
    return noRegister;
     */
}
void Registers::freeRegister(reg register1)
{
    /*
    if(std::find(availableRegisters.begin(),availableRegisters.end(),register1)!=availableRegisters.end())
    {
        return;  ///if the register is not allocated, (== available)
    }
    //assert(REG_FILE_SIZE-capacity>=1);
    this->availableRegisters.push_back(register1);
    this->capacity++;
     */
    int reg_index=regToInt(register1);
    this->allRegisters[reg_index]=false;

}
vector<reg> Registers::getAvailReg()
{
    //return this->availableRegisters;
    vector<reg> availReg;
    for (int i=0;i<REG_FILE_SIZE;i++)
    {
        if(this->allRegisters[i]==false)
        {
            availReg.push_back(intToReg(i));
        }
    }
    return availReg;
}
vector<reg> Registers::getUsedReg()
{
    /*
    vector<reg> usedRegisters;
    for(int i=0;i<this->allRegisters.size();i++)
    {
        usedRegisters.push_back(allRegisters[i]);
    }
    usedRegisters.erase(this->availableRegisters.begin(),this->availableRegisters.end());
    return usedRegisters;
     */
    vector<reg> usedReg;
    for (int i=0;i<REG_FILE_SIZE;i++)
    {
        if(this->allRegisters[i]==true)
        {
            usedReg.push_back(intToReg(i));
        }
    }
    return usedReg;

}
vector<reg> Registers::getAllReg()
{
    //return this->allRegisters;
    vector<reg> allReg;
    for (int i=0;i<REG_FILE_SIZE;i++)
    {
        allReg.push_back(intToReg(i));
    }
    return allReg;
}


int Registers::getCapacity(){
    //return this->capacity;
    int capacity=0;
    for (int i=0;i<REG_FILE_SIZE;i++)
    {
        if(this->allRegisters[i]==false)
        {
            capacity++;
        }
    }
    return capacity;

}


reg Registers::loadImmToReg(string string1)
{
    //ostringstream aux;
    reg register1=register_alloc->RegisterAlloc();
    //aux<<"li"<<reg_to_string(register1)<<", "<<boolImmToStr(string1);
    //CodeBuffer::instance().emit(aux.str());
    string string2=boolImmToStr(string1);
    loadImm(register1,string2);
    // register_alloc->freeRegister(register1);
    return register1;
}
string Registers::boolImmToStr(string imm_val)
{
    if(imm_val=="false")
    {
        return "0";
    }
    if(imm_val=="true")
    {
        return "1";
    }
    return imm_val;
}
void Registers::addUsedRegistersToStack()
{
    /*
    // vector<registers > all_reg=this->allRegisters;
    for(vector<reg>::iterator iterator1=register_alloc->getAllReg().begin(); iterator1!=register_alloc->getAllReg().end();iterator1++)
    {
        CodeBuffer::instance().emit("subu $sp,$sp,4");
        CodeBuffer::instance().emit("sw "+reg_to_string(iterator1.operator*()) + ", ($sp)" );
    }
     */
    for(int i=0; i<REG_FILE_SIZE; i++)
    {
        pushReg(intToReg(i));
    }
}
void Registers::removeUsedRegistersFromStack()
{
    //  for(vector<reg>::reverse_iterator iterator1=register_alloc->getAllReg().rbegin(); iterator1!=register_alloc->getAllReg().rend();iterator1++)
    //{
    /*
    CodeBuffer::instance().emit("lw "+reg_to_string(iterator1.operator*()) + ", ($sp)" );
    CodeBuffer::instance().emit("addu $sp,$sp,4");
     */
    //  pushReg(iterator1.operator*());

    // }
    for(int i=0; i<REG_FILE_SIZE; i++)
    {
        popReg(intToReg(i));
    }
}

reg Registers::intToReg(int reg_num)
{
    if(reg_num==-1)
    {
        return noRegister;
    }
    if(reg_num==0)
    {
        return $v0;
    }
    if(reg_num==1)
    {
        return $t0;
    }
    if(reg_num==2)
    {
        return $t1;
    }
    if(reg_num==3)
    {
        return $t2;
    }
    if(reg_num==4)
    {
        return $t3;
    }
    if(reg_num==5)
    {
        return $t4;
    }
    if(reg_num==6)
    {
        return $t5;
    }
    if(reg_num==7)
    {
        return $t6;
    }
    if(reg_num==8)
    {
        return $t7;
    }
    if(reg_num==9)
    {
        return $s0;
    }
    if(reg_num==10)
    {
        return $s1;
    }
    if(reg_num==11)
    {
        return $s2;
    }
    if(reg_num==12)
    {
        return $s3;
    }
    if(reg_num==13)
    {
        return $s4;
    }
    if(reg_num==14)
    {
        return $s5;
    }
    if(reg_num==15)
    {
        return $s6;
    }if(reg_num==16)
    {
        return $s7;
    }
    if(reg_num==17)
    {
        return $t8;
    }
    if(reg_num==18)
    {
        return $t9;
    }
    return noRegister;


}
int Registers::regToInt(reg register1)
{
    if(register1==noRegister)
    {
        return -1;
    }
    if(register1==$v0)
    {
        return 0;
    }
    if(register1==$t0)
    {
        return 1;
    }
    if(register1==$t1)
    {
        return 2;
    }
    if(register1==$t2)
    {
        return 3;
    }
    if(register1==$t3)
    {
        return 4;
    }
    if(register1==$t4)
    {
        return 5;
    }
    if(register1==$t5)
    {
        return 6;
    }
    if(register1==$t6)
    {
        return 7;
    }
    if(register1==$t7)
    {
        return 8;
    }
    if(register1==$s0)
    {
        return 9;
    }
    if(register1==$s1)
    {
        return 10;
    }
    if(register1==$s2)
    {
        return 11;
    }
    if(register1==$s3)
    {
        return 12;
    }
    if(register1==$s4)
    {
        return 13;
    }
    if(register1==$s5)
    {
        return 14;
    }
    if(register1==$s6)
    {
        return 15;
    }
    if(register1==$s7)
    {
        return 16;
    }
    if(register1==$t8)
    {
        return 17;
    }
    if(register1==$t9)
    {
        return 18;
    }
    return -1;
}