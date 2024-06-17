#ifndef __EXPR_PARSER_HPP__
#define __EXPR_PARSER_HPP__

#include <vector>
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

    void addStmt(AstNode *stmt)
    { stmts.push_back(stmt); }

    const std::vector<AstNode *>& getStmts() const
    { return stmts; }

    ExprLexer& getLexer()
    { return lexer; }

    const ExprLexer& getLexer() const
    { return lexer; }

private:
    std::vector<AstNode *> stmts;
    ExprLexer& lexer;
};

#endif
