#include "ASTArrayLengthExpr.h"
#include "ASTVisitor.h"

void ASTArrayLengthExpr::accept(ASTVisitor * visitor) {
    if (visitor->visit(this)) {
        getArray()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream& ASTArrayLengthExpr::print(std::ostream &out) const {
    return out << "#" << *getArray();
}

std::vector<std::shared_ptr<ASTNode>> ASTArrayLengthExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(array);
    return children;
}

llvm::Value * ASTArrayLengthExpr::codegen() {
    return nullptr;
}
