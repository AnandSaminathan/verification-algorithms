#include "verification-algorithms/ic3/ic3.hpp"

TEST_CASE("example from https://ece.uwaterloo.ca/~vganesh/TEACHING/W2013/SATSMT/IC3.pdf", "[ic3]") {

  Symbol a(bool_const, "a");
  Symbol b(bool_const, "b");
  Symbol c(bool_const, "c");

  std::vector<Symbol> symbols;
  symbols.push_back(a);
  symbols.push_back(b);
  symbols.push_back(c);

  std::string I = "(a && b && !c)";
  std::string T = "(next_c || !a) && (!next_c || a) && (!next_b || b) && (!next_a || !a || !b) && (next_a || a || !c) && (next_a || b || !c)";

  IC3 i(symbols, I, T);
  std::string P;

  SECTION("property is at least one false") {
    P = "(!a || !b || !c)";
    REQUIRE(i.check(P) == true);
  }

  SECTION("property is at least one true") {
    P = "(a || b || c)";
    REQUIRE(i.check(P) == true);
  }
}

