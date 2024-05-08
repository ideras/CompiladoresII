#ifndef __EXPR_PARSER_HPP__
#define __EXPR_PARSER_HPP__

#include "ExprParserImpl.hpp"
#include "ExprLexer.hpp"

class ExprParser
{
public:
    ExprParser(ExprLexer& lexer)
      : lexer(lexer)
    {}

    int parse();

    int getValue() const
    { return value; }

private:
    int value;
    ExprLexer& lexer;
};

#endif
