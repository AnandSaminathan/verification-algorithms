#include "verification-algorithms/common/symbol.hpp"
#include "verification-algorithms/common/matrix.hpp"
#include "verification-algorithms/k-induction/k-induction.hpp"
#include "catch.hpp"

using namespace verifier;

TEST_CASE("symbol test", "[symbol]") {

  SECTION("symbol is bool_const") {
    Symbol S(bool_const, "abcd");
    REQUIRE(S.getType() == bool_const);
    REQUIRE(S.getName() == "abcd");
  }

  SECTION("symbol is int_val") {
    Symbol T(int_val, "ddd", "23");
    REQUIRE(T.getType() == int_val);
    REQUIRE(T.getName() == "ddd");
    REQUIRE(T.getValue() == "23");
  }

  SECTION("symbol is bool_val") {
    Symbol U(bool_val, "xya");
    REQUIRE(U.getType() == bool_val);
    REQUIRE(U.getName() == "xya");
    REQUIRE(U.getValue() == "");
  }  
}

TEST_CASE("trace test", "[trace]") {
  Symbol a(bool_const, "a");
  Symbol b(bool_const, "b");
  Symbol c(bool_const, "c");

  std::vector<Symbol> symbols;
  symbols.push_back(a);
  symbols.push_back(b);
  symbols.push_back(c);

  std::string I = "(a && !b && !c)";
  std::string T = "((next_a == c) && (next_b == a) && (next_c == b))";

  kInduction k(symbols, I, T);
  std::string P;

  SECTION("property is firstOrSecondHigh") {
    P = "((a && !b && !c) || (!a && b && !c))";
    REQUIRE(k.check(P) == false);
    Trace t = k.getTrace();
    auto states = t.getStates();
    std::vector<std::string> expected[3];
    expected[0] = {"true", "false", "false"};
    expected[1] = {"false", "true", "false"};
    expected[2] = {"false", "false", "true"};
    REQUIRE(states.size() == 3);
    for(int i = 0; i < 3; ++i) {
      auto state = states[i];
      REQUIRE(state.size() == 3);
      REQUIRE(state == expected[i]);
    }
  }
}

