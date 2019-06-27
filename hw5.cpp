//
// Created by omri on 04/06/2019.
//
#include "hw5.hpp"

symbolTable* scopes = new symbolTable();

//TODO: take care to preconditions too....


void allocVar(StackType stackType)
{
    reg register1=stackType.regist;
    //CodeBuffer::instance().emit("subu $sp,$sp,4");
    //pop();

    ///REMOVE
    /*if(stackType.type==UndefinedType)
    {
        CodeBuffer::instance().emit("sw $0,$(sp)");
        return;
    }*/
    if(register1==noRegister || reg_to_string(register1)=="")
    {
        register1=Registers::loadImmToReg(stackType.str);
    }
    //ostringstream ostringstream1;
    //ostringstream1<<"sw"<<reg_to_string(register1)<<", ($sp)";
    //CodeBuffer::instance().emit(ostringstream1.str());
    pushReg(register1);
    register_alloc->freeRegister(register1);
}
void assignToVar(int offset, StackType stackType)
{
    //ostringstream ostringstream1;
    reg register1=stackType.regist;
    if(register1==noRegister)
    {
        register1=Registers::loadImmToReg(stackType.str);
    }
    //CodeBuffer::instance().emit(ostringstream1.str());
    pushOffset(register1,offset);
    register_alloc->freeRegister(register1);
}
reg arithmetic_op(ari_op op, StackType stackType1, StackType stackType3)
{
    reg register1=stackType1.regist;
    reg register3=stackType3.regist;
    string reg1_str=stackType1.str;
    string reg3_str=stackType3.str;
/// if one of reg1 or reg2 are noReg, we allocate them
    if(register1==noRegister)
    {
        register1=register_alloc->loadImmToReg(stackType1.str);
    }
    if(register3==noRegister)
    {
        register3=register_alloc->loadImmToReg(stackType3.str);
    }
    bool is_byte_op= false;
    if(stackType1.type==ByteType && stackType3.type==ByteType)
    {
        is_byte_op=true;
    }
    if(!is_byte_op)
    {
        if(op==add_op)
        {
            add(register1,register1,register3);
        }
        if(op==sub_op)
        {
            sub(register1,register1,register3);
        }
        if(op==mul_op)
        {
            mul(register1,register1,register3);
        }
        if(op==div_op)
        {
            div(register1,register1,register3);
        }
    }
    if(is_byte_op)
    {
        if(op==add_op)
        {
            //CodeBuffer::instance().emit("hi");
            addB(register1,register1,register3);
        }
        if(op==sub_op)
        {
            subB(register1,register1,register3);
        }
        if(op==mul_op)
        {
            mulB(register1,register1,register3);
        }
        if(op==div_op)
        {
            divB(register1,register1,register3);
        }
    }

/*
    string op_str=ari_to_string(op);
    ostringstream ostringstream1;
    ostringstream1<<op_str<<" "<<reg_to_string(register1)<<","<<reg_to_string(register1)<<", "<<reg_to_string(register3);
    if(resy == true)
    {
        ostringstream1<<endl<<"and "<<reg_to_string(register1)<<", "<< "255";
    }
    CodeBuffer::instance().emit(ostringstream1.str());
    */
    register_alloc->freeRegister(register3);
    return register1;
}
reg loadRegister(VariableEntry* variableEntry)
{
    reg register1=register_alloc->RegisterAlloc();
    //ostringstream ostringstream1;
    int offset=(variableEntry->getWordOffset());
    popOffset(register1,offset);
    //ostringstream1<<"lw "<<reg_to_string(register1)<<", "<<offset<< "($fp)";
    // CodeBuffer::instance().emit(ostringstream1.str());
    return register1;
}
reg loadImmediate(string number)
{
    reg register1=register_alloc->RegisterAlloc();
    ostringstream ostringstream1;
    ostringstream1<<"li "<<reg_to_string(register1)<<", "<< register_alloc->boolImmToStr(number);
    CodeBuffer::instance().emit(ostringstream1.str());
    return register1;
}

