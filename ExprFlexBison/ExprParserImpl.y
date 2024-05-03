
%define parse.error verbose
%define api.pure full

%{

#include <iostream>
#include "ExprLexerImpl.h"
#include "ExprLexer.hpp"

bool error;
int value;
extern ExprLexer lexer;

void yyerror(const char *msg)
{
    error = true;
    std::cerr << "Error: " << msg << '\n';
}

#define yylex(v) static_cast<int>(lexer.nextToken(v))

%}

%token OpAdd "+"
%token OpMult "*"
%token OpenPar "("
%token ClosePar ")"
%token Number "number"

%%

input: expr { value = $1; }
;

expr: expr OpAdd term { $$ = $1 + $3; }
      | term { $$ = $1; }
;

term: term OpMult factor { $$ = $1 * $3;  }
      | factor { $$ = $1; }
;

factor: OpenPar expr ClosePar { $$ = $2; }
      | Number { $$ = $1; }
;