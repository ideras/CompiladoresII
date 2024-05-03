#ifndef __ExprLexer_HPP__
#define __ExprLexer_HPP__

#include <iosfwd>
#include <string>
#include "ExprParserImpl.h"

class ExprLexer
{
    using yyscan_t = void*;
public:
    ExprLexer(std::istream& _in);
    ~ExprLexer();

    yytokentype nextToken()
    { return nextTokenHelper(yyscanner); }

    std::string text() const;

    static const char *tokenString(yytokentype tk);

private:
    yytokentype nextTokenHelper(yyscan_t yyscanner);

private:
    std::istream& in;
    yyscan_t yyscanner;
};

#endif