void logRelop(const string& relop, reg register1, reg register2, vector<int>& true_list, vector<int>& false_list)
{
    if(relop=="==")
    {
        true_list=CodeBuffer::instance().makelist(beq(register1,register2));
    }
    else if(relop== "!=")
    {
        true_list=CodeBuffer::instance().makelist(bne(register1,register2));
    }
    else if(relop== "<=")
    {
        true_list=CodeBuffer::instance().makelist(ble(register1,register2));
    }
    else if(relop== ">=")
    {
        true_list=CodeBuffer::instance().makelist(bge(register1,register2));
    }
    else if(relop== "<")
    {
        true_list=CodeBuffer::instance().makelist(blt(register1,register2));
    }
    else if(relop== ">")
    {
        true_list=CodeBuffer::instance().makelist(bgt(register1,register2));
    }
    false_list=CodeBuffer::instance().makelist(jmp());

    /*
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
*/

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

////in this function, we probably suppose that the register is valid todo: check it.
void addRegisterToFunc(reg register1) {
    if(register1!=noRegister)
    {
        /*
        CodeBuffer::instance().emit("subu $sp,$sp,4");
        ostringstream ostringstream1;
        ostringstream1<<"sw"<<reg_to_string(register1)<<", ($sp)";
        CodeBuffer::instance().emit(ostringstream1.str());
        //CodeBuffer::instance().emit("sw" + reg_to_string(register1)+", ($sp)");
         */
        pushReg(register1);
        register_alloc->freeRegister(register1);
    }

}
void addVarToFunc(string varName)
{
    VariableEntry* variableEntry=scopes->getVariable(varName);
    int offset=variableEntry->getWordOffset();
    reg reg1=register_alloc->RegisterAlloc();
    pushReg(reg1);
    popOffset(reg1,offset);
    register_alloc->freeRegister(reg1);

}
//string boolImmToStr(string imm_val) {}

void returnValueFromFunc(StackType stackType)
{
    if(stackType.regist!=noRegister)
    {
        //CodeBuffer::instance().emit("move $v0, "+ reg_to_string(stackType.regist));
        stackType.regist = register_alloc->RegisterAlloc();
        mov($v0,stackType.regist);
        register_alloc->freeRegister(stackType.regist);
        return;
    }
    else
    {
        string string1=stackType.str;
        ostringstream ostringstream1;
        if(isImmediate(string1))
        {
            //CodeBuffer::instance().emit("li $v0, "+ register_alloc->boolImmToStr(string1));
            string string2=register_alloc->boolImmToStr(string1);
            loadImm($v0,string2);
            return;
        }
        // ostringstream ostringstream2;
        VariableEntry* variableEntry=scopes->getVariable(string1);
        //assert(variableEntry!=NULL);
        int offset = variableEntry->getOffset();
        //ostringstream2<<"lw $vo, "<<offset<<"($fp)";
        popOffset($v0,offset);
    }

}
void addImmToFunc(string imm_value)
{
    //ass_alloc();
    //pop();
    reg register1=register_alloc->RegisterAlloc();
    //ostringstream ostringstream1;
    string imm_val=register_alloc->boolImmToStr(imm_value);
    if(imm_val[imm_val.size()-1] =='b')
    {
        imm_val=imm_val.substr(0,imm_val.size()-1);
    }
    loadImm(register1,imm_val);
    pushReg(register1);

    //ostringstream1 << "li " << reg_to_string(register1) << ", " << register_alloc->boolImmToStr(imm_val) << endl;
    //ostringstream1 << "sw " << reg_to_string(register1) << ", " << "($sp)";
    //CodeBuffer::instance().emit(ostringstream1.str());
    register_alloc->freeRegister(register1);
}
void retFromFunc(StackType stackType)
{
    //popReg($ra);
    //popReg($fp);
    CodeBuffer::instance().emit("lw $ra, ($sp)");
    CodeBuffer::instance().emit("addu $sp, $sp, 4");

    CodeBuffer::instance().emit("lw $fp, ($sp)");
    CodeBuffer::instance().emit("addu $sp, $sp, 4");

    //CodeBuffer::instance().emit("addu $sp, $sp, 8");
    register_alloc->removeUsedRegistersFromStack();
}
reg createString(string string1)
{
    reg register1 = register_alloc->RegisterAlloc();
    static int counter = 0;
    ostringstream ostringstream1;
    ostringstream1 << "string_label" << counter++;
    string str_label = ostringstream1.str();
    ostringstream1 << ": .asciiz " << string1;
    CodeBuffer::instance().emitData(ostringstream1.str());
    ostringstream ostringstream2;
    ostringstream2<<"la "<<reg_to_string(register1)<<", "<<str_label;
    CodeBuffer::instance().emit(ostringstream2.str());
    return register1;
}

string createPrecondString(string string1){
    reg register1 = register_alloc->RegisterAlloc();
    static int counter = 0;
    ostringstream ostringstream1;
    ostringstream1 << "precond_label" << counter++;
    string label = ostringstream1.str();
    string str_label = ostringstream1.str();
    ostringstream1 << ": .asciiz " << string1;
    CodeBuffer::instance().emitData(ostringstream1.str());
    return label;
}

reg callFunc(string func_name, StackType stackType)
{
    int size=0;
    // vector<TypedVar> parameters=stackType.func_info;
    register_alloc->addUsedRegistersToStack();
    //CodeBuffer::instance().emit("subu $sp, $sp, 8");
    CodeBuffer::instance().emit("subu $sp, $sp, 4");
    CodeBuffer::instance().emit("sw $fp, ($sp)");
    CodeBuffer::instance().emit("subu $sp, $sp, 4");
    CodeBuffer::instance().emit("sw $ra, ($sp)");
    if(func_name=="print")
    {
        reg register1= createString(stackType.str);
        stackType.regist=register1;
        allocVar(stackType);
        register_alloc->freeRegister(register1);
        CodeBuffer::instance().emit("jal __" + func_name);
        //ass_free();
        pop();
        retFromFunc(stackType);
        return noRegister;
    }
    if(func_name=="printi"){
        pushReg(stackType.regist);
        CodeBuffer::instance().emit("jal __" + func_name);
        //ass_free();
        pop();
        retFromFunc(stackType);
        return noRegister;
    }
    for(int i=stackType.func_info.size()-1;i>=0; i--)
    {
        VariableEntry* variableEntry=scopes->getVariable(stackType.func_info[i].Id);
        if(stackType.func_info[i].regist== noRegister)
        {
            addRegisterToFunc(stackType.func_info[i].regist);
            // size+=4;
        }
        else if(isImmediate(stackType.func_info[i].Id))
        {
            addImmToFunc(stackType.func_info[i].Id);
            //size+=4;
        }
        else if(variableEntry!=NULL)
        {
            addVarToFunc(stackType.func_info[i].Id);
            //size+=4;
        }
        //size+=1;
    }

    CodeBuffer::instance().emit("jal __" + func_name);
    //reg register1 = noRegister;
    reg ret_value_reg = register_alloc->RegisterAlloc();
    register_alloc->freeRegister(ret_value_reg);
    FunctionEntry* func_entry = scopes->getFunction(func_name);
    assert(func_entry != NULL);
    ///This is fantastic. Bad Coding habits for the win!
    /*if(func_name != "printi"){
        pop();
    }*/
    //stringstream ostream;
    //ostream << "addu $sp, $sp, " << size;
    //CodeBuffer::instance().emit(ostream.str());
    ////I added this shit, too
    for(int i=0;i<stackType.func_info.size();i++)
    {
        //CodeBuffer::instance().emit("#### this is my shit");
        //reg tmp=register_alloc->RegisterAlloc();
        //popReg(tmp);
        pop();
    }
    ///This is supposed to handle return value
    if (func_entry->getType() != typeToString(VoidType)) {
        // CodeBuffer::instance().emit("move " + reg_to_string(register1) + ", $v0");
        mov(ret_value_reg,$v0);
    }
    retFromFunc(stackType);
    return ret_value_reg;

}
void inline emit_print_printi(){
    CodeBuffer::instance().emit("__print:");
    CodeBuffer::instance().emit("lw $a0, ($sp)");
    CodeBuffer::instance().emit("li $v0, 4");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("jr $ra");
    CodeBuffer::instance().emit("__printi:");
    CodeBuffer::instance().emit("lw $a0, ($sp)");
    CodeBuffer::instance().emit("li $v0, 1");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("jr $ra");
}
void startingText()
{
    CodeBuffer::instance().emit(".globl main");
    CodeBuffer::instance().emit(".ent main");
    CodeBuffer::instance().emit("main:");
    //ass_alloc();
    CodeBuffer::instance().emit("subu $sp, $sp, 4");
    CodeBuffer::instance().emit("sw $ra, ($sp)");
    CodeBuffer::instance().emit("jal __main");
    CodeBuffer::instance().emit("ExitCode: li $v0, 10 ");
    CodeBuffer::instance().emit("syscall");
    emit_print_printi();
    CodeBuffer::instance().emit("PreConditionLabel: la $a0, PrecondFail");
    CodeBuffer::instance().emit("li $v0, 4");
    CodeBuffer::instance().emit("syscall");

    CodeBuffer::instance().emitData("DivisionByZero: .asciiz \"Error division by zero\\n\"");
    CodeBuffer::instance().emitData("PrecondFail: .asciiz \"Preconditon hasn't been satisfied for function \"");
    CodeBuffer::instance().emit("j ExitCode");
    CodeBuffer::instance().emit("TerminateZero: la $a0, DivisionByZero");
    CodeBuffer::instance().emit("li $v0, 4");
    CodeBuffer::instance().emit("syscall");
    CodeBuffer::instance().emit("j ExitCode");
}

void endingText(){
    CodeBuffer::instance().emit("jr $ra");
}