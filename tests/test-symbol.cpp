#include <assert.h>
#include <string>
#include "common/symbol.hpp"

int main() {
  Symbol S(bool_const, "abcd");
  assert(S.getType() == bool_const);
  assert(S.getName() == "abcd");

  Symbol T(int_val, "ddd", "23");
  assert(T.getType() == int_val);
  assert(T.getName() == "ddd");
  assert(T.getValue() == "23");

  Symbol U(bool_val, "xya");
  assert(U.getType() == bool_val);
  assert(U.getName() == "xya");
  assert(U.getValue() == "");
}
