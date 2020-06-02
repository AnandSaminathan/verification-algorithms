#include "verification-algorithms/k-induction/k-induction.hpp"
#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"
#include "verification-algorithms/ic3/ic3.hpp"

#include "catch.hpp"

SCENARIO("three bit shift register", "[3bit-shift-register]") {
  std::vector<Symbol> symbols;

  for(int i = 0; i <= 2; ++i) {
    std::string name = "x" + std::to_string(i);
    symbols.emplace_back(Symbol(bool_const, name));
  }

  std::string I = "(x0 == false && x1 == false && x2 == false)";
  std::string T = "(next_x0 == x1 && next_x1 == x2 && next_x2 == true)";

  GIVEN("safety properties") {
    kInduction k(symbols, I, T);
    IC3 i(symbols, I, T);
    std::string P;

    WHEN("property is allFalse") {
      P = "!x0 && !x1 && !x2";
      THEN("property does not hold"){
        REQUIRE(k.check(P) == false);
        REQUIRE(i.check(P) == false);
      }
    }
  }

  GIVEN("ltl properties") {
    ltlBmc l(symbols, I, T);
    l.setBound(3);
    std::string P;
    
    WHEN("property is always allFalse") {
      P = "G(x0 == false && x1 == false && x2 == false)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is eventuallyAllTrue") {
      P = "F(x0 == true && x1 == true && x2 == true)";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      }
    }

    WHEN("property is correctNextStep") {
      P = "X(x0 == false && x1 == false && x2 == true)";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      }
    }

    WHEN("property is wrongNextStep") {
      P = "X!(x0 == false && x1 == false && x2 == true)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is untilAllTrueAtleastOneFalse") {
      P = "!(x0 && x1 && x2) U (x0 && x1 && x2)";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      }
    }

    WHEN("property is releaseAtleastOneFalseAllTrue") {
      P = "(x0 && x1 && x2) R !(x0 && x1 && x2)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is releaseX2TrueX1false") {
      P = "(x2 R !x1)";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      }
    }
  }

}
