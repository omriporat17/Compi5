#ifndef HW3_SYMBOLTABLE_HPP
#define HW3_SYMBOLTABLE_HPP
#include "output.hpp"
#include "StackStruct.hpp"
#include "bp.hpp"
#include <string>
#include <vector>
#include <cassert>
using std::string;
using std::vector;
using namespace output;
template <class T>
void clearVectorOfPointers(vector<T>& v){
    for (typename vector<T>::iterator it = v.begin(); it != v.end(); ++it){
        delete (*it);
    }

    v.clear();
}

class TableEntry{

protected:
    string id;
    int offset;

public:
    TableEntry(string& id, int offset) : id(id), offset(offset) {}
    virtual string& getId(){return this->id;}
    int getOffset(){return this->offset;}
    virtual void print() {}
    virtual ~TableEntry() {}
    int getWordOffset(){ return 4*(this->offset +1);}
};

class VariableEntry : public TableEntry{
private:
    string type;

public:
    VariableEntry(string& type, string& id, int offset) : TableEntry(id, offset), type(type) {}
    string& getType(){return type;}

    void print() {
        printID(id, offset, type);
    }
};

//TODO: Should we even implement a class for Precondition?
/*class PreEntry : public TableEntry{
public:
    int num;
    string& funcId;
    PreEntry(int preNum, string& id):TableEntry(funcId,0), num(preNum), funcId(id){}
    void print(){
        printPreconditions(id, num);
    }
};*/

///this will represent a function, as defined by the instructions
class FunctionEntry : public TableEntry{
private:
    vector<TypedVar> parameters; ///formals - whatever is between the ()
    vector<string> args;
    string type;
    int preconditionsNum;

public:
    FunctionEntry(vector<TypedVar> parameters, string& id, string& type) :
            TableEntry(id, 0), parameters(parameters), type(type), preconditionsNum(0)
    {
        for (vector<TypedVar>::iterator it = parameters.begin(); it != parameters.end(); ++it){
            args.push_back((*it).Type);
        }
    }///We match the description of the "formals" as strings in args
    string getType(){return this->type;}
    string& getId(){return this->id;}

    vector<string>& getArgs() {return args;}
    vector<TypedVar>& getParams() { return parameters;}
    void print() {
        //output::printPreconditions(this->id, this->preconditionsNum);
        ///output::printID(this->id, this->offset, output::makeFunctionType(type, args));
    }

    bool matchArgs(vector<TypedVar>& other){
        if (other.size() != args.size()){
            return false;
        }
        for (int i = 0; i < args.size(); i++){
            if (!isTypesEqual(parameters[i].Type, other[i].Type)){
                return false;
            }
        }
        return true;
    }

    bool matchType(string& type){
        return isTypesEqual(this->type, type);
    }

    bool operator==(const FunctionEntry& other) const {
        if (other.id.compare(this->id) != 0){
            return false;
        }
        if (other.parameters.size() != this->parameters.size()){
            return false;
        }
        for (int i = 0; i < other.parameters.size(); i++){
            if (other.parameters[i] != this->parameters[i])
                return false;
        }
        return true;
    }

    bool operator!=(const FunctionEntry& other) const {
        return (!(other == *this));
    }
    void incPreconditions(){
        this->preconditionsNum++;
    }
};

///this is the array of entries for each scope, the mini table inside the big table
class Scope{
private:
    vector<TableEntry *> entries;
    int offset;
    bool isWhileScope;
    bool isGlobalScope;
    bool isFuncScope;
    int precond_num;
    string func_name;

public:
    Scope(){}
    ~Scope() {
        ///output::endScope();
        ///CHANGE: REMOVED IF FROM INSIDE FOR TO OUTSIDE FOR
        if(isFuncScope){
            string s = func_name;
            ///printPreconditions(s, precond_num);
        }
        /*for (vector<TableEntry*>::iterator it = this->entries.begin(); it != this->entries.end(); ++it) {
            (*it)->print();
        }*/
        clearVectorOfPointers(this->entries);
    }
    Scope(int offset, bool isWhile_, bool isGlobal_ = false, bool isFuncScope_= false) :
            offset(offset), isWhileScope(isWhile_), isGlobalScope(isGlobal_), isFuncScope(isFuncScope_),
            precond_num(0){}
    void addEntry(TableEntry * entry)
    {
        this->entries.push_back(entry);
    }
    bool existsId(string& id)
    {
        for(vector<TableEntry*>::iterator iterator1=this->entries.begin(); iterator1!=this->entries.end(); iterator1++)
        {
            if(iterator1.operator*()->getId()==id)
            {
                return true;
            }
        }
        return false;
    }
    VariableEntry* getVariable(string& id)
    {
        VariableEntry* variableEntry= dynamic_cast<VariableEntry*>(this->getEntry(id));
        return variableEntry;
    }

