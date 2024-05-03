%option noyywrap
%option reentrant
%option yylineno
%option extra-type = "std::istream *"

%{
#include <iostream>
#include <string>
#include "ExprParserImpl.h"
#include "ExprLexer.hpp"

#define YY_DECL yytokentype ExprLexer::nextTokenHelper(yyscan_t yyscanner)
#define yyterminate() return YYEOF

#define YY_INPUT(buf, result, max_size) \
    { \
        auto *in = yyget_extra(yyscanner); \
        in->read(buf, max_size); \
        result = in->gcount(); \
    }
%}

%x comment

%%
[ \t\n]	{  }
"//"[^\n]*\n { }
"/*" { BEGIN(comment); }
"+"		{ return OpAdd; }
"*"		{ return OpMult; }
"("		{ return OpenPar; }
")"		{ return ClosePar; }
[0-9]+	{ yylval = std::stoi(yytext); return Number; }
.		{ std::cerr << "Invalid symbol\n"; }

<comment>"*/" { BEGIN(INITIAL); }
<comment>.|\n { /* Nothing */ }
<comment><<EOF>> { std::cerr << "Warning: Block comment without close\n";  }
%%
