#include "ASTHelper.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include <sstream>
#include "ASTVisitor.h"

class RecordPostPrint : public ASTVisitor
{
public:
  std::vector<std::string> postPrintStrings;
  void record(ASTNode *element)
  {
    std::stringstream s;
    s << *element;
    postPrintStrings.push_back(s.str());
  }
  void endVisit(ASTProgram *element) { record(element); }
  void endVisit(ASTFunction *element) { record(element); }
  void endVisit(ASTNumberExpr *element) { record(element); }
  void endVisit(ASTVariableExpr *element) { record(element); }
  void endVisit(ASTBinaryExpr *element) { record(element); }
  void endVisit(ASTInputExpr *element) { record(element); }
  void endVisit(ASTFunAppExpr *element) { record(element); }
  void endVisit(ASTAllocExpr *element) { record(element); }
  void endVisit(ASTRefExpr *element) { record(element); }
  void endVisit(ASTDeRefExpr *element) { record(element); }
  void endVisit(ASTNullExpr *element) { record(element); }
  void endVisit(ASTFieldExpr *element) { record(element); }
  void endVisit(ASTRecordExpr *element) { record(element); }
  void endVisit(ASTAccessExpr *element) { record(element); }
  void endVisit(ASTDeclNode *element) { record(element); }
  void endVisit(ASTDeclStmt *element) { record(element); }
  void endVisit(ASTAssignStmt *element) { record(element); }
  void endVisit(ASTWhileStmt *element) { record(element); }
  void endVisit(ASTIfStmt *element) { record(element); }
  void endVisit(ASTOutputStmt *element) { record(element); }
  void endVisit(ASTReturnStmt *element) { record(element); }
  void endVisit(ASTErrorStmt *element) { record(element); }
  void endVisit(ASTBlockStmt *element) { record(element); }
  void endVisit(ASTArrayConstructorExpr *element) { record(element); }
  void endVisit(ASTArrayLengthExpr *element) { record(element); }
  void endVisit(ASTArraySubscriptExpr *element) { record(element); }
  void endVisit(ASTBooleanExpr *element) { record(element); }
  void endVisit(ASTPostfixStmt *element) { record(element); }
  void endVisit(ASTTernaryExpr *element) { record(element); }
  void endVisit(ASTUnaryExpr *element) { record(element); }
  void endVisit(ASTForStmt *element) { record(element); }
};

// Helper function that checks for raw node pointer in list
bool contains(std::vector<std::shared_ptr<ASTNode>> nodeList, ASTNode *nodeP)
{
  bool found = false;
  for (auto &sharedNodeP : nodeList)
  {
    if (sharedNodeP.get() == nodeP)
    {
      found = true;
      break;
    }
  }
  return found;
}

