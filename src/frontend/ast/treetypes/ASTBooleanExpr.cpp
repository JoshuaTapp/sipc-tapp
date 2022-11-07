#include "ASTBooleanExpr.h"
#include "ASTVisitor.h"

#include <iostream>

void ASTBooleanExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
    visitor->endVisit(this);
}

std::ostream &ASTBooleanExpr::print(std::ostream &out) const
{
    return getValue() ? out << "true" : out << "false";
}

llvm::Value *ASTBooleanExpr::codegen()
{
    return nullptr;
}
