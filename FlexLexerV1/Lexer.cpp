#include <fstream>
#include "Lexer.hpp"
#include "LexerImpl.h"

Lexer::Lexer(std::istream& _in)
  : in(_in)
{
    yylex_init_extra(reinterpret_cast<void *>(&in), &yyscanner);
}

Lexer::~Lexer()
{
    yylex_destroy(yyscanner);
}

std::string Lexer::text() const
{
    return std::string(yyget_text(yyscanner));
}

const char *Lexer::tokenString(Token tk)
{
    switch (tk)
    {
        case Token::Eof: return "TkEof";
        case Token::Hex: return "TkHex";
        case Token::Dec: return "TkDec";
        case Token::Ident: return "TkIdent";
        default:
            return "Unknown";
    }
}
