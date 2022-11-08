#include "ASTBuilder.h"

#include "picosha2.h"

#include "loguru.hpp"
#include <functional>
#include <vector>

using namespace antlrcpp;

ASTBuilder::ASTBuilder(TIPParser *p) : parser{p} {}

std::string ASTBuilder::opString(int op) {
  std::string opStr;
  switch (op) {
  case TIPParser::MUL:
    opStr = "*";
    break;
  case TIPParser::DIV:
    opStr = "/";
    break;
  case TIPParser::ADD:
    opStr = "+";
    break;
  case TIPParser::SUB:
    opStr = "-";
    break;
  case TIPParser::GT:
    opStr = ">";
    break;
  case TIPParser::EQ:
    opStr = "==";
    break;
  case TIPParser::NE:
    opStr = "!=";
    break;
  case TIPParser::GTE:
    opStr = ">=";
    break;
  case TIPParser::LT:
    opStr = "<";
    break;
  case TIPParser::LTE:
    opStr = "<=";
    break;
  case TIPParser::LAND:
    opStr = "and";
    break;
  case TIPParser::LOR:
    opStr = "or";
    break;
  case TIPParser::LNOT:
    opStr = "not";
    break;
  case TIPParser::MOD:
    opStr = "%";
    break;
  case TIPParser::DEC:
    opStr = "--";
    break;
  case TIPParser::INC:
    opStr = "++";
    break;
  default:
    throw std::runtime_error(
        "unknown operator :" +
        std::string(ASTBuilder::parser->getVocabulary().getLiteralName(op)));
  }
  return opStr;
}

/*
 * Globals for communicating information up from visited subtrees
 * These are overwritten by every visit call.
 * We use multiple variables here to avoid downcasting of unique smart pointers.
 */
static std::unique_ptr<ASTStmt> visitedStmt = nullptr;
static std::unique_ptr<ASTDeclNode> visitedDeclNode = nullptr;
static std::unique_ptr<ASTDeclStmt> visitedDeclStmt = nullptr;
static std::unique_ptr<ASTExpr> visitedExpr = nullptr;
static std::unique_ptr<ASTFieldExpr> visitedFieldExpr = nullptr;
static std::unique_ptr<ASTFunction> visitedFunction = nullptr;

/**********************************************************************
 * These methods override selected methods in the TIPBaseVisitor.
 *
 * For each rule name in an ANTLR4 grammar a visit method and a
 * "context" class is generated.  The visit methods are defined in
 * TIPBaseVisitor.h and the context classes in TIPParser.h
 *
 * Only the methods for grammar rules that "directly" contain
 * content that must be processed need to be overridden.  For example,
 * for strings that match "program" you need to process the list of
 * functions.
 *
 * If you are new to visitors, it is very important to understand
 * that since you are selectively overriding methods you cannot
 * rely on the call stack to return values (since the values will
 * be lost by the methods you don't override).  Instead you must create
 * your own structure that is local to the visitor to communicate between
 * the calls during the visit.  In the case of this visitor it is the
 * visitedX variables above.
 *
 * Note that the visit methods are required to return a value, but
 * we make no use of that value, so we simply return the empty string ("")
 * since we cannot return a nullptr (leads to a crash in the visitor).
 *
 * Consult context class definitions to understand the type definitions
 * of the fields that contain the program elements captured during the parse.
 * You will access these from the method overrides in your visitor.
 */

std::unique_ptr<ASTProgram> ASTBuilder::build(TIPParser::ProgramContext *ctx) {
  std::vector<std::unique_ptr<ASTFunction>> pFunctions;
  for (auto fn : ctx->function()) {
    visit(fn);
    pFunctions.push_back(std::move(visitedFunction));
  }

  auto prog = std::make_unique<ASTProgram>(std::move(pFunctions));
  prog->setName(generateSHA256(ctx->getText()));
  return prog;
}

