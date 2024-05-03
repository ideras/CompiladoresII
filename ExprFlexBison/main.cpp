#include <iostream>
#include <fstream>
#include "ExprParserImpl.h"
#include "ExprLexer.hpp"

extern bool error;
extern int value;

std::ifstream in;
ExprLexer lexer(in);

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        std::cerr << "Not enough CLI arguments\n";
        return 1;
    }
    in.open(argv[1], std::ios::in);

    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }
    yyparse();
    if (!error) {
        std::cout << "Expression value: " << value << '\n';
    }
}
