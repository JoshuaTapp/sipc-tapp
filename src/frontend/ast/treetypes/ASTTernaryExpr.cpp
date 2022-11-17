#include "ASTTernaryExpr.h"
#include "ASTVisitor.h"

void ASTTernaryExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getCond()->accept(visitor);
    getTrueExpr()->accept(visitor);
    getFalseExpr()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTTernaryExpr::print(std::ostream &out) const {
  out << *getCond() << " ? " << *getTrueExpr() << " : " << *getFalseExpr();
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTTernaryExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(cond);
  children.push_back(trueExpr);
  children.push_back(falseExpr);
  return children;
}
