
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
#include <variant>

class ExprParser; // Forward declaration

using ParserValueType = std::variant<std::string, double>;

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

input: expr { parser.setValue(std::get<double>($1)); }
;

expr: expr OpAdd term { $$ = std::get<double>($1) + std::get<double>($3); }
      | term { $$ = $1; }
;

term: term OpMult factor { $$ = std::get<double>($1) * std::get<double>($3);  }
      | factor { $$ = $1; }
;

factor: OpenPar expr ClosePar { $$ = $2; }
      | Number { $$ = $1; }
      | Ident  {
            $$ = parser.constValue(std::get<std::string>($1));
      }
;