#pragma once

#include <vector>

#include "verification-algorithms/common/verifier.hpp"
#include "verification-algorithms/common/symbol.hpp"
#include "verification-algorithms/common/matrix.hpp"

class PnetCoverability : public Verifier {
  public:

    PnetCoverability(std::vector<Symbol> symbols, std::vector<std::string> m0, std::vector<std::vector<std::string>> incidence_matrix) : incidence(incidence_matrix), 
  symbols(symbols),
  places(symbols.size()),
  transitions(incidence_matrix[0].size()),
  m0(std::vector<std::vector<std::string>>({m0})),
  marking(1, symbols.size()),
  count(1, incidence_matrix[0].size()),
  P(ctx),
  marking_constraint(ctx) { 
    incidence.transpose();
    declare();
    makeMarkingConstraint();
  }

    bool check(std::string) override;

  private:

    void declare();
    void makeMarkingConstraint();
    z3::expr nonNegative(matrix&);
    void fillMatrix(matrix&, std::string);

    z3::expr P;
    z3::expr marking_constraint;
    matrix m0;
    matrix incidence;
    matrix marking;
    matrix count;

    int places;
    int transitions;
    std::vector<Symbol> symbols;
};

