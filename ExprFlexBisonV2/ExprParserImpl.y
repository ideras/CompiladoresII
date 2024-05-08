
%define parse.error verbose
%define api.pure full

%parse-param {ExprLexer& lexer}
%parse-param {int& value}

%code top {

#include <iostream>
#include <stdexcept>
#include "ExprLexerImpl.h"
#include "ExprLexer.hpp"

#define yylex(v) static_cast<int>(lexer.nextToken(v))

void yyerror(const ExprLexer& lexer, int& value, const char *msg)
{
      throw std::runtime_error(msg);
}

}

%code requires {
#include "ExprLexer.hpp"
}

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