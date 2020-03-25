#ifndef formula_tree
#define formula_tree

#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <assert.h>

class FormulaNode {
  public:
    FormulaNode(std::string& content, std::shared_ptr<std::shared_ptr<FormulaNode>[]>& children, int childrenCount)
    : content(content),
      children(children),
      childrenCount(childrenCount) { }

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
    inline std::shared_ptr<FormulaNode> getPointerToChild(int child) { assertChild(child); return (children[child]); }
    
    inline void setType(std::string type) { contentType = type; }
    inline void setContent(std::string content) { this->content = content; }
    inline void toggleIsVar() { val = true; }

  private:
    bool val{false};
    int childrenCount;
    std::string content;
    std::string contentType;
    std::shared_ptr<std::shared_ptr<FormulaNode>[]> children;

    inline void assertChild(int child) { assert(child >= 0 && child < childrenCount); }
};


class FormulaTree {
  public:
    FormulaTree(std::string formula)
    : formula(formula) {
      this->constructTree();
    }

    inline void makeNNF() { constructNNF(); }

    inline std::string getFormula() { return toString((*root)); }
    inline FormulaNode getRoot() { return (*root); }
    inline std::shared_ptr<FormulaNode> getPointerToRoot() { return (root); }
    inline FormulaNode getNNFRoot() { return (*nnfRoot); }
    void substitute(std::map<std::string, std::string>&);

  private:
    std::shared_ptr<FormulaNode> root;
    std::shared_ptr<FormulaNode> nnfRoot;
    std::string formula;
    void constructTree();
    void constructNNF();
    std::string toString(FormulaNode);
};

#endif