    TableEntry * getEntry(string& id)
    {
        for(std::vector<TableEntry*>::iterator iterator1=this->entries.begin();
            iterator1!=this->entries.end(); iterator1++)
        {
            if(iterator1.operator*()->getId()==id)
            {
                return iterator1.operator*();
            }
        }
        return NULL;
    }
    int getOffset(){
        return this->offset;
    }
    void incrementOffset(int delta){
        offset += delta;
    }
    bool isWhile(){
        return this->isWhileScope;
    }
    TableEntry * getLastEntry() {
        if (entries.empty()){
            return NULL;
        }
        return entries.back();
    }
    void incPreconditions(){
        this->precond_num++;
    }
    void set_func_name(string& name){
        this->func_name = name;
    }
};

class symbolTable {
public:
    int lineNum;
    vector<Scope *> scopes;
private:
    Scope *global;          ///global scope
    bool mainExists;

    Scope *newScope(bool isWhile, bool initOffset = false, bool isFunc= false) {
        if (initOffset) {
            this->scopes.push_back(new Scope(0, isWhile, false, isFunc));
        } else {
            this->scopes.push_back(new Scope(this->getOffset(), isWhile, false, isFunc));
        }
        return this->scopes.back();
    }

public:
    symbolTable()
    {
        this->lineNum=1;
        this->mainExists=false;
        this->global= new Scope(0,false,true);
        this->scopes.push_back(this->global);
        vector<TypedVar> print_arguments;
        print_arguments.push_back(TypedVar("", typeToString(StringType)));
        vector<TypedVar> printi_arguments;
        printi_arguments.push_back(TypedVar("", typeToString(IntType)));

        this->addFunction(typeToString(VoidType),string("print"),print_arguments,this->lineNum, false);
        this->addFunction(typeToString(VoidType),string("printi"),printi_arguments,this->lineNum, false);

    }

    ~symbolTable()
    {
        clearVectorOfPointers(this->scopes);
    }

    //TODO: remove this is for DEBUGGING
    /*void print_func(){
        std::cout << this->scopes.back()->getLastEntry()->getId() << std::endl;
    }*/


//    The following functions are scope-related functions (i.e. create a new scope)
    void addFunction(string retval, string id, vector<TypedVar> formals, int lineno, bool addScope)
    {
        this->lineNum=lineno;
        int argOffset=0;

        if(this->existsId(id))
        {
            output::errorDef(this->lineNum,id);
            exit(0);
        }
        if(id.compare("main")==0 && retval.compare(typeToString(VoidType))==0 && formals.empty())
        {
            this->mainExists=true;
        }
        FunctionEntry* fun = new FunctionEntry(formals, id, retval);
        this->scopes.back()->addEntry(fun);
        if(addScope)
        {
            Scope *func_scope = newScope(false, true, true);
            func_scope->set_func_name(id);
            for(vector<TypedVar>::iterator iterator1=formals.begin(); iterator1!=formals.end();iterator1++)
            {
                argOffset=argOffset-getVariableSize(iterator1.operator*().Type);
                this->addFunctionArgument(iterator1.operator*().Type,iterator1.operator*().Id,argOffset,iterator1.operator*().lineNum);
            }
        }
        //print_func();
    }

    void addWhile()
    {
        this->newScope(true,false);
    }

    void addIf()
    {
        this->newScope(false,false);
    }

    void addElse()
    {
        this->newScope(false,false);

    }

    void addScope()
    {
        this->newScope(false,false);
    }


    void popScope()
    {
        if(this->scopes.empty())
        {
            return;
        }
        Scope* curr=scopes.back();
        delete(curr);
        this->scopes.pop_back();
    }

