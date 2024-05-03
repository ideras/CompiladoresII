#ifndef __ExprLexer_HPP__
#define __ExprLexer_HPP__

#include <iosfwd>
#include <string>

enum class Token: int {
    Eof = 0,
    Error = 256,
    Undef = 257,
    OpAdd = 258,
    OpMult = 259,
    OpenPar = 260,
    ClosePar = 261,
    Number = 262
};

class ExprLexer
{
public:
    using yyscan_t = void*;
    using BisonValueType = int;

public:
    ExprLexer(std::istream& _in);
    ~ExprLexer();

    Token nextToken(BisonValueType *lval)
    { return nextTokenHelper(yyscanner, lval); }

    std::string text() const;

    static const char *tokenString(Token tk);

private:
    Token nextTokenHelper(yyscan_t yyscanner, BisonValueType *lval);

private:
    std::istream& in;
    yyscan_t yyscanner;
};

#endif
