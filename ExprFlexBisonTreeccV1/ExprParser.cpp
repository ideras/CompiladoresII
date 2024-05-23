#include <unordered_map>
#include "ExprParser.hpp"

int ExprParser::parse()
{
    return yyparse(*this);
}
