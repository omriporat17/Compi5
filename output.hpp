#ifndef HW3_OUTPUT_HPP
#define HW3_OUTPUT_HPP


#include <string>
#include <vector>
using namespace std;
namespace output{

    void endScope();

    void printID(const string& id, int offset, const string& type);

    void printPreconditions(const string& id, int preconditionsNum); /* Do not save the string returned from this function in a data structure as it is not dynamically allocated and will be destroyed(!) at the end of the calling scope. */

    string makeFunctionType(const string& retType, vector<string>& argTypes);

    void errorLex(int lineno);

    void errorSyn(int lineno);

    void errorUndef(int lineno, const string& id);

    void errorDef(int lineno, const string& id);

    void errorUndefFunc(int lineno, const string& id);

    void errorMismatch(int lineno);

    void errorPrototypeMismatch(int lineno, const string& id, vector<string>& argTypes);

    void errorUnexpectedBreak(int lineno);

    void errorUnexpectedContinue(int lineno);

    void errorMainMissing();

    void errorByteTooLarge(int lineno, const string& value);
}

#endif //HW3_OUTPUT_HPP
