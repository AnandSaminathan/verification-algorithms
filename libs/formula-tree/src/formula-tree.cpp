#include "FormulaLexer.h"
#include "FormulaParser.h"
#include "FormulaVisitor.h"

#include "antlr4-runtime.h"

#include "formula-tree/formula-tree.h"

using namespace antlr4;

void FormulaTree::constructTree() {
  ANTLRInputStream input(this->formula);
  FormulaLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  FormulaParser parser(&tokens);

  tree::ParseTree *tree = parser.ltlForm();
  FormulaVisitor visitor;
  visitor.visit(tree);
  root = visitor.getNode();
}

