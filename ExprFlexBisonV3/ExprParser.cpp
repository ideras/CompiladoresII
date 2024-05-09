#include <unordered_map>
#include "ExprParser.hpp"

int ExprParser::parse()
{
    return yyparse(*this);
}

double ExprParser::constValue(const std::string& cname) const
{
    // Values taken from https://en.wikipedia.org/wiki/List_of_mathematical_constants
    static std::unordered_map<std::string, double> cmap = {
        {"Pi", 3.14159}, // Ratio of a circle's circumference to its diameter
        {"Tau", 6.28319}, // Ratio of a circle's circumference to its radius
        {"SrTwo", 1.41421}, // Square root of 2. Pythagoras constant
        {"SrThree", 1.73205}, // Square root of 3. Theodorus' constant
        {"Phi", 1.61803}, // Golden ratio
        {"E", 2.71828}, // Euler's number
    };

    auto it = cmap.find(cname);
    return (it == cmap.end())? 0.0 : it->second;
}