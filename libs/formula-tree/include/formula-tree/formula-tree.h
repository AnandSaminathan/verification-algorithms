#pragma once

#include <string>
#include <vector>
#include <assert.h>

class FormulaNode {
  public:
    FormulaNode(std::string content, std::vector<FormulaNode*> children) {
      this->content = content;
      this->childrenCount = children.size();
      this->children = children;
    }

    inline bool isLeaf() { return (childrenCount == 0); }

    inline std::string getContent() { return content; }
    inline std::string getContentType() { return contentType; }

    inline int getChildrenCount() { return childrenCount; }
    inline FormulaNode getChild(int child) { assertChild(child); return (*children[child]); }
    
    inline void setType(std::string type) { contentType = type; }

  private:
    int childrenCount;
    std::string content;
    std::string contentType;
    std::vector<FormulaNode*> children;

    inline void assertChild(int child) { assert(child >= 0 && child < childrenCount); }
};


class FormulaTree {
  public:
    FormulaTree(std::string formula) {
      this->formula = formula;
      this->constructTree();
    }

    inline std::string getFormula() { return formula; }
    inline FormulaNode getRoot() { return (*root); }

  private:
    FormulaNode *root;
    std::string formula;
    void constructTree();
};


