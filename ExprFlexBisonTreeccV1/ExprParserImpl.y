
%define parse.error verbose
%define api.pure full

%parse-param {ExprParser& parser}

%code top {

#include <iostream>
#include <stdexcept>
#include "ExprLexer.hpp"
#include "ExprParser.hpp"

#define yylex(v) static_cast<int>(parser.getLexer().nextToken(v))

void yyerror(const ExprParser& parser, const char *msg)
{
      throw std::runtime_error(msg);
}

}

%code requires {
#include <string>
#include "ExprAst.hpp"

class ExprParser; // Forward declaration

using ParserValueType = AstNode *;

#define YYSTYPE ParserValueType
#define YYSTYPE_IS_DECLARED 1

}

%token OpAdd "+"
%token OpMult "*"
%token OpenPar "("
%token ClosePar ")"
%token Number "number"
%token Ident "identifier"

%%

input: expr { parser.setNode($1); }
;

expr: expr OpAdd term { $$ = new AddExpr($1, $3); }
      | term { $$ = $1; }
;

term: term OpMult factor { $$ = new MulExpr($1, $3);  }
      | factor { $$ = $1; }
;

factor: OpenPar expr ClosePar { $$ = $2; }
      | Number { $$ = $1; }
      | Ident  {
            $$ = $1;
      }
;