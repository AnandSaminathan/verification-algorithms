#include "kripke-structure.hpp"
#include <string>
#include <vector>

class kInduction {
  public:

    kInduction(std::vector<std::string> variables, KripkeStructure K) {
      this->variables = variables;
      this->K = K;
    }
    
    bool check(std::string property);
    KripkeStructure 

  private:

    std::vector<std::string> variables;
    KripkeStructure K;
};
