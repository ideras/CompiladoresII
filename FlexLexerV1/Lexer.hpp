#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <iosfwd>
#include <string>

enum class Token {
    Eof,
    Hex,
    Dec,
    Ident
};

class Lexer
{
    using yyscan_t = void*;
public:
    Lexer(std::istream& _in);
    ~Lexer();

    Token nextToken()
    { return nextTokenHelper(yyscanner); }

    std::string text() const;

    static const char *tokenString(Token tk);

private:
    Token nextTokenHelper(yyscan_t yyscanner);

private:
    std::istream& in;
    yyscan_t yyscanner;
};

#endif
