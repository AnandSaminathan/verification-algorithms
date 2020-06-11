#include "verification-algorithms/common/symbol.hpp"
#include "verification-algorithms/common/matrix.hpp"
#include "verification-algorithms/k-induction/k-induction.hpp"
#include "catch.hpp"

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

TEST_CASE("matrix test", "[matrix]") {
  SECTION("addition") {
    std::vector<std::vector<std::string>> a(2, std::vector<std::string>(2));
    std::vector<std::vector<std::string>> b(2, std::vector<std::string>(2));
    a[0][0] = "1"; a[0][1] = "2"; a[1][0] = "3"; a[1][1] = "4";
    b[0][0] = "-2"; b[0][1] = "-2"; b[1][0] = "4"; b[1][1] = "100";
    matrix a_mat(a);
    matrix b_mat(b);
    matrix c_mat = a_mat + b_mat;
    REQUIRE(c_mat.get(0, 0) == ctx.int_val("-1"));
    REQUIRE(c_mat.get(0, 1) == ctx.int_val("0"));
    REQUIRE(c_mat.get(1, 0) == ctx.int_val("7"));
    REQUIRE(c_mat.get(1, 1) == ctx.int_val("104"));
  }

  SECTION("subtraction") {
    std::vector<std::vector<std::string>> a(2, std::vector<std::string>(2));
    std::vector<std::vector<std::string>> b(2, std::vector<std::string>(2));
    a[0][0] = "1"; a[0][1] = "2"; a[1][0] = "3"; a[1][1] = "4";
    b[0][0] = "-2"; b[0][1] = "-2"; b[1][0] = "4"; b[1][1] = "100";
    matrix a_mat(a);
    matrix b_mat(b);
    matrix c_mat = a_mat - b_mat;
    REQUIRE(c_mat.get(0, 0) == ctx.int_val("3"));
    REQUIRE(c_mat.get(0, 1) == ctx.int_val("4"));
    REQUIRE(c_mat.get(1, 0) == ctx.int_val("-1"));
    REQUIRE(c_mat.get(1, 1) == ctx.int_val("-96"));
  }


  SECTION("multiplication") {
    std::vector<std::vector<std::string>> a(2, std::vector<std::string>(2));
    std::vector<std::vector<std::string>> b(2, std::vector<std::string>(2));
    a[0][0] = "1"; a[0][1] = "2"; a[1][0] = "3"; a[1][1] = "4";
    b[0][0] = "-2"; b[0][1] = "-2"; b[1][0] = "4"; b[1][1] = "100";
    matrix a_mat(a);
    matrix b_mat(b);
    matrix c_mat = a_mat * b_mat;
    REQUIRE(c_mat.get(0, 0) == ctx.int_val("10"));
    REQUIRE(c_mat.get(0, 1) == ctx.int_val("298"));
    REQUIRE(c_mat.get(1, 0) == ctx.int_val("12"));
    REQUIRE(c_mat.get(1, 1) == ctx.int_val("396"));
  }
}

