#pragma once

#include "ASTExpr.h"

/*! \brief Class for array constructors.
 */

class ASTArrayConstructorExpr : public ASTExpr {
  bool implicit;
  std::vector<std::shared_ptr<ASTExpr>> elements = {};

public:
  ASTArrayConstructorExpr(std::vector<std::unique_ptr<ASTExpr>> elements,
                          bool implicit);
  void accept(ASTVisitor *visitor) override;
  std::vector<ASTExpr *> getElements() const;
  bool isImplicit() const { return implicit; }
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
