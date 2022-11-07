#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

class ASTPostfixStmt : public ASTStmt {
    std::string op;
    std::shared_ptr<ASTExpr> expr;

public:
    ASTPostfixStmt(std::unique_ptr<ASTExpr> expr, std::string op) : expr(std::move(expr)), op(op) {}
    std::string getOp() const { return op; }
    ASTExpr* getExpr() const { return expr.get(); }
    void accept(ASTVisitor * visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    llvm::Value* codegen() override;

protected:
    std::ostream& print(std::ostream &out) const override;
};
    