#include "antlr4-runtime.h"
#include "FormulaLexer.h"
#include "FormulaParser.h"

using namespace antlr4;

int main() {
  ANTLRInputStream input("G((a && !b && !c) || (!a && b && !c) || (!a && !b && c))");
  FormulaLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  FormulaParser parser(&tokens);

  tree::ParseTree *tree = parser.ltlForm();
  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
}