Any ASTBuilder::visitFunction(TIPParser::FunctionContext *ctx) {
  std::unique_ptr<ASTDeclNode> fName;
  std::vector<std::unique_ptr<ASTDeclNode>> fParams;
  std::vector<std::unique_ptr<ASTDeclStmt>> fDecls;
  std::vector<std::unique_ptr<ASTStmt>> fBody;

  bool firstId = true;
  for (auto decl : ctx->nameDeclaration()) {
    visit(decl);
    if (firstId) {
      firstId = !firstId;
      fName = std::move(visitedDeclNode);
    } else {
      fParams.push_back(std::move(visitedDeclNode));
    }
  }

  for (auto decl : ctx->declaration()) {
    visit(decl);
    fDecls.push_back(std::move(visitedDeclStmt));
  }

  for (auto stmt : ctx->statement()) {
    visit(stmt);
    fBody.push_back(std::move(visitedStmt));
  }

  // return statement is always the last statement in a TIP function body
  visit(ctx->returnStmt());
  fBody.push_back(std::move(visitedStmt));

  visitedFunction =
      std::make_unique<ASTFunction>(std::move(fName), std::move(fParams),
                                    std::move(fDecls), std::move(fBody));

  LOG_S(1) << "Built AST node for function " << *visitedFunction;

  // Set source location
  visitedFunction->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

/*
 * Unfortunately, the context types for binary expressions generated
 * by ANTLR are not organized into a sub-type hierarchy.  If they were
 * we could have a single method to construct binary expression nodes,
 * but as it stands we have some repetitive code to handle the different
 * context types.
 *
 * This might be improved by restructuring the grammar, but then another
 * mechanism for handling operator precedence would be needed.
 */
template <typename T>
void ASTBuilder::visitBinaryExpr(T *ctx, const std::string &op) {
  visit(ctx->expr(0));
  auto lhs = std::move(visitedExpr);

  visit(ctx->expr(1));
  auto rhs = std::move(visitedExpr);

  visitedExpr =
      std::make_unique<ASTBinaryExpr>(op, std::move(lhs), std::move(rhs));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
}

Any ASTBuilder::visitAdditiveExpr(TIPParser::AdditiveExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRelationalExpr(TIPParser::RelationalExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitMultiplicativeExpr(
    TIPParser::MultiplicativeExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitEqualityExpr(TIPParser::EqualityExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitParenExpr(TIPParser::ParenExprContext *ctx) {
  visit(ctx->expr());
  // leave visitedExpr from expr unchanged
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNumExpr(TIPParser::NumExprContext *ctx) {
  int val = std::stoi(ctx->NUMBER()->getText());
  visitedExpr = std::make_unique<ASTNumberExpr>(val);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitVarExpr(TIPParser::VarExprContext *ctx) {
  std::string name = ctx->IDENTIFIER()->getText();
  visitedExpr = std::make_unique<ASTVariableExpr>(name);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitInputExpr(TIPParser::InputExprContext *ctx) {
  visitedExpr = std::make_unique<ASTInputExpr>();

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitFunAppExpr(TIPParser::FunAppExprContext *ctx) {
  std::unique_ptr<ASTExpr> fExpr = nullptr;
  std::vector<std::unique_ptr<ASTExpr>> fArgs;

  // First expression is the function, the rest are the args
  bool first = true;
  for (auto e : ctx->expr()) {
    visit(e);
    if (first) {
      fExpr = std::move(visitedExpr);
      first = false;
    } else {
      fArgs.push_back(std::move(visitedExpr));
    }
  }

  visitedExpr =
      std::make_unique<ASTFunAppExpr>(std::move(fExpr), std::move(fArgs));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitAllocExpr(TIPParser::AllocExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_unique<ASTAllocExpr>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRefExpr(TIPParser::RefExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_unique<ASTRefExpr>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitDeRefExpr(TIPParser::DeRefExprContext *ctx) {
  visit(ctx->expr());
  visitedExpr = std::make_unique<ASTDeRefExpr>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNullExpr(TIPParser::NullExprContext *ctx) {
  visitedExpr = std::make_unique<ASTNullExpr>();

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitRecordExpr(TIPParser::RecordExprContext *ctx) {
  std::vector<std::unique_ptr<ASTFieldExpr>> rFields;
  for (auto fn : ctx->fieldExpr()) {
    visit(fn);
    rFields.push_back(std::move(visitedFieldExpr));
  }

  visitedExpr = std::make_unique<ASTRecordExpr>(std::move(rFields));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitFieldExpr(TIPParser::FieldExprContext *ctx) {
  std::string fName = ctx->IDENTIFIER()->getText();
  visit(ctx->expr());
  visitedFieldExpr =
      std::make_unique<ASTFieldExpr>(fName, std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedFieldExpr->setLocation(ctx->getStart()->getLine(),
                                ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitAccessExpr(TIPParser::AccessExprContext *ctx) {
  std::string fName = ctx->IDENTIFIER()->getText();

  visit(ctx->expr());
  auto rExpr = std::move(visitedExpr);

  visitedExpr = std::make_unique<ASTAccessExpr>(std::move(rExpr), fName);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitDeclaration(TIPParser::DeclarationContext *ctx) {
  std::vector<std::unique_ptr<ASTDeclNode>> dVars;
  for (auto decl : ctx->nameDeclaration()) {
    visit(decl);
    dVars.push_back(std::move(visitedDeclNode));
  }
  visitedDeclStmt = std::make_unique<ASTDeclStmt>(std::move(dVars));

  LOG_S(1) << "Built AST node " << *visitedDeclStmt;

  // Set source location
  visitedDeclStmt->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitNameDeclaration(TIPParser::NameDeclarationContext *ctx) {
  std::string name = ctx->IDENTIFIER()->getText();
  visitedDeclNode = std::make_unique<ASTDeclNode>(name);

  LOG_S(1) << "Built AST node " << *visitedDeclNode;

  // Set source location
  visitedDeclNode->setLocation(ctx->getStart()->getLine(),
                               ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitBlockStmt(TIPParser::BlockStmtContext *ctx) {
  std::vector<std::unique_ptr<ASTStmt>> bStmts;
  for (auto s : ctx->statement()) {
    visit(s);
    bStmts.push_back(std::move(visitedStmt));
  }
  visitedStmt = std::make_unique<ASTBlockStmt>(std::move(bStmts));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitWhileStmt(TIPParser::WhileStmtContext *ctx) {
  visit(ctx->expr());
  auto cond = std::move(visitedExpr);
  visit(ctx->statement());
  auto body = std::move(visitedStmt);
  visitedStmt =
      std::make_unique<ASTWhileStmt>(std::move(cond), std::move(body));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitIfStmt(TIPParser::IfStmtContext *ctx) {
  visit(ctx->expr());
  auto cond = std::move(visitedExpr);
  visit(ctx->statement(0));
  auto thenBody = std::move(visitedStmt);

  // else is optional
  std::unique_ptr<ASTStmt> elseBody = nullptr;
  if (ctx->statement().size() == 2) {
    visit(ctx->statement(1));
    elseBody = std::move(visitedStmt);
  }

  visitedStmt = std::make_unique<ASTIfStmt>(
      std::move(cond), std::move(thenBody), std::move(elseBody));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

Any ASTBuilder::visitOutputStmt(TIPParser::OutputStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_unique<ASTOutputStmt>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitErrorStmt(TIPParser::ErrorStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_unique<ASTErrorStmt>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitReturnStmt(TIPParser::ReturnStmtContext *ctx) {
  visit(ctx->expr());
  visitedStmt = std::make_unique<ASTReturnStmt>(std::move(visitedExpr));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitAssignStmt(TIPParser::AssignStmtContext *ctx) {
  visit(ctx->expr(0));
  auto lhs = std::move(visitedExpr);
  visit(ctx->expr(1));
  auto rhs = std::move(visitedExpr);
  visitedStmt = std::make_unique<ASTAssignStmt>(std::move(lhs), std::move(rhs));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
}

std::string ASTBuilder::generateSHA256(std::string tohash) {
  std::vector<unsigned char> hash(picosha2::k_digest_size);
  picosha2::hash256(tohash.begin(), tohash.end(), hash.begin(), hash.end());
  return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}

/*
 * Begin new ASTBuilder methods for SIP extension for Deliverable 2
 */

Any ASTBuilder::visitArrayConstructorExpr(
    TIPParser::ArrayConstructorExprContext *ctx) {
  /*
   * Because both array types are represented by the same expression type
   * in the grammar, we need to check the type of the array being constructed.
   * This is done by checking if ctx->array()->OF() is null or not.
   * If the OF() is null, then the array is implicitly constructed (e.g. [1 of
   * 2]). If the OF() is not null, then the array is explicitly constructed
   * (e.g. [1, 2, 3]).
   *
   * We double check the parser if correct, by ensuring OF()->getText() == "of".
   * Our parser is case-sensitive, so we only check the lowercase version.
   */
  bool implicit = (ctx->array()->OF()->getText() == "of") ? true : false;
  std::vector<std::unique_ptr<ASTExpr>> arrayExprs;

  if (implicit) {
    for (auto e : ctx->array()->expr()) {
      visit(e);
      arrayExprs.push_back(std::move(visitedExpr));
    }
  } else {
    for (auto e : ctx->array()->expr()) {
      visit(e);
      arrayExprs.push_back(std::move(visitedExpr));
    }
  } // LCOV_EXCL_LINE

  visitedExpr = std::make_unique<ASTArrayConstructorExpr>(std::move(arrayExprs),
                                                          implicit);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitArrayLengthExpr(TIPParser::ArrayLengthExprContext *ctx) {
  visit(ctx->expr());
  auto array = std::move(visitedExpr);
  visitedExpr = std::make_unique<ASTArrayLengthExpr>(std::move(array));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitArraySubscriptExpr(
    TIPParser::ArraySubscriptExprContext *ctx) {
  visit(ctx->expr(0));
  auto array = std::move(visitedExpr);
  visit(ctx->expr(1));
  auto index = std::move(visitedExpr);
  visitedExpr = std::make_unique<ASTArraySubscriptExpr>(std::move(array),
                                                        std::move(index));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitBooleanExpr(TIPParser::BooleanExprContext *ctx) {
  bool value = ctx->BOOLEAN()->getText() == "true" ? true : false;
  visitedExpr = std::make_unique<ASTBooleanExpr>(value);

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

// visitForStmt
Any ASTBuilder::visitForStmt(TIPParser::ForStmtContext *ctx) {
  /*
   * ForStmt is similar to arrayConstructorExpr, in that we need to check
   * if the for loop is range-based or interator-based. This is done by
   * checking if our token ".." (DDOT) is null or not. We can also check
   * if E3 is nullptr. If DDOT is not null, then the for loop is range-based.
   * We also check if our "by" (BY) token is null or not. If BY is not null,
   * then the range-based for loop also has a step value (E4).
   */

  // Check if range-based or iterator-based
  bool rangeBased = (ctx->DDOT() != nullptr) ? true : false;
  bool step = (ctx->BY() != nullptr) ? true : false;

  // Grab the body of the for loop either way
  visit(ctx->statement());
  auto body = std::move(visitedStmt);

  // range-based for loop
  if (rangeBased) {
    visit(ctx->expr(0));
    auto E1 = std::move(visitedExpr);
    visit(ctx->expr(1));
    auto E2 = std::move(visitedExpr);
    visit(ctx->expr(2));
    auto E3 = std::move(visitedExpr);
    // If step is true, then we need to grab E4
    if (step) {
      visit(ctx->expr(3));
      auto E4 = std::move(visitedExpr);
      visitedStmt = std::make_unique<ASTForStmt>(std::move(E1), std::move(E2),
                                                 std::move(E3), std::move(E4),
                                                 std::move(body));
    } else {
      visitedStmt =
          std::make_unique<ASTForStmt>(std::move(E1), std::move(E2),
                                       std::move(E3), nullptr, std::move(body));
    }
  }
  // iterator-based for loop
  else {
    visit(ctx->expr(0));
    auto E1 = std::move(visitedExpr);
    visit(ctx->expr(1));
    auto E2 = std::move(visitedExpr);
    visitedStmt = std::make_unique<ASTForStmt>(
        std::move(E1), std::move(E2), nullptr, nullptr, std::move(body));
  }

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitPostfixStmt(TIPParser::PostfixStmtContext *ctx) {
  visit(ctx->expr());
  auto expr = std::move(visitedExpr);
  visitedStmt = std::make_unique<ASTPostfixStmt>(std::move(expr),
                                                 opString(ctx->op->getType()));

  LOG_S(1) << "Built AST node " << *visitedStmt;

  // Set source location
  visitedStmt->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitTernaryExpr(TIPParser::TernaryExprContext *ctx) {
  visit(ctx->expr(0));
  auto E1 = std::move(visitedExpr);
  visit(ctx->expr(1));
  auto E2 = std::move(visitedExpr);
  visit(ctx->expr(2));
  auto E3 = std::move(visitedExpr);
  visitedExpr = std::make_unique<ASTTernaryExpr>(std::move(E1), std::move(E2),
                                                 std::move(E3));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitLogicalAndExpr(TIPParser::LogicalAndExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitLogicalOrExpr(TIPParser::LogicalOrExprContext *ctx) {
  visitBinaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

template <typename T>
void ASTBuilder::visitUnaryExpr(T *ctx, const std::string &op) {
  visit(ctx->expr());
  auto expr = std::move(visitedExpr);
  visitedExpr = std::make_unique<ASTUnaryExpr>(op, std::move(expr));

  LOG_S(1) << "Built AST node " << *visitedExpr;

  // Set source location
  visitedExpr->setLocation(ctx->getStart()->getLine(),
                           ctx->getStart()->getCharPositionInLine());
} // LCOV_EXCL_LINE

Any ASTBuilder::visitNegExpr(TIPParser::NegExprContext *ctx) {
  visitUnaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE

Any ASTBuilder::visitLogicalNotExpr(TIPParser::LogicalNotExprContext *ctx) {
  visitUnaryExpr(ctx, opString(ctx->op->getType()));
  return "";
} // LCOV_EXCL_LINE