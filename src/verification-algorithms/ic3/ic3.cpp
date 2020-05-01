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

CNF getCube(const z3::expr_vector& x, const z3::model& assign) {
  CNF cube;
  for(int i = 0; i < x.size(); ++i) {
    z3::func_decl f = (x[i]).decl();
    if(assign.has_interp(f)) {
      z3::expr interp = assign.get_const_interp(f);
      cube.addClause(f() == interp);
    } 
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

void IC3::generateTrace(z3::model& assign) {
  std::vector<std::string> state;
  for(int i = 0; i < x.size(); ++i) {
    z3::expr res = assign.eval(x[i]);
    state.emplace_back(res.to_string());
  }
  trace.addState(state);
}

bool IC3::check(std::string property) {
  frames.clear();
  P = stringToZ3(property);

  z3::solver s(ctx);
  z3::check_result res1;
  std::vector<std::vector<bool>> moved;

  frames.emplace_back(CNF());
  moved.emplace_back(std::vector<bool>(I.getClauseCount(), false));
  frames[0] = I;

  while(true) {
    s.push();
      s.add((frames.back())() && !P);
      res1 = s.check();
    s.pop();
    if(res1 == z3::unsat) {
      frames.emplace_back(CNF());
      moved.emplace_back(std::vector<bool>(1, true));
      
      for(int j = 0; j < frames.size() - 1; ++j) {
        auto clauses = frames[j].getClauses();
        for(int c = 0; c < clauses.size(); ++c) {
          z3::expr clause = clauses[c];
          if(moved[j][c] == false) {
            s.push();
              z3::expr clausep = clause.substitute(x, next_x);
              s.add(frames[j]() && T && !clausep);
              res1 = s.check();
            s.pop();
            if(res1 == z3::unsat) {
              moved[j][c] = true;
              frames[j + 1].addClause(clause);
              moved[j + 1].emplace_back(false);
            }
          } 
        } 
        s.push();
          s.add(!(frames[j]() == frames[j + 1]()));
          res1 = s.check();
        s.pop();
        if(res1 == z3::unsat) {
          result = true;
          stoppedAt = frames.size() - 1;
          return true;
        }
      }
    } else { 
      z3::model assign = s.get_model();
      CNF cube = getCube(x, assign);
      int j = frames.size() - 2;
      trace = Trace();
      generateTrace(assign);
      while(j >= 0) {
        s.push();
          z3::expr cubep = (cube()).substitute(x, next_x);
          s.add(frames[j]() && T && cubep);
          res1 = s.check();
        s.pop();
        if(res1 == z3::sat) {
          assign = s.get_model();
          generateTrace(assign);
          cube = getCube(x, assign);
          j = j - 1;
        } else {
          z3::expr negCube = negateCube(cube);
          frames[j + 1].addClause(negCube);
          moved[j + 1].emplace_back(false);
          break;
        }
      }
      if(j == -1 || frames.size() == 1) {
        result = false;
        stoppedAt = frames.size();
        trace.reverseTrace();
        trace.setSymbols(getSymbolNames(symbols));
        return false;
      }
    }  
  }
}

