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
      this->val = false;
    }

    FormulaNode(const FormulaNode& other) {
      (*this) = other;
    }

    inline bool isLeaf() { return (childrenCount == 0); }
    inline bool isVar() { return isLeaf() && !val; }
    inline bool isVal() { return isLeaf() && val; }

    inline std::string getContent() { return content; }
    inline std::string getContentType() { return contentType; }

    inline int getChildrenCount() { return childrenCount; }
    inline FormulaNode getChild(int child) { assertChild(child); return (*children[child]); }
    
    inline void setType(std::string type) { contentType = type; }
    inline void setContent(std::string content) { this->content = content; }
    inline void toggleIsVar() { val = true; }

  private:
    bool val;
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

    inline void makeNNF() { constructNNF(); }

    inline std::string getFormula() { return formula; }
    inline FormulaNode getRoot() { return (*root); }
    inline FormulaNode getNNFRoot() { return (*nnfRoot); }

  private:
    FormulaNode *root;
    FormulaNode *nnfRoot;
    std::string formula;
    void constructTree();
    void constructNNF();
};


