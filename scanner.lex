%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SymbolTable.hpp"
#include "parser.tab.hpp"

extern symbolTable* scopes;

yytokentype handleTokenAux(yytokentype token);

void printString(string str);

void printStringAux1(string str);

void printStringAux2(string str);

yytokentype handleTokenType(yytokentype token, types type);

yytokentype handleToken(yytokentype token);

yytokentype handleOP(yytokentype token, types op);

string convert_to_string(yytokentype token);


%}

%option noyywrap
%option yylineno

%%

(void) 		                      return handleToken(VOID);
(int) 		                         return handleTokenType(INT,IntType);
(byte)		                          return handleTokenType(BYTE,ByteType);
(b)			                          return handleToken(B);
(bool)		                         return handleTokenType(BOOL,BoolType);
(and)		                      return handleToken(AND);
(or)		                    return handleToken(OR);
(not)		                   return handleToken(NOT);
(true)		                    return handleTokenType(TRUE,BoolType);
(false)		                      return handleTokenType(FALSE,BoolType);
(return)	                        return handleToken(RETURN);
(if)		                         return handleToken(IF);
(else)		                        return handleToken(ELSE);
(while)		                      return handleToken(WHILE);
(break)		                    return handleToken(BREAK);
(continue)	                   return handleToken(CONTINUE);
(@pre)		                   return handleToken(PRECOND);
;		                        return handleToken(SC);
,		                          return handleToken(COMMA);
\(		                            return handleToken(LPAREN);
\)		                            return handleToken(RPAREN);
\{		                          return handleToken(LBRACE);
\}		                        return handleToken(RBRACE);
=		                       return handleToken(ASSIGN);
==|!=|<|>|<=|>= 				return handleToken(RELOP);
\+                                return handleOP(BINOPPM,add_op);
\-						            return handleOP(BINOPPM,sub_op);
\*						            return handleOP(BINOPMD,mul_op);
\/                                return handleOP(BINOPMD,div_op);
([a-zA-Z][a-zA-Z0-9]*)	        return handleToken(ID);
(0|[1-9][0-9]*) 		       return handleTokenType(NUM,IntType);
\"([^\n\r\"\\]|\\[rnt"\\])+\"   return handleTokenType(STRING,StringType);
[ \n\r\t]+                     ;
\/\/[^\r\n]*[\r|\n|\r\n]?      ;
. {output::errorLex(yylineno); exit(0);}


%%


yytokentype handleTokenType(yytokentype token, types type)
{
	yylval=StackType(type);
	return handleTokenAux(token);
}

yytokentype handleToken(yytokentype token)
{
	yylval=StackType();
	return handleTokenAux(token);
}

yytokentype handleOP(yytokentype token, types op)
{
	yylval=StackType(op);
	return handleTokenAux(token);
}


yytokentype handleTokenAux(yytokentype token)
{
	yylval.str=yytext;
	yylval.lineNum=yylineno;
	//printString(convert_to_string(token));
	scopes->lineNum = yylineno;
	return token;
}


void printString(string str)
{
	if(str=="ID" || str=="NUM" || str=="STRING")
	{
		printStringAux1(str);
	}
	else{
		printStringAux2(str);
	}
}


void printStringAux1(string str)
{
	printf("%s %s\n",str.c_str(),yytext);
}

void printStringAux2(string str)
{
	printf("%s\n",str.c_str());
}

string convert_to_string(yytokentype token){
	switch(token) {
		case VOID: 	return "VOID";	   					break;
		case INT: return "INT";	    					break;
		case B: return "B";	    						break;
		case BYTE:	return "BYTE"; 						break;
		case BOOL:	return "BOOL";   					break;
		case PRECOND: return "PRECOND";					break;
		case AND:	return "AND";						break;
		case OR:	return "OR";						break;
		case NOT:	return "NOT";						break;
		case TRUE: return "TRUE";						break;
		case FALSE:return "FALSE";						break;
		case RETURN:return "RETURN";					break;
		case IF:return "IF";							break;
		case ELSE:return "ELSE";						break;
		case WHILE:return "WHILE";						break;
		case BREAK:return "BREAK";						break;
		case CONTINUE:return "CONTINUE";				break;
		case SC:return "SC";							break;
		case COMMA:return "COMMA";						break;
		case LPAREN:return "LPAREN";					break;
		case RPAREN:return "RPAREN";					break;
		case LBRACE:return "LBRACE";					break;
		case RBRACE:return "RBRACE";					break;
		case ASSIGN:return "ASSIGN";					break;
		case RELOP:return "RELOP";						break;
		case BINOPPM:return "BINOPPM";					break;
		case BINOPMD:return "BINOPMD";					break;
		case ID:return "ID";							break;
		case NUM:return "NUM";							break;
		case STRING:return "STRING";					break;
	}
}