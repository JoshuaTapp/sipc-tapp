#include "ASTArraySubscriptExpr.h"
#include "ASTVisitor.h"

void ASTArraySubscriptExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getArray()->accept(visitor);
    getIndex()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTArraySubscriptExpr::print(std::ostream &out) const {
  return out << *getArray() << "[" << *getIndex() << "]";
}

std::vector<std::shared_ptr<ASTNode>> ASTArraySubscriptExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(array);
  children.push_back(index);
  return children;
}

llvm::Value *ASTArraySubscriptExpr::codegen() { return nullptr; }