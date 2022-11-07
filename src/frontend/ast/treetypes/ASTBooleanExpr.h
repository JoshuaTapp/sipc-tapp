#pragma once

#include "ASTExpr.h"

/*! \brief Class for boolean literals.
 */

class ASTBooleanExpr : public ASTExpr
{
    bool value;

public:
    ASTBooleanExpr(bool value) : value(value) {}
    bool getValue() const { return value; }
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};