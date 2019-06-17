//
// Created by omri on 04/06/2019.
//
#include "hw5.hpp"

symbolTable* scopes = new symbolTable();

//TODO: take care to preconditions too....


void allocVar(StackType stackType)
{
    reg register1=stackType.regist;
    CodeBuffer::instance().emit("subu $sp,$sp,4");
    if(stackType.type==UndefinedType)
    {
        CodeBuffer::instance().emit("sw $0,$(sp)");
        return;
    }
    if(register1==noRegister)
    {
        register1=Registers::loadImmToReg(stackType.str);
    }
    ostringstream ostringstream1;
    ostringstream1<<"sw"<<reg_to_string(register1)<<", $(sp)";
    CodeBuffer::instance().emit(ostringstream1.str());
    register_alloc.freeRegister(register1);

}
void assignToVar(int offset, StackType stackType)
{
    ostringstream ostringstream1;
    reg register1=stackType.regist;
    if(register1==noRegister)
    {
        register1=Registers::loadImmToReg(stackType.str);
    }
    CodeBuffer::instance().emit(ostringstream1.str());
    register_alloc.freeRegister(register1);
}
reg arithmetic_op(ari_op op, StackType stackType1, StackType stackType3)
{
    reg register1=stackType1.regist;
    reg register3=stackType3.regist;
    string reg1_str=stackType1.str;
    string reg3_str=stackType3.str;
    if(register1==noRegister)
    {
        register1=register_alloc.loadImmToReg(stackType3.str);
    }
    if(register1==noRegister)
    {
        register1=register_alloc.loadImmToReg(stackType3.str);
    }
    bool resy= false;
    if(stackType1.type==ByteType && stackType3.type==ByteType)
    {
        resy=true;
    }
    string op_str=ari_to_string(op);
    ostringstream ostringstream1;
    ostringstream1<<op_str<<" "<<reg_to_string(register1)<<","<<reg_to_string(register1)<<", "<<reg_to_string(register3);
    if(resy== true)
    {
        ostringstream1<<endl<<"and "<<reg_to_string(register1)<<", "<< "255";
    }
    CodeBuffer::instance().emit(ostringstream1.str());
    register_alloc.freeRegister(register3);
    return register1;
}
reg loadRegister(VariableEntry* variableEntry)
{
    reg register1=register_alloc.RegisterAlloc();
    ostringstream ostringstream1;
    int offset=(variableEntry->getOffset())*(-1);
    ostringstream1<<"lw"<<reg_to_string(register1)<<", "<<offset<< "($fp)";
    CodeBuffer::instance().emit(ostringstream1.str());
    return register1;
}
reg loadImmidiate(string number)
{
    reg register1=register_alloc.RegisterAlloc();
    ostringstream ostringstream1;
    ostringstream1<<"li"<<reg_to_string(register1)<<", "<< register_alloc.boolImmToStr(number);
    CodeBuffer::instance().emit(ostringstream1.str());
    return register1;
}

void logRelop(const string& relop, reg register1, reg register2, vector<int>& true_list, vector<int>& false_list)
{
    string rop="";

    if(relop == "==")
    {
        rop="beq ";
    } else if(relop== "!=")
    {
        rop="bne ";
    }
    else if(relop=="<=")
    {
        rop="ble ";
    }
    else if(relop==">=")
    {
        rop="bge ";
    }
    else if(relop=="<")
    {
        rop="blt ";
    }
    else if(relop==">")
    {
        rop="bgt ";
    }
    true_list=CodeBuffer::instance().makelist(CodeBuffer::instance().emit(rop+reg_to_string(register1)+ ", " + reg_to_string(register2) + ", "));
    false_list=CodeBuffer::instance().makelist(CodeBuffer::instance().emit("j "));


}
void checkDivisionByZero(StackType stackType)
{
    ostringstream ostringstream1;
    if(stackType.regist==noRegister)
    {
        stackType.regist=Registers::loadImmToReg(stackType.str);
    }
    ostringstream1<<"beq "<<reg_to_string(stackType.regist)<<", 0, TerminateZero";
    CodeBuffer::instance().emit(ostringstream1.str());

}
void defineFunc(string func_name)
{
    CodeBuffer::instance().emit("__" + func_name + ":");
    CodeBuffer::instance().emit("move $fp, $sp");
}
bool isImmediate(string imm)
{
    if(imm=="true" || imm=="false" || (imm[0]<='9' && imm[0]>='0'))
    {
        return true;
    }
    return false;
}
void callReturnFunc()
{
    CodeBuffer::instance().emit("move $sp, $fp");
    CodeBuffer::instance().emit("jr $ra");
}
void addRegisterToFunc(reg register1)
{
    CodeBuffer::instance().emit("subu $sp,$sp,4");
    CodeBuffer::instance().emit("sw" + reg_to_string(register1)+", ($sp)");
    register_alloc.freeRegister(register1);
}
void addVarToFunc(string varName)
{

}
//string boolImmToStr(string imm_val) {}

