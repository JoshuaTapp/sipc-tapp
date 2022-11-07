#pragma once

#include "ASTExpr.h"

/*! \brief Class for array subscript expressions (e.g., a[1]).
*/

class ASTArraySubscriptExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> array;
    std::shared_ptr<ASTExpr> index;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTArraySubscriptExpr(std::unique_ptr<ASTExpr> array, std::unique_ptr<ASTExpr> index) : array(std::move(array)), index(std::move(index)) {}
    ASTExpr * getArray() const { return array.get(); }
    ASTExpr * getIndex() const { return index.get(); }
    void accept(ASTVisitor * visitor) override;
    llvm::Value *codegen() override;
protected:
    std::ostream& print(std::ostream &out) const override;
};