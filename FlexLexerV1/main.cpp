#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "Lexer.hpp"

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        std::cerr << "Not enough CLI arguments\n";
        return 1;
    }
    std::cout << "Filename " << argv[1] << '\n';
    std::ifstream in(argv[1], std::ios::in);
    
    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 2;
    }

    Lexer lex(in);

    Token tk = lex.nextToken();
    while (tk != Token::Eof) {
        std::cout << Lexer::tokenString(tk) << ":" << lex.text() << '\n';
        tk = lex.nextToken();
    }
}