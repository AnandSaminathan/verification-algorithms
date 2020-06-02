#include "verification-algorithms/ltl-bmc/ltl-bmc.hpp"


void ltlBmc::declare() {
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

z3::expr_vector ltlBmc::globalStateAt(int k) {
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

z3::expr ltlBmc::translationWithoutLoop(FormulaNode root, int i, int k) {

  std::string content = root.getContent();

  if(content == "()") { return ( translationWithoutLoop(root.getChild(0), i, k) ); }
  if(content == "!") { return !translationWithoutLoop(root.getChild(0), i, k); }
  if(content == "&&") { return translationWithoutLoop(root.getChild(0), i, k) && translationWithoutLoop(root.getChild(1), i, k); }
  if(content == "||") { return translationWithoutLoop(root.getChild(0), i, k) || translationWithoutLoop(root.getChild(1), i, k); }
  if(content == "G") { return getZ3Val("bool", "false"); }
  
  if(content == "F") {
    z3::expr result(ctx);
    FormulaNode child = root.getChild(0);
    for(int j = i; j <= k; ++j) {
      z3::expr cur = translationWithoutLoop(child, j, k);
      if(j == i) { result = (cur); }
      else { result = result || (cur); }
    }
    return result;
  }

  if(content == "X") {
    if(i < k) { return translationWithoutLoop(root.getChild(0), i + 1, k); } 
    else { return getZ3Val("bool", "false"); }
  }

  if(content == "U") {
    z3::expr result(ctx);
    FormulaNode leftChild = root.getChild(0);
    FormulaNode rightChild = root.getChild(1);
    for(int j = i; j <= k; ++j) {
      z3::expr cur = translationWithoutLoop(rightChild, j, k);
      for(int n = i; n <= j - 1; ++n) { cur = cur && translationWithoutLoop(leftChild, n, k); }
      if(j == i) { result = (cur); }
      else { result = result || (cur); }
    }
    return result;
  }

  if(content == "R") {
    z3::expr result(ctx);
    FormulaNode leftChild = root.getChild(0);
    FormulaNode rightChild = root.getChild(1);
    for(int j = i; j <= k; ++j) {
      z3::expr cur = translationWithoutLoop(leftChild, j, k);
      for(int n = i; n <= j; ++n) { cur = cur && translationWithoutLoop(rightChild, n, k); }
      if(j == i) { result = (cur); }
      else result = result || (cur);
    }
    return result;    
  }

  if(content == "==") {
    return translationWithoutLoop(root.getChild(0), i, k) == translationWithoutLoop(root.getChild(1), i, k);
  }

  if(content == "!=") {
    return translationWithoutLoop(root.getChild(0), i, k) != translationWithoutLoop(root.getChild(1), i, k); 
  }

  z3::expr result = construct(root);
  result = result.substitute(x, globalStates[i]);

  return result;
}

z3::expr ltlBmc::translationWithLoop(FormulaNode root, int i, int k, int l) {

  std::string content = root.getContent();

  if(content == "()") { return ( translationWithLoop(root.getChild(0), i, k, l) ); }
  if(content == "!") { return !translationWithLoop(root.getChild(0), i, k, l); }
  if(content == "&&") { return translationWithLoop(root.getChild(0), i, k, l) && translationWithLoop(root.getChild(1), i, k, l); }
  if(content == "||") { return translationWithLoop(root.getChild(0), i, k, l) || translationWithLoop(root.getChild(1), i, k, l); }

  if(content == "G") {
    z3::expr result(ctx);
    int start = std::min(i, l);
    FormulaNode child = root.getChild(0);
    for(int j = start; j <= k; ++j) {
      z3::expr cur = translationWithLoop(child, j, k, l);
      if(j == start) {  result = (cur); }
      else { result = result && (cur); }
    }
    return result;
  }

  if(content == "F") {
    z3::expr result(ctx);
    int start = std::min(i, l);
    FormulaNode child = root.getChild(0);
    for(int j = start; j <= k; ++j) {
      z3::expr cur = translationWithLoop(child, j, k, l);
      if(j == start) { result = (cur); }
      else { result = result || (cur); }
    }
    return result;
  }

  if(content == "X") {
    if(i < k) { return translationWithLoop(root.getChild(0), i + 1, k, l); }
    else { return translationWithLoop(root.getChild(0), l, k, l); }
  }

  if(content == "U") {
    z3::expr result(ctx);
    FormulaNode leftChild = root.getChild(0);
    FormulaNode rightChild = root.getChild(1);
    for(int j = i; j <= k; ++j) {
      z3::expr cur = translationWithLoop(rightChild, j, k, l);
      for(int n = i; n <= j - 1; ++n) { cur = cur && translationWithLoop(leftChild, n, k, l); }
      if(j == i) { result = (cur); }
      else { result = result || (cur); }
    }

    for(int j = l; j <= i - 1; ++j) {
      z3::expr cur = translationWithLoop(rightChild, j, k, l);
      for(int n = i; n <= k; ++n) { cur = cur && translationWithLoop(leftChild, n, k, l); }
      for(int n = l; n <= j - 1; ++n) { cur = cur && translationWithLoop(leftChild, n, k, l); }
      result = result || (cur);
    }

    return result;
  }

  if(content == "R") {
    z3::expr result(ctx);
    FormulaNode leftChild = root.getChild(0);
    FormulaNode rightChild = root.getChild(1);

    int start = std::min(i, l);
    for(int j = start; j <= k; ++j) {
      z3::expr cur = translationWithLoop(rightChild, j, k, l);
      if(j == start) { result = cur; }
      else { result = result && (cur); }
    } 
    result = (result); 

    for(int j = i; j <= k; ++j) {
      z3::expr cur = translationWithLoop(leftChild, j, k, l);
      for(int n = i; n <= j; ++n) { cur = cur && translationWithLoop(rightChild, n, k, l); }
      result = result || (cur);
    }

    for(int j = l; j <= i - 1; ++j) {
      z3::expr cur = translationWithLoop(leftChild, j, k, l);
      for(int n = i; n <= k; ++n) { cur = cur && translationWithLoop(rightChild, n, k, l); }
      for(int n = l; n <= j; ++n) { cur = cur && translationWithLoop(rightChild, n, k, l); }
      result = result || (cur);
    }

    return result;
  }

  if(content == "==") {
    return translationWithLoop(root.getChild(0), i, k, l) == translationWithLoop(root.getChild(1), i, k, l);
  }

  if(content == "!=") {
    return translationWithLoop(root.getChild(0), i, k, l) != translationWithLoop(root.getChild(1), i, k, l); 
  }

  z3::expr result = construct(root);
  result = result.substitute(x, globalStates[i]);

  return result;
}

z3::expr ltlBmc::generalTranslation(z3::expr& withoutLoop, FormulaNode propertyRoot, int k) {
  includeGlobalState(k);
  if(k == 0) { withoutLoop = (this->initialState()); }
  else { withoutLoop = withoutLoop && (transition(globalStates[k - 1], globalStates[k])); }

  z3::expr withLoop = (!(loopCondition(k)) && translationWithoutLoop(propertyRoot, 0, k));
  for(int l = 0; l <= k; ++l) {
    withLoop = withLoop || (loopCondition(k, l) && translationWithLoop(propertyRoot, 0, k, l));
  }

  return withoutLoop && (withLoop);
}


void ltlBmc::generateTrace(z3::model& assign) {
  for(int i = 0; i <= stoppedAt; ++i) {
    std::vector<std::string> state;
    for(int j = 0; j < varsPerState; ++j) {
      z3::expr res = assign.eval(globalStates[i][j]);
      state.emplace_back(res.to_string());
    }
    trace.addState(state);
  }
}

bool ltlBmc::check(std::string property) {
  trace = Trace();
  FormulaTree propertyTree("!(" + property + ")");
  propertyTree.makeNNF();
  FormulaNode propertyRoot = propertyTree.getNNFRoot();
  
  z3::expr withoutLoop(ctx);
  z3::solver s(ctx);

  int k = 0;
  while(k <= bound) {
    z3::expr currentTranslation = generalTranslation(withoutLoop, propertyRoot, k);
    s.push();
      s.add(currentTranslation);
      if(s.check() == z3::sat) {
        stoppedAt = k;
        result = false;
        z3::model assign = s.get_model();
        generateTrace(assign);
        trace.setSymbols(getSymbolNames(symbols)); 
        return false;
      }
    s.pop();
    k = k + 1;
  }

  result = true;
  stoppedAt = bound;
  return true;
}