TEST_CASE("ASTNodeTest: ASTAssign", "[ASTNode]")
{
  auto rhs = std::make_unique<ASTNumberExpr>(42);
  auto lhs = std::make_unique<ASTVariableExpr>("x");

  // Record the raw pointers for these values because rhs and lhs will not be
  // usable after the call to the constructor below.  This is because of the
  // move semantics associated with unique pointers, i.e., after the move the
  // locals rhs and lhs are nullptrs
  auto rhsValue = rhs.get();
  auto lhsValue = lhs.get();

  auto assign = std::make_unique<ASTAssignStmt>(std::move(lhs), std::move(rhs));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *assign;
  REQUIRE(nodePrintStream.str() == "x = 42;");

  // Test getters
  REQUIRE(rhsValue == assign->getRHS());
  REQUIRE(lhsValue == assign->getLHS());

  // Test getChildren
  auto children = assign->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, rhsValue));
  REQUIRE(contains(children, lhsValue));

  // Test accept
  RecordPostPrint visitor;
  assign->accept(&visitor);
  std::string expected[] = {"x", "42", "x = 42;"};
  for (int i = 0; i < 3; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTAccessExpr", "[ASTNode]")
{
  auto record = std::make_unique<ASTVariableExpr>("x");
  auto field = "y";
  auto recordValue = record.get();

  auto accessExpr = std::make_unique<ASTAccessExpr>(std::move(record), field);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *accessExpr;
  REQUIRE(nodePrintStream.str() == "(x.y)");

  // Test getters
  REQUIRE(recordValue == accessExpr->getRecord());
  REQUIRE(field == accessExpr->getField());

  // Test getChildren
  auto children = accessExpr->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, recordValue));

  // Test accept
  RecordPostPrint visitor;
  accessExpr->accept(&visitor);
  std::string expected[] = {"x", "(x.y)"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTErrorStmt", "[ASTNode]")
{
  auto errorArg = std::make_unique<ASTNumberExpr>(42);
  auto errorValue = errorArg.get();

  auto errorStmt = std::make_unique<ASTErrorStmt>(std::move(errorArg));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *errorStmt;
  REQUIRE(nodePrintStream.str() == "error 42;");

  // Test getters
  REQUIRE(errorValue == errorStmt->getArg());

  // Test getChildren
  auto children = errorStmt->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, errorValue));

  // Test accept
  RecordPostPrint visitor;
  errorStmt->accept(&visitor);
  std::string expected[] = {"42", "error 42;"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

// test ASTFieldExpr
TEST_CASE("ASTNodeTest: ASTFieldExpr", "[ASTNode]")
{
  auto field = "x";
  auto init = std::make_unique<ASTNumberExpr>(42);
  auto initValue = init.get();

  auto fieldExpr = std::make_unique<ASTFieldExpr>(field, std::move(init));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *fieldExpr;
  REQUIRE(nodePrintStream.str() == "x:42");

  // Test getters
  REQUIRE(field == fieldExpr->getField());
  REQUIRE(initValue == fieldExpr->getInitializer());

  // Test getChildren
  auto children = fieldExpr->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, initValue));

  // Test accept
  RecordPostPrint visitor;
  fieldExpr->accept(&visitor);
  std::string expected[] = {"42", "x:42"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTIfStmt", "[ASTNode]")
{
  auto cond = std::make_unique<ASTBooleanExpr>(true);
  auto thenStmt = std::make_unique<ASTAssignStmt>(
      std::make_unique<ASTVariableExpr>("x"), std::make_unique<ASTNumberExpr>(42));
  auto elseStmt = std::make_unique<ASTAssignStmt>(
      std::make_unique<ASTVariableExpr>("y"), std::make_unique<ASTNumberExpr>(42));

  auto condValue = cond.get();
  auto thenValue = thenStmt.get();
  auto elseValue = elseStmt.get();

  auto ifStmt = std::make_unique<ASTIfStmt>(std::move(cond), std::move(thenStmt), std::move(elseStmt));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *ifStmt;
  REQUIRE(nodePrintStream.str() == "if (true) x = 42; else y = 42;");

  // Test getters
  REQUIRE(condValue == ifStmt->getCondition());
  REQUIRE(thenValue == ifStmt->getThen());
  REQUIRE(elseValue == ifStmt->getElse());

  // Test getChildren
  auto children = ifStmt->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, condValue));
  REQUIRE(contains(children, thenValue));
  REQUIRE(contains(children, elseValue));
}

// test ASTWhileStmt getChildren
TEST_CASE("ASTNodeTest: ASTWhileStmt", "[ASTNode]")
{
  auto cond = std::make_unique<ASTBooleanExpr>(true);
  auto body = std::make_unique<ASTAssignStmt>(
      std::make_unique<ASTVariableExpr>("x"), std::make_unique<ASTNumberExpr>(42));

  auto condValue = cond.get();
  auto bodyValue = body.get();

  auto whileStmt = std::make_unique<ASTWhileStmt>(std::move(cond), std::move(body));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *whileStmt;
  REQUIRE(nodePrintStream.str() == "while (true) x = 42;");

  // Test getters
  REQUIRE(condValue == whileStmt->getCondition());
  REQUIRE(bodyValue == whileStmt->getBody());

  // Test getChildren
  auto children = whileStmt->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, condValue));
  REQUIRE(contains(children, bodyValue));
}

// test ASTRefExpr getChildren
TEST_CASE("ASTNodeTest: ASTRefExpr", "[ASTNode]")
{
  auto ref = std::make_unique<ASTVariableExpr>("x");
  auto refValue = ref.get();

  auto refExpr = std::make_unique<ASTRefExpr>(std::move(ref));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *refExpr;
  REQUIRE(nodePrintStream.str() == "&x");

  // Test getters
  REQUIRE(refValue == refExpr->getVar());

  // Test getChildren
  auto children = refExpr->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, refValue));
}

// test ASTOutputStmt getChildren
TEST_CASE("ASTNodeTest: ASTOutputStmt", "[ASTNode]")
{
  auto output = std::make_unique<ASTVariableExpr>("x");
  auto outputValue = output.get();

  auto outputStmt = std::make_unique<ASTOutputStmt>(std::move(output));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *outputStmt;
  REQUIRE(nodePrintStream.str() == "output x;");

  // Test getters
  REQUIRE(outputValue == outputStmt->getArg());

  // Test getChildren
  auto children = outputStmt->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, outputValue));
}

