#pragma once

#include "ASTExpr.h"

class ASTLogicalNotExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> expr;

public:
    ASTLogicalNotExpr(std::unique_ptr<ASTExpr> expr) : expr(std::move(expr)) {}
    ASTExpr* getExpr() const { return expr.get(); }
    void accept(ASTVisitor * visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    llvm::Value *codegen() override;

protected:
    std::ostream& print(std::ostream &out) const override;
};
