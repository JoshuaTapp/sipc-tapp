#pragma once

#include "ASTExpr.h"

/*! \brief Class for the array length operator (e.g., #a).
*/

class ASTArrayLengthExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> array;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTArrayLengthExpr(std::shared_ptr<ASTExpr> array) : array(array) {}
    ASTExpr * getArray() const { return array.get(); }
    void accept(ASTVisitor * visitor) override;
    llvm::Value *codegen() override;
protected:
    std::ostream& print(std::ostream &out) const override;
};