/*
 * TESTS FOR NEW AST NODES SUBTYPES IMPLEMENTED FOR DELIVERABLE 2
 */

TEST_CASE("ASTNodeTest: ASTArrayConstructorExpr: explicit syntax", "[ASTNode]")
{
  auto expr1 = std::make_unique<ASTNumberExpr>(42);
  auto expr2 = std::make_unique<ASTNumberExpr>(43);
  auto expr3 = std::make_unique<ASTNumberExpr>(44);

  auto expr1Value = expr1.get();
  auto expr2Value = expr2.get();
  auto expr3Value = expr3.get();

  std::vector<std::unique_ptr<ASTExpr>> exprList;
  exprList.push_back(std::move(expr1));
  exprList.push_back(std::move(expr2));
  exprList.push_back(std::move(expr3));

  auto arrayConstructor = std::make_unique<ASTArrayConstructorExpr>(std::move(exprList), false);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arrayConstructor;
  REQUIRE(nodePrintStream.str() == "[42, 43, 44]");

  // Test getChildren
  auto children = arrayConstructor->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, expr1Value));
  REQUIRE(contains(children, expr2Value));
  REQUIRE(contains(children, expr3Value));

  // Test accept
  RecordPostPrint visitor;
  arrayConstructor->accept(&visitor);

  std::string expected[] = {"42", "43", "44", "[42, 43, 44]"};
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayConstructorExpr: implicit syntax", "[ASTNode]")
{
  auto expr1 = std::make_unique<ASTNumberExpr>(42);
  auto expr2 = std::make_unique<ASTNumberExpr>(43);

  auto expr1Value = expr1.get();
  auto expr2Value = expr2.get();

  std::vector<std::unique_ptr<ASTExpr>> exprList;
  exprList.push_back(std::move(expr1));
  exprList.push_back(std::move(expr2));

  auto arrayConstructor = std::make_unique<ASTArrayConstructorExpr>(std::move(exprList), true);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arrayConstructor;
  REQUIRE(nodePrintStream.str() == "[42 of 43]");

  // Test getChildren
  auto children = arrayConstructor->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, expr1Value));
  REQUIRE(contains(children, expr2Value));

  // Test accept
  RecordPostPrint visitor;
  arrayConstructor->accept(&visitor);

  std::string expected[] = {"42", "43", "[42 of 43]"};
  for (int i = 0; i < 3; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayLengthExpr: identifier array", "[ASTNode]")
{
  auto id = std::make_unique<ASTVariableExpr>("x");

  auto idValue = id.get();

  auto arrayLength = std::make_unique<ASTArrayLengthExpr>(std::move(id));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arrayLength;
  REQUIRE(nodePrintStream.str() == "#x");

  // Test getChildren
  auto children = arrayLength->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, idValue));

  // Test accept
  RecordPostPrint visitor;
  arrayLength->accept(&visitor);

  std::string expected[] = {"x", "#x"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayLengthExpr: array constructor", "[ASTNode]")
{
  auto expr1 = std::make_unique<ASTNumberExpr>(42);
  auto expr2 = std::make_unique<ASTNumberExpr>(43);
  auto expr3 = std::make_unique<ASTNumberExpr>(44);

  auto expr1Value = expr1.get();
  auto expr2Value = expr2.get();
  auto expr3Value = expr3.get();

  std::vector<std::unique_ptr<ASTExpr>> exprList;
  exprList.push_back(std::move(expr1));
  exprList.push_back(std::move(expr2));
  exprList.push_back(std::move(expr3));

  auto arrayConstructor = std::make_unique<ASTArrayConstructorExpr>(std::move(exprList), false);

  auto arrayConstructorValue = arrayConstructor.get();

  auto arrayLength = std::make_unique<ASTArrayLengthExpr>(std::move(arrayConstructor));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arrayLength;
  REQUIRE(nodePrintStream.str() == "#[42, 43, 44]");

  // Test getChildren
  auto children = arrayLength->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, arrayConstructorValue));

  // Test accept
  RecordPostPrint visitor;
  arrayLength->accept(&visitor);

  std::string expected[] = {"42", "43", "44", "#[42, 43, 44]"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayLengthExpr: empty array", "[ASTNode]")
{
  std::vector<std::unique_ptr<ASTExpr>> exprList;

  auto arrayConstructor = std::make_unique<ASTArrayConstructorExpr>(std::move(exprList), false);

  auto arrayConstructorValue = arrayConstructor.get();

  auto arrayLength = std::make_unique<ASTArrayLengthExpr>(std::move(arrayConstructor));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arrayLength;
  REQUIRE(nodePrintStream.str() == "#[]");

  // Test getChildren
  auto children = arrayLength->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, arrayConstructorValue));

  // Test accept
  RecordPostPrint visitor;
  arrayLength->accept(&visitor);

  std::string expected[] = {"[]", "#[]"};
  for (int i = 0; i < 1; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArraySubscriptExpr", "[ASTNode]")
{
  auto id = std::make_unique<ASTVariableExpr>("x");
  auto index = std::make_unique<ASTNumberExpr>(1);

  auto indexValue = index.get();
  auto idValue = id.get();

  auto arraySubscript = std::make_unique<ASTArraySubscriptExpr>(std::move(id), std::move(index));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *arraySubscript;
  REQUIRE(nodePrintStream.str() == "x[1]");

  // Test getChildren
  auto children = arraySubscript->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, idValue));
  REQUIRE(contains(children, indexValue));

  // Test accept
  RecordPostPrint visitor;
  arraySubscript->accept(&visitor);

  std::string expected[] = {"x", "1", "x[1]"};
  for (int i = 0; i < 3; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBooleanExpr", "[ASTNode]")
{
  auto booleanExpr = std::make_unique<ASTBooleanExpr>(true);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *booleanExpr;
  REQUIRE(nodePrintStream.str() == "true");

  // Test getChildren
  auto children = booleanExpr->getChildren();
  REQUIRE(children.size() == 0);

  // Test accept
  RecordPostPrint visitor;
  booleanExpr->accept(&visitor);

  std::string expected[] = {"true"};
  for (int i = 0; i < 1; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTForStmt: range loop, no step", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTNumberExpr>(1);
  auto E3 = std::make_unique<ASTNumberExpr>(10);

  std::vector<std::unique_ptr<ASTStmt>> stmtList;
  auto S = std::make_unique<ASTBlockStmt>(std::move(stmtList));

  auto E1Value = E1.get();
  auto E2Value = E2.get();
  auto E3Value = E3.get();
  auto SValue = S.get();

  auto forStmt = std::make_unique<ASTForStmt>(std::move(E1), std::move(E2), std::move(E3), nullptr, std::move(S));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *forStmt;
  REQUIRE(nodePrintStream.str() == "for (x : 1 .. 10) { }");

  // Test getChildren
  auto children = forStmt->getChildren();
  REQUIRE(children.size() == 4);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));
  REQUIRE(contains(children, E3Value));
  REQUIRE(contains(children, SValue));

  // Test accept
  RecordPostPrint visitor;
  forStmt->accept(&visitor);

  std::string expected[] = {"x", "1", "10", "{ }", "for (x : 1 .. 10) { }"};
  for (int i = 0; i < 5; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTForStmt: range loop, with step", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTNumberExpr>(1);
  auto E3 = std::make_unique<ASTNumberExpr>(10);
  auto E4 = std::make_unique<ASTNumberExpr>(2);

  std::vector<std::unique_ptr<ASTStmt>> stmtList;
  auto S = std::make_unique<ASTBlockStmt>(std::move(stmtList));

  auto E1Value = E1.get();
  auto E2Value = E2.get();
  auto E3Value = E3.get();
  auto E4Value = E4.get();
  auto SValue = S.get();

  auto forStmt = std::make_unique<ASTForStmt>(std::move(E1), std::move(E2), std::move(E3), std::move(E4), std::move(S));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *forStmt;
  REQUIRE(nodePrintStream.str() == "for (x : 1 .. 10 by 2) { }");

  // Test getChildren
  auto children = forStmt->getChildren();
  REQUIRE(children.size() == 5);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));
  REQUIRE(contains(children, E3Value));
  REQUIRE(contains(children, E4Value));
  REQUIRE(contains(children, SValue));

  // Test accept
  RecordPostPrint visitor;
  forStmt->accept(&visitor);

  std::string expected[] = {"x", "1", "10", "2", "{ }", "for (x : 1 .. 10 by 2) { }"};
  for (int i = 0; i < 6; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

// test ASTForStmt iterator loop
TEST_CASE("ASTNodeTest: ASTForStmt: iterator loop", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTVariableExpr>("y");

  std::vector<std::unique_ptr<ASTStmt>> stmtList;
  auto S = std::make_unique<ASTBlockStmt>(std::move(stmtList));

  auto E1Value = E1.get();
  auto E2Value = E2.get();
  auto SValue = S.get();

  auto forStmt = std::make_unique<ASTForStmt>(std::move(E1), std::move(E2), nullptr, nullptr, std::move(S));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *forStmt;
  REQUIRE(nodePrintStream.str() == "for (x : y) { }");

  // Test getChildren
  auto children = forStmt->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));
  REQUIRE(contains(children, SValue));

  // Test accept
  RecordPostPrint visitor;
  forStmt->accept(&visitor);

  std::string expected[] = {"x", "y", "{ }", "for (x : y) { }"};
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTTernaryExpr", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTNumberExpr>(1);
  auto E3 = std::make_unique<ASTNumberExpr>(2);

  auto E1Value = E1.get();
  auto E2Value = E2.get();
  auto E3Value = E3.get();

  auto ternaryExpr = std::make_unique<ASTTernaryExpr>(std::move(E1), std::move(E2), std::move(E3));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *ternaryExpr;
  REQUIRE(nodePrintStream.str() == "x ? 1 : 2");

  // Test getChildren
  auto children = ternaryExpr->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));
  REQUIRE(contains(children, E3Value));

  // Test accept
  RecordPostPrint visitor;
  ternaryExpr->accept(&visitor);

  std::string expected[] = {"x", "1", "2", "x ? 1 : 2"};
  for (int i = 0; i < 4; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTUnaryExpr: logical not", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");

  auto E1Value = E1.get();

  auto unaryExpr = std::make_unique<ASTUnaryExpr>("not", std::move(E1));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *unaryExpr;
  REQUIRE(nodePrintStream.str() == "not x");

  // Test getChildren
  auto children = unaryExpr->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, E1Value));

  // Test accept
  RecordPostPrint visitor;
  unaryExpr->accept(&visitor);

  std::string expected[] = {"x", "not x"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTUnaryExpr: arithmetic negation", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");

  auto E1Value = E1.get();

  auto unaryExpr = std::make_unique<ASTUnaryExpr>("-", std::move(E1));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *unaryExpr;
  REQUIRE(nodePrintStream.str() == "-x");

  // Test getChildren
  auto children = unaryExpr->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, E1Value));

  // Test accept
  RecordPostPrint visitor;
  unaryExpr->accept(&visitor);

  std::string expected[] = {"x", "-x"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBinaryExpr: logical and", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTVariableExpr>("y");

  auto E1Value = E1.get();
  auto E2Value = E2.get();

  auto logicalAndExpr = std::make_unique<ASTBinaryExpr>("and", std::move(E1), std::move(E2));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *logicalAndExpr;
  REQUIRE(nodePrintStream.str() == "(x and y)");

  // Test getChildren
  auto children = logicalAndExpr->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));

  // Test accept
  RecordPostPrint visitor;
  logicalAndExpr->accept(&visitor);

  std::string expected[] = {"x", "y", "(x and y)"};
  for (int i = 0; i < 3; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBinaryExpr: logical or", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");
  auto E2 = std::make_unique<ASTVariableExpr>("y");

  auto E1Value = E1.get();
  auto E2Value = E2.get();

  auto logicalOrExpr = std::make_unique<ASTBinaryExpr>("or", std::move(E1), std::move(E2));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *logicalOrExpr;
  REQUIRE(nodePrintStream.str() == "(x or y)");

  // Test getChildren
  auto children = logicalOrExpr->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, E1Value));
  REQUIRE(contains(children, E2Value));

  // Test accept
  RecordPostPrint visitor;
  logicalOrExpr->accept(&visitor);

  std::string expected[] = {"x", "y", "(x or y)"};
  for (int i = 0; i < 3; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

// test for ASTPostfixStmt: both postfix increment and postfix decrement

TEST_CASE("ASTNodeTest: ASTPostfixStmt: postfix increment", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");

  auto E1Value = E1.get();

  auto postfixStmt = std::make_unique<ASTPostfixStmt>(std::move(E1), "++");

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *postfixStmt;
  REQUIRE(nodePrintStream.str() == "x++;");

  // Test getChildren
  auto children = postfixStmt->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, E1Value));

  // Test accept
  RecordPostPrint visitor;
  postfixStmt->accept(&visitor);

  std::string expected[] = {"x", "x++;"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTPostfixStmt: postfix decrement", "[ASTNode]")
{
  auto E1 = std::make_unique<ASTVariableExpr>("x");

  auto E1Value = E1.get();

  auto postfixStmt = std::make_unique<ASTPostfixStmt>(std::move(E1), "--");

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *postfixStmt;
  REQUIRE(nodePrintStream.str() == "x--;");

  // Test getChildren
  auto children = postfixStmt->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, E1Value));

  // Test accept
  RecordPostPrint visitor;
  postfixStmt->accept(&visitor);

  std::string expected[] = {"x", "x--;"};
  for (int i = 0; i < 2; i++)
  {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}