    void addVariable(string type, string id, int lineno)
    {
        if(this->existsId(id))   //we already define this var
        {
            output::errorDef(this->lineNum,id);
            exit(0);
        }
        this->scopes.back()->addEntry(new VariableEntry(type,id,this->getOffset()));
        this->scopes.back()->incrementOffset(1); // each var in the size of 1.
        //print_func();
    }

    void addFunctionArgument(string &type, string &id, int offset, int lineno)
    {
        this->lineNum=lineno;
        if(this->existsId(id))
        {
            output::errorDef(this->lineNum,id);
            exit(0);
        }

        this->scopes.back()->addEntry(new VariableEntry(type,id,offset));
    }

    void addVariable(TypedVar p, int lineno)
    {
        this->addVariable(p.Type,p.Id,lineno);
    }

//    Existence checkers and validation
    bool existsId(string &id)
    {
        for(vector<Scope*>::iterator iterator1=this->scopes.begin(); iterator1!=this->scopes.end(); iterator1++)
        {
            if(iterator1.operator*()->existsId(id))
            {
                return true;
            }
        }
        return false;
    }

    void existsMain()
    {
        if(!this->mainExists)
        {
            output::errorMainMissing();
            exit(0);
        }
    }

    void isBreakAllowed(int lineno)
    {
        this->lineNum=lineno;
        for(vector<Scope*>::iterator iterator1=this->scopes.begin();iterator1!=this->scopes.end();iterator1++)
        {
            if(iterator1.operator*()->isWhile())
            {
                return;
            }
        }
        output::errorUnexpectedBreak(lineno);
        exit(0);
    }

    void isContinueAllowed(int lineno)
    {
        this->lineNum=lineno;
        for(vector<Scope*>::iterator iterator1=this->scopes.begin();iterator1!=this->scopes.end();iterator1++)
        {
            if(iterator1.operator*()->isWhile())
            {
                return;
            }
        }
        output::errorUnexpectedContinue(lineno);
        exit(0);
    }

    void checkReturn(string type, int lineno)
    {
        FunctionEntry* functionEntry= dynamic_cast<FunctionEntry*>(this->global->getLastEntry());
        assert(functionEntry!=NULL);
        {
            if(!functionEntry->matchType(type))
            {
                cout << "A\n";
                output::errorMismatch(lineno);
                exit(0);
            }
        }
    }

    int getOffset()
    {
        if(!this->scopes.empty())
        {
            return this->scopes.back()->getOffset();
        }
        return -1; /// if there is no scope...
    }


    TableEntry* getEntry(string &id)
    {
        if(!this->scopes.empty())
        {
            return this->scopes.back()->getEntry(id);
        }
        return NULL;
    }

    FunctionEntry* getFunction(string &id)
    {
        if(!this->global)
        {
            return NULL;
        }
        return (dynamic_cast<FunctionEntry*>(this->global->getEntry(id)));
    }

    VariableEntry *getVariable(string &id)
    {
        if(!this->scopes.empty())
        {
            for(vector<Scope*>::iterator iterator1=this->scopes.begin();iterator1!=this->scopes.end();iterator1++)
            {
                if(iterator1.operator*()->getVariable(id))
                {
                    return iterator1.operator*()->getVariable(id);
                }
            }
        }
        return NULL;
    }

    int getVariableSize(string &type)
    {
        return 1;  /// all the variables in the size of 1
    }

    string callFunction(string &id, vector<TypedVar> &args, int lineno)
    {
        this->lineNum=lineno;
        FunctionEntry* functionEntry=this->getFunction(id);
        if(!functionEntry)
        {
            output::errorUndefFunc(lineno,id);
            exit(0);
        }
        if(!functionEntry->matchArgs(args))
        {
            vector<TypedVar> params = functionEntry->getParams();
            vector<string> types;
            for(vector<TypedVar>::iterator it = params.begin(); it != params.end(); it++){
                types.push_back((*it).Type);
            }
            output::errorPrototypeMismatch(lineno,id,types);
            exit(0);
        }
        return functionEntry->getType();
    }

    void isPreCondLegal(vector<TypedVar> &pre_args) {
        for(vector<TypedVar>::iterator iterator1=pre_args.begin(); iterator1!=pre_args.end();iterator1++){
            if(!existsId(iterator1.operator*().Id)){
                output::errorUndef(iterator1.operator*().lineNum, iterator1.operator*().Id);
                exit(0);
            }
        }
    }
};
#endif //HW3_SYMBOLTABLE_HPP