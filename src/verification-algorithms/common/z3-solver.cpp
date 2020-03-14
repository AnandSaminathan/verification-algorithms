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

z3::expr construct(FormulaNode cur) {

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
  if(content == "%") { ret = z3::mod(construct(cur.getChild(0)), construct(cur.getChild(1)));  }

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

z3::expr stringToZ3(std::string stringExpr) {
  FormulaTree tree(stringExpr);
  return construct(tree.getRoot());
}
