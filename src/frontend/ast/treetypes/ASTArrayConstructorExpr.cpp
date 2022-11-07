#include "ASTArrayConstructorExpr.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

ASTArrayConstructorExpr::ASTArrayConstructorExpr(std::vector<std::unique_ptr<ASTExpr>> elements, bool implicit)
    : implicit(implicit), elements()
{
    this->implicit = implicit;

    for (auto &element : elements)
    {
        std::shared_ptr<ASTExpr> e = std::move(element);
        this->elements.push_back(e);
    }
}

std::vector<ASTExpr *> ASTArrayConstructorExpr::getElements() const
{
    return rawRefs(elements);
}

void ASTArrayConstructorExpr::accept(ASTVisitor *visitor)
{
    if (visitor->visit(this))
    {
        for (auto &elem : getElements())
        {
            elem->accept(visitor);
        }
    }
    visitor->endVisit(this);
}

std::ostream &ASTArrayConstructorExpr::print(std::ostream &out) const
{
    out << "[";
    if (implicit)
    {
        out << *elements[0] << " of " << *elements[1];
    }
    else
    {
        bool skip = true;
        for (auto &elem : getElements())
        {
            if (skip)
            {
                skip = false;
                out << *elem;
                continue;
            }
            out << ", " << *elem;
        }
    }
    out << "]";
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTArrayConstructorExpr::getChildren()
{
    std::vector<std::shared_ptr<ASTNode>> children;
    for (auto &elem : elements)
    {
        children.push_back(elem);
    }
    return children;
}

llvm::Value *ASTArrayConstructorExpr::codegen()
{
    return nullptr;
}