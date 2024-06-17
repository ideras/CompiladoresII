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
    Ident = 263,
    Semicolon = 264,
    KwPrint = 265,
    OpAssign = 266,
    OpLessThan = 267,
    OpLessEqualThan = 268,
    OpGreaterThan = 269,
    OpGreaterEqualThan = 270,
    OpEqual = 271,
    OpNotEqual = 272,
    OpenBrace = 273,
    CloseBrace = 274,
    KwIf = 275,
    KwElse = 276,
    OpSub = 277
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

    long line() const;

    static const char *tokenString(Token tk);

private:
    Token nextTokenHelper(yyscan_t yyscanner, ParserValueType *lval);

private:
    std::istream& in;
    yyscan_t yyscanner;
};

#endif
