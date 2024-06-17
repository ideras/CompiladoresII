#include <iostream>
#include <fstream>
#include "ExprLexer.hpp"
#include "ExprParser.hpp"
#include "ExprAst.hpp"

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        std::cerr << "Not enough CLI arguments\n";
        return 1;
    }
    std::ifstream in(argv[1], std::ios::in);

    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    ExprLexer lexer(in);
    ExprParser parser(lexer);

    // Values taken from https://en.wikipedia.org/wiki/List_of_mathematical_constants
    static SymbolTable cmap = {
        {"Pi", 3.14159}, // Ratio of a circle's circumference to its diameter
        {"Tau", 6.28319}, // Ratio of a circle's circumference to its radius
        {"SrTwo", 1.41421}, // Square root of 2. Pythagoras constant
        {"SrThree", 1.73205}, // Square root of 3. Theodorus' constant
        {"Phi", 1.61803}, // Golden ratio
        {"E", 2.71828}, // Euler's number
    };

    try {
        parser.parse();
        const std::vector<AstNode *>& stmts = parser.getStmts();

        SymbolTable symb_tbl;
        for (const auto& s : stmts) {
            s->eval(symb_tbl);
        }
    }
    catch (const std::runtime_error& ex) {
        std::cerr << ex.what() << '\n';
    }
}