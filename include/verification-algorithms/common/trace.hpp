#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Trace {
  public:

    Trace() {  }
    Trace(int varsPerState) { (this->varsPerState) = varsPerState; }

    inline void addState(std::vector<std::string> state) { states.emplace_back(state); }
    inline void setSymbols(std::vector<std::string> symbols) { (this->symbols) = symbols;  }
    inline std::vector<std::vector<std::string>> getStates() { return states;  }
    inline void reverseTrace() { std::reverse(states.begin(), states.end());  }

    inline std::vector<std::string> getSymbols() { return symbols;  } 

  private:
    
    int varsPerState;
    std::vector<std::vector<std::string>> states; 
    std::vector<std::string> symbols;
};

