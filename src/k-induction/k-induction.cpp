#include "k-induction/k-induction.hpp"

z3::expr notEqual(z3::expr_vector &op1, z3::expr_vector &op2) {
  z3::expr res(ctx);
  
  res = (op1[0] != op2[0]);
  for(int i = 1; i < (int) (std::min(op1.size(), op2.size())); ++i) {
    res = res || (op1[i] != op2[i]);
  }

  return res;
}

void kInduction::declare(std::vector<Symbol> symbols) {
  for(auto symbol: symbols) {
    addOrGetSymbol(symbol);
    
    type type = symbol.getType();
    std::string name = symbol.getName();
    std::string value = symbol.getValue();
    
    std::string txName = "tx" + name;
    std::string tyName = "ty" + name;
    Symbol tx(type, txName, value);
    Symbol ty(type, tyName, value);

    x.push_back(addOrGetSymbol(tx));
    y.push_back(addOrGetSymbol(ty));
  }
}

z3::expr_vector kInduction::globalStateAt(int k) {
  z3::expr_vector globalState(ctx);
  std::string curState = std::to_string(k);
  int counter = 0;

  for(auto symbol: symbols) {
    std::string name = symbol.getName();
    if(k != 0) name += (curState + std::to_string(counter));
    Symbol temp(symbol.getType(), name, symbol.getValue());
    globalState.push_back(addOrGetSymbol(temp));
    counter += 1;

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

bool kInduction::check(std::string property) {
  P = stringToZ3(property);
 
  int k = 0;
  z3::solver s(ctx);
  z3::expr path(ctx);
  z3::expr loopFree(ctx);
  z3::check_result res1, res2;

  s.push();
    globalStates.push_back(globalStateAt(0));
    s.add(I && propertyAt(k));
    if(s.check() == z3::unsat) { return false; }
  s.pop();

  k = k + 1;
  while(true) {
    globalStates.push_back(globalStateAt(k));
    updateAt(k, path, loopFree);

    z3::expr Pk = propertyAt(k);
    s.push();
      s.add(I && (path && loopFree));
      res1 = s.check();
    s.pop();
    s.push();
      s.add((loopFree && path) && !Pk);
      res2 =  s.check();
      if(res1 == z3::unsat || res2 == z3::unsat) { return true; }
    s.pop();

    s.push();
      s.add(I && path && !Pk);
      res1 = s.check();
      if(res1 == z3::sat) { 
        std::cout << s.get_model() << '\n';
        return false;  
      }
    s.pop();

    k = k + 1;
  }
}





