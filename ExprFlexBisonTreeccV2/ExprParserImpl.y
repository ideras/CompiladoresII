
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
      throw std::runtime_error("Line " + std::to_string(parser.getLexer().line()) + ":" + std::string(msg));
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
%token Semicolon ";"
%token KwPrint "print"
%token OpAssign "="
%token OpLessThan "<"
%token OpLessEqualThan "<="
%token OpGreaterThan ">"
%token OpGreaterEqualThan ">="
%token OpEqual "=="
%token OpNotEqual "!="
%token OpenBrace "{"
%token CloseBrace "}"
%token KwIf "if"
%token KwElse "else"
%token OpSub "-"

%%

input: stmt_list
;

stmt_list:  stmt_list Semicolon stmt { parser.addStmt($3); }
            | stmt { parser.addStmt($1); }
;

stmt: KwPrint expr { $$ = new PrintStmt($2); }
      | Ident OpAssign expr { $$ = new AssignStmt($1, $3); }
      | if_stmt { $$ = $1; }
;

if_stmt: KwIf OpenPar expr ClosePar 
         OpenBrace stmt CloseBrace
         KwElse
         OpenBrace stmt CloseBrace
         { $$ = new IfStmt($3, $6, $10); }
;

expr: expr_arith OpLessThan expr_arith { $$ = new LessExpr($1, $2); }
      | expr_arith OpLessEqualThan expr_arith { $$ = new LessOrEqualExpr($1, $2); }
      | expr_arith OpGreaterThan expr_arith { $$ = new GreaterExpr($1, $2); }
      | expr_arith OpGreaterEqualThan expr_arith { $$ = new GreaterOrEqualExpr($1, $2); }
      | expr_arith OpEqual expr_arith { $$ = new EqualExpr($1, $2); }
      | expr_arith OpNotEqual expr_arith { $$ = new NotEqualExpr($1, $2); }
      | expr_arith { $$ = $1; }
;

expr_arith: expr OpAdd term { $$ = new AddExpr($1, $3); }
            | expr OpSub term { $$ = new SubExpr($1, $3); }
            | term { $$ = $1; }
;

term: term OpMult factor { $$ = new MulExpr($1, $3);  }
      | factor { $$ = $1; }
;

factor: OpenPar expr ClosePar { $$ = $2; }
      | Number { $$ = $1; }
      | Ident  { $$ = $1; }
;