#include "verification-algorithms/common/z3-solver.hpp"

z3::context ctx;
std::map<std::string, Symbol> symbolTable;

z3::expr addOrGetSymbol(Symbol s, bool make) {
  type symbolType = s.getType();
  std::string symbolName = s.getName();

  z3::expr symbol(ctx); 

  if(symbolType == bool_const) { symbol = ctx.bool_const(symbolName.c_str()); }
  if(symbolType == int_const) { symbol = ctx.int_const(symbolName.c_str()); }
  if(symbolType == real_const) { symbol = ctx.real_const(symbolName.c_str()); }

  if(make == true) { symbolTable[symbolName] = s; }

  return symbol;
}

z3::expr getZ3Val(std::string type, std::string val) {
  if(type == "bool") {
    if(val == "true") { return ctx.bool_val(true); }
    else if(val == "false") { return ctx.bool_val(false); }
    else { assert(val == "true" || val == "false"); }
  } 
  else if(type == "int") { return ctx.int_val(val.c_str());  }
  else if(type == "real") { return ctx.real_const(val.c_str()); }
  else { assert(type == "bool" || type == "int" || type == "real"); }
}

inline z3::expr getZ3Const(std::string name) {
  auto it = symbolTable.find(name);
  assert(it != symbolTable.end());
  return addOrGetSymbol(it->second, false);
}

z3::expr pble(z3::expr_vector& forms, std::vector<int>& coeff, int rhs) {
  int* cc = new int[coeff.size()];
  for(int i = 0; i < coeff.size(); ++i) { cc[i] = coeff[i];  }
  return z3::pble(forms, cc, rhs);
}

z3::expr pbge(z3::expr_vector& forms, std::vector<int>& coeff, int rhs) {
  int* cc = new int[coeff.size()];
  for(int i = 0; i < coeff.size(); ++i) { cc[i] = coeff[i];  }
  return z3::pbge(forms, cc, rhs);
}

z3::expr pbeq(z3::expr_vector& forms, std::vector<int>& coeff, int rhs) {
  int* cc = new int[coeff.size()];
  for(int i = 0; i < coeff.size(); ++i) { cc[i] = coeff[i];  }
  return z3::pbeq(forms, cc, rhs);
}

formulaType typeResolution(std::shared_ptr<FormulaNode> cur) {
  if(cur->isVal()) {
    std::string curType = cur->getContentType();
    return (curType == "bool") ? pl : arith;
  }

  if(cur->isLeaf()) {
    auto curType = symbolTable[cur->getContent()].getType();
    auto ret = (curType == int_const) ? arith : pl;
    cur->setSubTreeType(ret);
    return ret;
  }

  std::string content = cur->getContent();

  if(content == "()") {
    auto formType = typeResolution(cur->getPointerToChild(0));
    cur->setSubTreeType(formType);
    return formType;
  }
  
  if(content == "+" || content == "-") {
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    formulaType ret;
    if(leftType == pl || leftType == pb) {
      assert(rightType == pl || rightType == pb);
      ret = pb;
    } else {
      assert(rightType == arith);
      ret = arith;
    }
    cur->setSubTreeType(ret);
    return ret;
  }
  
  if(content == "*") {
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    formulaType ret;
    assert(leftType == arith);
    if(rightType == pl || rightType == pb) {
      ret = pb; 
    } else {
      ret = arith;
    }
    cur->setSubTreeType(ret);
    return ret;
  }

  if(content == "/" || content == "%") { 
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    assert(leftType == arith && rightType == arith);
    cur->setSubTreeType(arith);
    return arith;
  }

  if(content == "&&" || content == "||" || content == "->") {
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    assert(leftType == pb || leftType == pl);
    assert(rightType == pb || rightType == pl);
    cur->setSubTreeType(pl);
    return pl;
  }

  if(content == "!") {
    auto formType = typeResolution(cur->getPointerToChild(0));
    assert(formType == pb || formType == pl);
    cur->setSubTreeType(pl);
    return pl;
  }

  if(content == "==" || content == "!=") {
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    formulaType ret;
    if(leftType == pb) {
      assert(rightType == arith);
      ret = pb;
    } else if(leftType == pl){
      assert(rightType == pl);
      ret = pl;
    } else if(leftType == arith) {
      assert(rightType == arith);
      ret = pl;
    }
    cur->setSubTreeType(ret);
    return ret;
  }

  if(content == ">=" || content == "<=" || content == "<" || content == ">") {
    auto leftType = typeResolution(cur->getPointerToChild(0));
    auto rightType = typeResolution(cur->getPointerToChild(1));
    formulaType ret;
    assert(rightType == arith);
    if(leftType == pb || leftType == pl) {
      ret = pb; 
    } else {
      ret = pl;
    }
    cur->setSubTreeType(ret);
    return ret;
  }

}

