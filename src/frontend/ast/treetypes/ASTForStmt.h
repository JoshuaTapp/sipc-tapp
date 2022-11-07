#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for both Range and Iterative For statements.
 */

class ASTForStmt : public ASTStmt
{
    std::shared_ptr<ASTExpr> E1;
    std::shared_ptr<ASTExpr> E2;
    std::shared_ptr<ASTExpr> E3;
    std::shared_ptr<ASTExpr> E4;
    std::shared_ptr<ASTStmt> body;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;

    ASTForStmt(std::shared_ptr<ASTExpr> E1, std::shared_ptr<ASTExpr> E2,
               std::shared_ptr<ASTExpr> E3, std::shared_ptr<ASTExpr> E4, std::shared_ptr<ASTStmt> body)
        : E1(std::move(E1)), E2(std::move(E2)), E3(std::move(E3)), E4(std::move(E4)), body(std::move(body)) {}

    ASTExpr *getE1() const { return E1.get(); }
    ASTExpr *getE2() const { return E2.get(); }
    ASTExpr *getE3() const { return E3.get(); }
    ASTExpr *getE4() const { return E4.get(); }
    ASTStmt *getBody() const { return body.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};