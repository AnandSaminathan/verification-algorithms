#pragma once

#include <vector>

#include "verification-algorithms/common/verifier.hpp"
#include "verification-algorithms/common/symbol.hpp"

class PnetCoverability : public Verifier {
  public:

    PnetCoverability(std::vector<Symbol> symbols, std::vector<std::string> m0, std::vector<std::vector<std::string>> incidence_matrix) : incidence(incidence_matrix), 
  symbols(symbols),
  places(symbols.size()),
  transitions(incidence_matrix[0].size()),
  m0(std::vector<std::vector<std::string>>({m0})),
  marking(1, places),
  count(1, transitions) { incidence.transpose(); }

    bool check(std::string) override;

  private:

    void declare();

    z3::expr P;
    matrix m0;
    matrix incidence;
    matrix marking;
    matrix count;

    int places;
    int transitions;
    std::vector<Symbol> symbols;
}

