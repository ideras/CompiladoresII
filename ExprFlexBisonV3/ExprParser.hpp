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

    void setValue(double _value)
    { value = _value; }

    double getValue() const
    { return value; }

    ExprLexer& getLexer()
    { return lexer; }

    double constValue(const std::string& cname) const;

private:
    double value;
    ExprLexer& lexer;
};

#endif
