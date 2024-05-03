#include <fstream>
#include "ExprLexer.hpp"
#include "ExprLexerImpl.h"

ExprLexer::ExprLexer(std::istream& _in)
  : in(_in)
{
    yylex_init_extra(&in, &yyscanner);
}

ExprLexer::~ExprLexer()
{
    yylex_destroy(yyscanner);
}

std::string ExprLexer::text() const
{
    return std::string(yyget_text(yyscanner));
}

const char *ExprLexer::tokenString(yytokentype tk)
{
    return "Unknown";
}
