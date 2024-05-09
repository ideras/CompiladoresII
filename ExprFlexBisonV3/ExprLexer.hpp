#ifndef __ExprLexer_HPP__
#define __ExprLexer_HPP__

#include <iosfwd>
#include <string>
#include "ExprParserImpl.hpp"

enum class Token: int {
    Eof = 0,
    Error = 256,
    Undef = 257,
    OpAdd = 258,
    OpMult = 259,
    OpenPar = 260,
    ClosePar = 261,
    Number = 262,
    Ident = 263
};

class ExprLexer
{
public:
    using yyscan_t = void*;

public:
    ExprLexer(std::istream& _in);
    ~ExprLexer();

    Token nextToken(ParserValueType *lval)
    { return nextTokenHelper(yyscanner, lval); }

    std::string text() const;

    static const char *tokenString(Token tk);

private:
    Token nextTokenHelper(yyscan_t yyscanner, ParserValueType *lval);

private:
    std::istream& in;
    yyscan_t yyscanner;
};

#endif
