#include "ASTArrayConstructorExpr.h"
#include "ASTVisitor.h"

void ASTArrayConstructorExpr::accept(ASTVisitor * visitor) {
    if (visitor->visit(this)) {
        for (auto & elem : elements) {
            elem->accept(visitor);
        }
    }
    visitor->endVisit(this);
}

std::ostream& ASTArrayConstructorExpr::print(std::ostream &out) const {
    out << "[";
    if( implicit ) { out << elements[0] << " by " << elements[1]; } 
    else {
        for (auto & elem : elements) {
            out << elem << ", ";
        }
    }
    out << "]";
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTArrayConstructorExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    for (auto & elem : elements) {
        children.push_back(elem);
    }
    return children;
}

llvm::Value * ASTArrayConstructorExpr::codegen() {
    return nullptr;
}