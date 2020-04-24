#include "verification-algorithms/ic3/ic3.hpp" 

void IC3::declare() {
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

CNF IC3::getCube(z3::model& assign) {
  CNF cube;
  for(int i = 0; i < assign.size(); ++i) {
    z3::func_decl f = assign[i];
    z3::expr interp = assign.get_const_interp(f);
    cube.addClause(f() == interp);
  }
  return cube;
}

z3::expr negateCube(CNF cube) {
  auto clauses = cube.getClauses();
  z3::expr form(ctx);
  for(int i = 0; i < clauses.size(); ++i) {
    if(i == 0) { form = !clauses[i]; }
    else { form = form || !clauses[i]; }
  }
  return form;
}

bool IC3::check(std::string property) {
  P = stringToZ3(property);

  int n = 0;
  z3::solver s(ctx);
  z3::check_result res1;

  frames.emplace_back(CNF());
  frames[0] = I;

  while(true) {
    s.push();
      s.add(frames[n]() && !P);
      res1 = s.check();
    s.pop();
    if(res1 == z3::unsat) {
      frames.emplace_back(CNF());
      for(int j = 0; j <= n; ++j) {
        auto clauses = frames[j].getClauses();
        for(auto clause : clauses) {
          s.push();
            z3::expr clausep = clause.substitute(x, next_x);
            s.add(frames[j]() && T && !clausep);
            res1 = s.check();
          s.pop();
          if(res1 == z3::unsat) {
            frames[j + 1].addClause(clause);
          }
        } 
        s.push();
          s.add(!(frames[j]() == frames[j + 1]()));
          res1 = s.check();
        s.pop();
        if(res1 == z3::unsat) {
          result = true;
          stoppedAt = n;
          return true;
        }
      }
      n = n + 1;
    } else {
      z3::model assign = s.get_model();
      CNF cube = getCube(assign);
      int j = n - 1;
      while(j >= 0) {
        s.push();
          z3::expr cubep = (cube()).substitute(x, next_x);
          s.add(frames[j]() && T && cubep);
          res1 = s.check();
        s.pop();
        if(res1 == z3::unsat) {
          frames[j].addClause(negateCube(cube));
          break;
        } else {
          assign = s.get_model();
          cube = getCube(assign);
          j = j - 1;
        }
      }
      if(j == -1) {
        result = false;
        stoppedAt = n;
        return false;
      }
    }
  }
}