void returnValueFromFunc(StackType stackType)
{
    if(stackType.regist!=noRegister)
    {
        CodeBuffer::instance().emit("move $v0, "+ reg_to_string(stackType.regist));
        register_alloc.freeRegister(stackType.regist);
        return;
    }
    else
    {
        string string1=stackType.str;
        ostringstream ostringstream1;
        if(isImmediate(string1))
        {
            CodeBuffer::instance().emit("li $v0, "+ register_alloc.boolImmToStr(string1));
            return;
        }
        ostringstream ostringstream2;
        VariableEntry* variableEntry=scopes->getVariable(string1);
        assert(variableEntry!=NULL);
        int offset = (-1)*(variableEntry->getOffset());
        ostringstream2<<"lw $vo, "<<offset<<"($fp)";
    }

}
void addImmToFunc(string imm_value)
{
    CodeBuffer::instance().emit("subu $sp, $sp, 4");
    reg register1=register_alloc.RegisterAlloc();
    ostringstream ostringstream1;
    string imm_val=register_alloc.boolImmToStr(imm_value);
    if(imm_val[imm_val.size()-1] =='b')
    {
        imm_val=imm_val.substr(0,imm_val.size()-1);
    }

    ostringstream1 << "li " << reg_to_string(register1) << ", " << register_alloc.boolImmToStr(imm_val) << endl;
    ostringstream1 << "sw " << reg_to_string(register1) << ", " << "($sp)";
    CodeBuffer::instance().emit(ostringstream1.str());
    register_alloc.freeRegister(register1);
}
void retFromFunc(StackType stackType)
{
    CodeBuffer::instance().emit("lw $ra, ($sp)");
    CodeBuffer::instance().emit("lw $fp, 4($sp)");
    CodeBuffer::instance().emit("addu $sp, $sp, 8");
    Registers::removeUsedRegistersFromStack();
}
reg createString(string string1)
{
    reg register1 = register_alloc.RegisterAlloc();
    static int counter = 0;
    ostringstream ostringstream1;
    ostringstream1 << "string_label" << counter++;
    string str_label = ostringstream1.str();
    ostringstream1 << ": .asciiz ";
    CodeBuffer::instance().emitData(ostringstream1.str());
    CodeBuffer::instance().emit("la " + reg_to_string(register1) + ", " + str_label);
    return register1;
}
reg callFunc(string func_name, StackType stackType)
{
    int size=0;
    // vector<TypedVar> parameters=stackType.func_info;
    register_alloc.addUsedRegistersToStack();
    CodeBuffer::instance().emit("subu $sp, $sp, 8");
    CodeBuffer::instance().emit("sw $ra, ($sp)");
    CodeBuffer::instance().emit("sw $fp, 4($sp)");
    if(func_name=="print")
    {
        reg register1= createString(stackType.str);
        stackType.regist=register1;
        allocVar(stackType);
        register_alloc.freeRegister(register1);
        CodeBuffer::instance().emit("jal __" + func_name);
        CodeBuffer::instance().emit("addu $sp, $sp, 4");
        retFromFunc(stackType);
        return noRegister;
    }
    else
    {
        for(int i=stackType.func_info.size();i>=0; i--)
        {
            VariableEntry* variableEntry=scopes->getVariable(stackType.func_info[i].Id);
            if(stackType.func_info[i].regist== noRegister)
            {
                addRegisterToFunc(stackType.func_info[i].regist);
                size+=4;
            }
            else if(isImmediate(stackType.func_info[i].Id))
            {
                addImmToFunc(stackType.func_info[i].Id);
                size+=4;
            }
            else if(variableEntry!=NULL)
            {
                addVarToFunc(stackType.func_info[i].Id);
                size+=4;
            }

        }

        CodeBuffer::instance().emit("jal __" + func_name);

        reg register1 = noRegister;
        FunctionEntry* func_entry = scopes->getFunction(func_name);
        assert(func_entry != NULL);

        stringstream ostream;
        ostream << "addu $sp, $sp, " << size;
        CodeBuffer::instance().emit(ostream.str());
        retFromFunc(stackType);

        if (func_entry->getType() != typeToString(VoidType)) {
            CodeBuffer::instance().emit("move " + reg_to_string(register1) + ", $v0");
        }

        return register1;

    }
}
//void addRegToStack() {}
//void removeRegFromStack() {}
void startingText()
{
    CodeBuffer::instance().emit(".globl    main");
    CodeBuffer::instance().emit(".ent    main");
    CodeBuffer::instance().emit("main:");
    CodeBuffer::instance().emit("subu $sp, $sp, 4");
    CodeBuffer::instance().emit("sw $ra, ($sp)");
    CodeBuffer::instance().emit("jal __main");
    CodeBuffer::instance().emit("ExitCode: li $v0, 10 ");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("__print:");
    CodeBuffer::instance().emit("lw $a0, 0($sp)");
    CodeBuffer::instance().emit("li $v0, 4");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("jr $ra");
    CodeBuffer::instance().emit("__printi:");
    CodeBuffer::instance().emit("lw $a0, 0($sp)");
    CodeBuffer::instance().emit("li $v0, 1");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("jr $ra");

    CodeBuffer::instance().emitData("DivisionByZero: .asciiz \"Error division by zero\\n\"");
    CodeBuffer::instance().emit("j ExitCode");
    CodeBuffer::instance().emit("TerminateZero: la $a0, DivisionByZero");
    CodeBuffer::instance().emit("li $v0, 4");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("j ExitCode");
}