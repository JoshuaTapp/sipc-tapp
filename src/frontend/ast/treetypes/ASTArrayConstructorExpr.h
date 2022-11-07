#pragma once

#include "ASTExpr.h"

/*! \brief Class for array constructors.
*/

class ASTArrayConstructorExpr : public ASTExpr {
    std::vector<std::shared_ptr<ASTExpr>> elements;
    bool implicit;

public:
    ASTArrayConstructorExpr(std::vector<std::shared_ptr<ASTExpr>> elements, bool implicit) : elements(std::move(elements)), implicit(implicit) {}
    void accept(ASTVisitor * visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    std::vector<std::shared_ptr<ASTExpr>> getElements() { return elements; }
    bool isImplicit() { return implicit; }
    llvm::Value * codegen() override;

protected:
    std::ostream& print(std::ostream &out) const override;
};
