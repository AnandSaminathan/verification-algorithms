#pragma once

#include "verification-algorithms/common/verifier.hpp"

class IC3 : public Verifier {
  public:
  
    bool check(std::string) override;

    inline int getLength() override {   }
    inline z3::model getTrace() override {   }

  private:

    void declare();

}
