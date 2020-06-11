#pragma once

#include "z3-solver.hpp"

class matrix {
  public:

    matrix(std::vector<std::vector<std::string>> mat) {
      for(auto x: mat) {
        std::vector<z3::expr> row;
        for(auto y: x) {
          row.push_back(stringToZ3(y).simplify());
        }
        (this->mat).push_back(row);
      } 
      dimensions = std::make_pair(mat.size(), mat[0].size());
    } 

    matrix(int m, int n) {
      (this->dimensions) = std::make_pair(m, n);
      for(int i = 0; i < m; ++i) {
        std::vector<z3::expr> row;
        for(int j = 0; j < n; ++j) {
          row.push_back(ctx.int_val("0"));
        }
        mat.push_back(row);
      }
    }

    std::pair<int, int> getDimensions() {
      return dimensions;
    }

    z3::expr get(int x, int y) {
      assert(x >= 0 && x < dimensions.first);
      assert(y >= 0 && y < dimensions.second);
      return mat[x][y];
    }

    void set(int x, int y, z3::expr val) {
      assert(x >= 0 && x < dimensions.first);
      assert(y >= 0 && y < dimensions.second);
      mat[x][y] = val.simplify();
    }

    matrix operator+(matrix other) {
      assert(dimensions == other.getDimensions()); 
      matrix result(dimensions.first, dimensions.second);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < dimensions.second; ++j) {
          result.set(i, j, get(i, j) + other.get(i, j));
        }
      }
      return result;
    }

    matrix operator-(matrix other) {
      assert(dimensions == other.getDimensions()); 
      matrix result(dimensions.first, dimensions.second);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < dimensions.second; ++j) {
          result.set(i, j, get(i, j) - other.get(i, j));
        }
      }
      return result;
    }

    matrix operator*(matrix other) {
      auto other_dimensions = other.getDimensions();
      assert(dimensions.second == other_dimensions.first);
      matrix result(dimensions.first, other_dimensions.second);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < other_dimensions.second; ++j) {
          for(int k = 0; k < dimensions.second; ++k) {
            z3::expr val = result.get(i, j);
            result.set(i, j, val + get(i, k) * other.get(k, j));
          }
        }
      }
      return result;
    }

    z3::expr operator==(matrix other) {
      assert(dimensions == other.getDimensions());
      z3::expr result(ctx);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < dimensions.second; ++j) {
          if(i == 0 && j == 0) { result = get(i, j) == other.get(i, j);  } else {
            result = result && (get(i, j) == other.get(i, j));
          }       
        }
      }
      return result;
    }

    z3::expr operator!=(matrix other) {
      assert(dimensions == other.getDimensions());
      z3::expr result(ctx);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < dimensions.second; ++j) {
          if(i == 0 && j == 0) { result = get(i, j) != other.get(i, j);  } else {
            result = result && (get(i, j) != other.get(i, j));
          }       
        }
      }
      return result;
    }


    void transpose() {
      matrix res(dimensions.second, dimensions.first);
      for(int i = 0; i < dimensions.first; ++i) {
        for(int j = 0; j < dimensions.second; ++j) {
          res.set(j, i, get(i, j));
        }
      }
      (*this) = res;
    }

  private:

    std::vector<std::vector<z3::expr>> mat;
    std::pair<int, int> dimensions;
};

