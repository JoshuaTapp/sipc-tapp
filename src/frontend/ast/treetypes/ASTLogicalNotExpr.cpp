#include "ASTLogicalNotExpr.h"
#include "ASTVisitor.h"

void ASTLogicalNotExpr::accept(ASTVisitor * visitor) {
    if (visitor->visit(this)) {
       getExpr()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::vector<std::shared_ptr<ASTNode>> ASTLogicalNotExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(expr);
  return children;
}

std::ostream& ASTLogicalNotExpr::print(std::ostream &out) const {
    out << "not " << *expr;
    return out;
}
