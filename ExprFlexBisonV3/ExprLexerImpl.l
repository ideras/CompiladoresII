%option noyywrap
%option reentrant
%option yylineno
%option extra-type = "std::istream *"

%{
#include <iostream>
#include <cstdlib>
#include "ExprLexer.hpp"

#define YY_DECL Token ExprLexer::nextTokenHelper(yyscan_t yyscanner, ParserValueType *lval)
#define yyterminate() return Token::Eof

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
"+"		{ return Token::OpAdd; }
"*"		{ return Token::OpMult; }
"("		{ return Token::OpenPar; }
")"		{ return Token::ClosePar; }
[0-9]+(\.[0-9]+)?	{ *lval = std::atof(yytext); return Token::Number; }
[a-zA-Z_][a-zA-Z0-9_]*	{ *lval = std::string(yytext); return Token::Ident; }
.		{ std::cerr << "Invalid symbol: " << yytext[0] << '\n'; return Token::Error; }

<comment>"*/" { BEGIN(INITIAL); }
<comment>.|\n { /* Nothing */ }
<comment><<EOF>> { std::cerr << "Warning: Block comment without close\n";  }
%%
