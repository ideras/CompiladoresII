%option noyywrap
%option reentrant

%{
#include <fstream>
#include "Lexer.hpp"

#define YY_DECL Token Lexer::nextTokenHelper(yyscan_t yyscanner)
#define yyterminate() return Token::Eof

#define YY_INPUT(buf, result, max_size) \
    {  \
        auto *in = reinterpret_cast<std::istream *>(yyget_extra(yyscanner)); \
        in->read(buf, max_size); \
        result = in->gcount(); \
    }
%}


%%

[0-9]+ { return Token::Dec; }
0[xX][0-9a-fA-f]+ { return Token::Hex; }
[a-zA-Z_][0-9a-zA-Z_]+ { return Token::Ident; }
\n|. ;

%%
