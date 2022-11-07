#include "ASTPostfixStmt.h"
#include "ASTVisitor.h"

void ASTPostfixStmt::accept(ASTVisitor * visitor) {
    if (visitor->visit(this)) {
        getExpr()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::vector<std::shared_ptr<ASTNode>> ASTPostfixStmt::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(expr);
    return children;
}

std::ostream& ASTPostfixStmt::print(std::ostream &out) const {
    out << *getExpr() << getOp() << ";";
    return out;
}

llvm::Value* ASTPostfixStmt::codegen() {
    return nullptr;
}