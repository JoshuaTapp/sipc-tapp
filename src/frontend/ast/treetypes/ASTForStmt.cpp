#include "ASTForStmt.h"
#include "ASTVisitor.h"

void ASTForStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getE1()->accept(visitor);
    getE2()->accept(visitor);
    if (getE3() != nullptr) {
      getE3()->accept(visitor);

      if (getE4() != nullptr) {
        getE4()->accept(visitor);
      }
    }
    getBody()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTForStmt::print(std::ostream &out) const {
  out << "for (" << *getE1() << " : " << *getE2();
  if (getE3() != nullptr) {
    out << " .. " << *getE3();
  }
  if (getE4() != nullptr) {
    out << " by " << *getE4();
  }
  out << ") " << *getBody();
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(E1);
  children.push_back(E2);

  if (E3 != nullptr) {
    children.push_back(E3);
    if (E4 != nullptr) {
      children.push_back(E4);
    }
  }

  children.push_back(body);
  return children;
}
