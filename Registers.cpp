//
// Created by omri on 04/06/2019.
//

#include "Registers.hpp"


Registers::Registers()
{
    for(int i=$t0;i<$t9;i++)
    {
        this->availableRegisters.push_back((registers)i);
        this->allRegisters.push_back((registers)i);
    }

}
registers Registers::RegisterAlloc()
{
    if(!this->availableRegisters.empty())
    {
        registers registers1=this->availableRegisters[0];
        this->availableRegisters.erase(this->availableRegisters.begin());
        return registers1;
    }


}
void Registers::freeRegister(registers register1)
{
    if(std::find(availableRegisters.begin(),availableRegisters.end(),register1)!=availableRegisters.end())
    {
        return;  ///if the register is not allocated, (== available)
    }
    assert(this->allRegisters.size()-this->availableRegisters.size()>=1);
    this->availableRegisters.push_back(register1);

}
vector<registers>& Registers::getAvailReg()
{
    return this->availableRegisters;
}
vector<registers>& Registers::getUsedReg()
{
    vector<registers> usedRegisters;
    for(int i=0;i<this->allRegisters.size();i++)
    {
        usedRegisters.push_back(allRegisters[i]);
    }
    usedRegisters.erase(this->availableRegisters.begin(),this->availableRegisters.end());
    return usedRegisters;

}
vector<registers>& Registers::getAllReg()
{
    return this->allRegisters;
}


registers Registers::loadImmToReg(string string1)
{
    ostringstream aux;
    registers register1=register_alloc.RegisterAlloc();
    aux<<"li"<<reg_to_string(register1)<<", "<<boolImmToStr(string1);
    CodeBuffer::instance().emit(aux.str());
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
   // vector<registers > all_reg=this->allRegisters;
    for(vector<registers >::iterator iterator1=register_alloc.getAllReg().begin(); iterator1!=register_alloc.getAllReg().end();iterator1++)
    {
        CodeBuffer::instance().emit("subu $sp,$sp,4");
        CodeBuffer::instance().emit("sw"+reg_to_string(iterator1.operator*()) + ", ($sp)" );

    }
}
void Registers::removeUsedRegistersFromStack()
{
    for(vector<registers >::reverse_iterator iterator1=register_alloc.getAllReg().rbegin(); iterator1!=register_alloc.getAllReg().rend();iterator1++)
    {
        CodeBuffer::instance().emit("lw"+reg_to_string(iterator1.operator*()) + ", ($sp)" );
        CodeBuffer::instance().emit("addu $sp,$sp,4");

    }
}