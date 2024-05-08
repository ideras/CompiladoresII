#include "ExprParser.hpp"

int ExprParser::parse()
{
    return yyparse(lexer, value);
}