z3::expr construct(FormulaNode cur) {

  if(cur.getSubTreeType() == pb) {
    z3::expr_vector vec(ctx);
    std::vector<int> coeff;
    return constructPb(cur, vec, coeff, false);
  }

  if(cur.isVal()) {
    return getZ3Val(cur.getContentType(), cur.getContent());
  }

  if(cur.isLeaf()) { 
    return getZ3Const(cur.getContent());
  }

  z3::expr ret(ctx);
  std::string content = cur.getContent();

  if(content == "()") { ret = ( construct(cur.getChild(0)) );  }

  if(content == "+") { ret = construct(cur.getChild(0)) + construct(cur.getChild(1));  }
  if(content == "-") { ret = construct(cur.getChild(0)) - construct(cur.getChild(1));  }
  if(content == "*") { ret = construct(cur.getChild(0)) * construct(cur.getChild(1));  }
  if(content == "/") { ret = construct(cur.getChild(0)) / construct(cur.getChild(1));  }
  if(content == "%") { ret = z3::rem(construct(cur.getChild(0)), construct(cur.getChild(1)));  }

  if(content == "!") { ret = !construct(cur.getChild(0));  }
  if(content == "&&") { ret = construct(cur.getChild(0)) && construct(cur.getChild(1));  }
  if(content == "||") { ret = construct(cur.getChild(0)) || construct(cur.getChild(1));  }
  if(content == "->") { ret = z3::implies(construct(cur.getChild(0)), construct(cur.getChild(1))); }
  if(content == "<->") { 
    z3::expr left = construct(cur.getChild(0));
    z3::expr right = construct(cur.getChild(1));
    ret = z3::implies(left, right) && z3::implies(right, left);
  }

  if(content == "==") { ret = construct(cur.getChild(0)) == construct(cur.getChild(1));  }
  if(content == "!=") { ret = construct(cur.getChild(0)) != construct(cur.getChild(1));  }
  if(content == ">") { ret = construct(cur.getChild(0)) > construct(cur.getChild(1));  }
  if(content == "<") { ret = construct(cur.getChild(0)) < construct(cur.getChild(1));  }
  if(content == ">=") { ret = construct(cur.getChild(0)) >= construct(cur.getChild(1));  }
  if(content == "<=") { ret = construct(cur.getChild(0)) <= construct(cur.getChild(1));  }

  return ret;
}

z3::expr constructPb(FormulaNode cur, z3::expr_vector& forms, std::vector<int>& coeff, bool neg = false) {
  std::string content = cur.getContent();
  if(content == "*") {
    forms.push_back(construct(cur.getChild(1)));
    int c = std::stoi((cur.getChild(0)).getContent());
    if(neg) { coeff.emplace_back(-1 * c); }
    else { coeff.emplace_back(c); }
  }

  FormulaNode child0 = cur.getChild(0);
  std::string childContent = child0.getContent();
  if(childContent == "+" || childContent == "-" || childContent == "*") { constructPb(child0, forms, coeff); }
  else { coeff.emplace_back(1); forms.push_back(construct(child0));  }

  if(content == "<=") { return pble(forms, coeff, std::stoi(cur.getChild(1).getContent())); }
  if(content == ">=") { return pbge(forms, coeff, std::stoi(cur.getChild(1).getContent())); }
  if(content == "==") { return pbeq(forms, coeff, std::stoi(cur.getChild(1).getContent())); }

  FormulaNode child1 = cur.getChild(1);
  if(child1.getContent() == "*") { constructPb(child1, forms, coeff, (content == "-")); }
  else if(content == "+") { coeff.emplace_back(1); forms.push_back(construct(child1)); } 
  else if(content == "-") { coeff.emplace_back(-1); forms.push_back(construct(child1)); }
  return getZ3Val("bool", "true");
}

z3::expr stringToZ3(std::string stringExpr) {
  FormulaTree tree(stringExpr);
  FormulaNode root = tree.getRoot();
  typeResolution(tree.getPointerToRoot());
  return construct(root);
}

