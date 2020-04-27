#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Trace {
  public:

    Trace() {  }
    Trace(int varsPerState) { (this->varsPerState) = varsPerState; }

    inline void addState(std::vector<std::string> state) { states.emplace_back(state); }
    inline std::vector<std::vector<std::string>> getStates() { return states;  }
    inline void reverseTrace() { std::reverse(states.begin(), states.end());  }

  private:
    
    int varsPerState;
    std::vector<std::vector<std::string>> states; 
};

