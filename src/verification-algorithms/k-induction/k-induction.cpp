#include "verification-algorithms/k-induction/k-induction.hpp"

namespace verifier {
  z3::expr notEqual(z3::expr_vector &op1, z3::expr_vector &op2) {
    z3::expr res(ctx);
    
    res = (op1[0] != op2[0]);
    for(int i = 1; i < (int) (std::min(op1.size(), op2.size())); ++i) {
      res = res || (op1[i] != op2[i]);
    }
  
    return res;
  }
  
  void kInduction::declare() {
    for(auto symbol: symbols) {
      x.push_back(addOrGetSymbol(symbol));
      
      type type = symbol.getType();
      std::string name = symbol.getName();
      std::string value = symbol.getValue();
      
      std::string nextName = "next_" + name;
      Symbol nextX(type, nextName, value);
  
      next_x.push_back(addOrGetSymbol(nextX));
    }
  }
  
  z3::expr_vector kInduction::globalStateAt(int k) {
    z3::expr_vector globalState(ctx);
    std::string curState = std::to_string(k);
  
    for(auto symbol: symbols) {
      std::string name = symbol.getName();
      name += curState;
      Symbol temp(symbol.getType(), name, symbol.getValue());
      globalState.push_back(addOrGetSymbol(temp));
    }
    
    return globalState;
  }
  
  void kInduction::updateAt(int k, z3::expr& path, z3::expr& loopFree) {
    if(k == 1) {
      path = transitionAt(k);
      loopFree = notEqual(globalStates[k], globalStates[k - 1]);
    } else {
      path = path && (transitionAt(k));
      for(int i = 0; i < k; ++i) {
        loopFree = loopFree && (notEqual(globalStates[k], globalStates[i]));
      }
    }
  }
  
  void kInduction::generateTrace(z3::model& assign) {
    for(int i = 0; i <= stoppedAt; ++i) {
      std::vector<std::string> state;
      for(int j = 0; j < varsPerState; ++j) {
        z3::expr res = assign.eval(globalStates[i][j]);
        state.emplace_back(res.to_string());
      }
      trace.addState(state);
    }
  }
  
  
  bool kInduction::check(std::string property) {
    P = stringToZ3(property);
    trace = Trace();
   
    int k = 0;
    z3::solver s(ctx);
    z3::expr path(ctx);
    z3::expr loopFree(ctx);
    z3::check_result res1, res2;
  
    z3::expr I(ctx);
  
    s.push();
      includeGlobalState(k);
      I = initialState();
      s.add(I && !propertyAt(k));
      res1 = s.check();
    s.pop();
    if(res1 == z3::sat) { 
      stoppedAt = 0;
      result = false;
      z3::model assign = s.get_model();
      generateTrace(assign);
      return false; 
    }
  
    k = k + 1;
    while(k <= bound) {
      includeGlobalState(k);
      updateAt(k, path, loopFree);
  
      z3::expr Pk = propertyAt(k);
      s.push();
        s.add(I && (path && loopFree));
        res1 = s.check();
      s.pop();
      s.push();
        s.add((loopFree && path) && !Pk);
        res2 = s.check();
      s.pop();
      if(res1 == z3::unsat || res2 == z3::unsat) { 
        stoppedAt = k;
        result = true;
        return true; 
      }
  
      s.push();
        s.add(I && path && !Pk);
        res1 = s.check();
      s.pop();
      if(res1 == z3::sat) {
        stoppedAt = k;
        result = false;
        z3::model assign = s.get_model();
        generateTrace(assign);
        trace.setSymbols(getSymbolNames(symbols));
        return false;  
      }
  
      k = k + 1;
    }
  }
}




