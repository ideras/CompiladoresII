#ifndef __EXPR_PARSER_HPP__
#define __EXPR_PARSER_HPP__

#include "ExprParserImpl.hpp"
#include "ExprLexer.hpp"
#include "ExprAst.hpp"

class ExprParser
{
public:
    ExprParser(ExprLexer& lexer)
      : lexer(lexer)
    {}

    int parse();

    void setNode(AstNode *_root)
    { root = _root; }

    AstNode *getNode() const
    { return root; }

    ExprLexer& getLexer()
    { return lexer; }

private:
    AstNode *root;
    ExprLexer& lexer;
};

#endif
