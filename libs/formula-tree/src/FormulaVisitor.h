#pragma once

#include "FormulaLexer.h"
#include "FormulaParser.h"
#include "FormulaParserBaseVisitor.h"
#include "formula-tree/formula-tree.h"

#include "antlr4-runtime.h"

class FormulaVisitor : public FormulaParserBaseVisitor {
  public:

    antlrcpp::Any visitLtlUnary(FormulaParser::LtlUnaryContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->formula); children.push_back(node);
      makeNode((ctx->op)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitLtlBinary(FormulaParser::LtlBinaryContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->left); children.push_back(node);
      visit(ctx->right); children.push_back(node);
      makeNode((ctx->op)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitLtlParanthesis(FormulaParser::LtlParanthesisContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->formula); children.push_back(node);
      makeNode("()", children);

      return nullptr;
    }

    antlrcpp::Any visitRelationalId(FormulaParser::RelationalIdContext *ctx) override {
      std::vector<FormulaNode*> children;
      makeNode((ctx->name)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitRelationalValue(FormulaParser::RelationalValueContext *ctx) override {
      std::vector<FormulaNode*> children;
      makeNode((ctx->value)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitRelationalParanthesis(FormulaParser::RelationalParanthesisContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->formula); children.push_back(node);
      makeNode("()", children);    

      return nullptr;
    }

    antlrcpp::Any visitRelationalBinary(FormulaParser::RelationalBinaryContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->left); children.push_back(node);
      visit(ctx->right); children.push_back(node);
      makeNode((ctx->op)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitArithmeticParanthesis(FormulaParser::ArithmeticParanthesisContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->formula); children.push_back(node);
      makeNode("()", children);

      return nullptr;
    }

    antlrcpp::Any visitArithmeticId(FormulaParser::ArithmeticIdContext *ctx) override {
      std::vector<FormulaNode*> children;
      makeNode((ctx->name)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitArithmeticValue(FormulaParser::ArithmeticValueContext *ctx) override {
      std::vector<FormulaNode*> children;
      makeNode((ctx->value)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitArithmeticBinary(FormulaParser::ArithmeticBinaryContext *ctx) override {
      std::vector<FormulaNode*> children;
      visit(ctx->left); children.push_back(node);
      visit(ctx->right); children.push_back(node);
      makeNode((ctx->op)->getText(), children);

      return nullptr;
    }

    antlrcpp::Any visitAtomicProposition(FormulaParser::AtomicPropositionContext *ctx) override {
      return visit(ctx->relationalForm());

      return nullptr;
    }

    FormulaNode* getNode() {
      return node;
    }

  private:

    FormulaNode *node;
    void makeNode(std::string content, std::vector<FormulaNode*> children) {
      node = new FormulaNode(content, children);
    }
};
