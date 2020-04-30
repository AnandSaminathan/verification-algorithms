#include "catch2/catch.hpp"

#include "verification-algorithms/k-induction/k-induction.hpp"
#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"
#include "verification-algorithms/ic3/ic3.hpp"


SCENARIO("three bit ring counter", "[3bit-ring-counter]") {
  Symbol a(bool_const, "a");
  Symbol b(bool_const, "b");
  Symbol c(bool_const, "c");

  std::vector<Symbol> symbols;
  symbols.push_back(a);
  symbols.push_back(b);
  symbols.push_back(c);

  std::string I = "(a && !b && !c)";
  std::string T = "((next_a == c) && (next_b == a) && (next_c == b))";


  GIVEN("safety properties (for kInduction and ic3)") {
    kInduction k(symbols, I, T);
    IC3 i(symbols, I, T);
    std::string P;

    WHEN("property is oneHigh") {
      P = "((a && !b && !c) || (!a && b && !c) || (!a && !b && c))";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
        REQUIRE(i.check(P) == true);
      } 
    }

    WHEN("property is allLow") {
      P = "(!a && !b && !c)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
        REQUIRE(i.check(P) == false);
      }
    }

    WHEN("property is allHigh") {
      P = "(a && b && c)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
        REQUIRE(i.check(P) == false);
      }
    }
      
    WHEN("property is firstHigh and othersLow") {
      P = "(a && !b && !c)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
        REQUIRE(i.check(P) == false);
      }
    }

    WHEN("property is firstHigh or secondHigh and othersLow")  {
      P = "((a && !b && !c) || (!a && b && !c))";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
        REQUIRE(i.check(P) == false);
      }
    }

    WHEN("property is atleastOneHigh") {
      P = "(a || b || c)";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
        REQUIRE(i.check(P) == true);
      }
    }
  }

  GIVEN("ltl properties") {
    ltlBmc l(symbols, I, T);
    l.setBound(3);
    std::string P;

    WHEN("property is oneHigh") {
      P = "G((a == true && b == false && c == false) || (a == false && b == true && c == false) || (a == false && b == false && c == true))";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      } 
    }

    WHEN("property is allLow") {
      P = "G(a == false && b == false && c == false)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is allHigh") {
      P = "G(a == true && b == true && c == true)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }
      
    WHEN("property is firstHigh and othersLow") {
      P = "G(a == true && b == false && c == false)";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is firstHigh or secondHigh and othersLow")  {
      P = "G((a == true && b == false && c == false) || (a == false && b == true && c == false))";
      THEN("property does not hold") {
        REQUIRE(l.check(P) == false);
      }
    }

    WHEN("property is atleastOneHigh") {
      P = "G(a == true || b == true || c == true)";
      THEN("property holds") {
        REQUIRE(l.check(P) == true);
      }
    }
  } 
}
