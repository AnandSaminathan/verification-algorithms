#pragma once

#include <z3++.h>
#include <map>
#include "symbol.hpp"
#include "formula-tree/formula-tree.h"

extern z3::context ctx;
extern std::map<std::string, Symbol> symbolTable;

extern z3::expr construct(FormulaNode);
extern z3::expr stringToZ3(std::string);
extern z3::expr addOrGetSymbol(Symbol, bool = true);
extern inline z3::expr getZ3Const(std::string);
extern z3::expr getZ3Val(std::string, std::string);