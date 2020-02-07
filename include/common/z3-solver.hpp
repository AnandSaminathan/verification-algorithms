#pragma once

#include <z3++.h>
#include <map>
#include "symbol.hpp"

extern z3::context ctx;
extern std::map<std::string, Symbol> symbolTable;

extern z3::expr stringToZ3(std::string);
extern z3::expr addOrGetSymbol(Symbol);
