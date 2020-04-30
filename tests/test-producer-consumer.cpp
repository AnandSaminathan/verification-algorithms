#include "verification-algorithms/k-induction/k-induction.hpp"
#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"
#include "verification-algorithms/ic3/ic3.hpp"

SCENARIO("producer consumer with propositional logic", "[producer-consumer]") {

  std::vector<Symbol> symbols;
  for(int i = 1; i <= 6; ++i) {
    char ic = (i + '0');
    std::string var = "p";
    var += ic;
    Symbol pi(int_const, var);
    symbols.push_back(pi);
  }

  std::string I = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)"; 

  std::string t[5];
  t[1] = "((p1 >= 1) && (next_p1 == p1 - 1 && next_p2 == p2 + 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 && next_p6 == p6))";
  t[2] = "((p2 >= 1 && p6 >= 1) && (next_p1 == p1 + 1 && next_p2 == p2 - 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 + 1 && next_p6 == p6 - 1))";
  t[3] = "((p5 >= 1 && p3 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 - 1 && next_p4 == p4 + 1 && next_p5 == p5 - 1 && next_p6 == p6 + 1))";
  t[4] = "((p4 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 + 1 && next_p4 == p4 - 1 && next_p5 == p5 && next_p6 == p6))";

  std::string T = "";
  for(int i = 1; i <= 4; ++i) {
    std::string clause = "(" + t[i];
    for(int j = 1; j <= 4; ++j) {
      if(j != i) {
       clause += " && !(" + t[j] + ")";
      }
    }
    clause += ")";
    if(i == 1) T = clause;
    else T += " || " + clause;
  }

  GIVEN("safety properties (for kinduction)") {
    kInduction k(symbols, I, T);
    std::string P;

    WHEN("property is all non-negative") {
      P = "(p1 >= 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
      }
    }

    WHEN("property is at least one positive") {
      P = "(p1 > 0 || p2 > 0 || p3 > 0 || p4 > 0 || p5 > 0 || p6 > 0)";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
      }
    }

    WHEN("property is p1 negative") {
      P = "(p1 < 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";

      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is all positive") {
      P = "(p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0 && p5 > 0 && p6 > 0)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is alwaysI") {
      P = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is p1Positive") {
      P = "(p1 > 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }
  } 
}

SCENARIO("producer consumer with pseudo-boolean formula", "[producer-consumer]") {

  std::vector<Symbol> symbols;
  for(int i = 1; i <= 6; ++i) {
    char ic = (i + '0');
    std::string var = "p";
    var += ic;
    Symbol pi(int_const, var);
    symbols.push_back(pi);
  }

  std::string I = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)"; 

  std::string t[5];
  t[1] = "((p1 >= 1) && (next_p1 == p1 - 1 && next_p2 == p2 + 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 && next_p6 == p6))";
  t[2] = "((p2 >= 1 && p6 >= 1) && (next_p1 == p1 + 1 && next_p2 == p2 - 1 && next_p3 == p3 && next_p4 == p4 && next_p5 == p5 + 1 && next_p6 == p6 - 1))";
  t[3] = "((p5 >= 1 && p3 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 - 1 && next_p4 == p4 + 1 && next_p5 == p5 - 1 && next_p6 == p6 + 1))";
  t[4] = "((p4 >= 1) && (next_p1 == p1 && next_p2 == p2 && next_p3 == p3 + 1 && next_p4 == p4 - 1 && next_p5 == p5 && next_p6 == p6))";

  std::string T = "";
  for(int i = 1; i <= 4; ++i) {
    if(i != 4) { T = T + t[i] + " + ";  }
    else { T = T + t[i] + " == 1";  }
  }
  GIVEN("safety properties (for kinduction)") {
    kInduction k(symbols, I, T);
    std::string P;

    WHEN("property is all non-negative") {
      P = "(p1 >= 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
      }
    }

    WHEN("property is at least one positive") {
      P = "(p1 > 0 || p2 > 0 || p3 > 0 || p4 > 0 || p5 > 0 || p6 > 0)";
      THEN("property holds") {
        REQUIRE(k.check(P) == true);
      }
    }

    WHEN("property is p1 negative") {
      P = "(p1 < 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";

      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is all positive") {
      P = "(p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0 && p5 > 0 && p6 > 0)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is alwaysI") {
      P = "(p1 == 1 && p2 == 0 && p3 == 1 && p4 == 0 && p5 == 0 && p6 == 1)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }

    WHEN("property is p1Positive") {
      P = "(p1 > 0 && p2 >= 0 && p3 >= 0 && p4 >= 0 && p5 >= 0 && p6 >= 0)";
      THEN("property does not hold") {
        REQUIRE(k.check(P) == false);
      }
    }
  } 
}
