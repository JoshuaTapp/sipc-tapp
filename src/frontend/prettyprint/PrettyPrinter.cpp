#include "PrettyPrinter.h"

#include <iostream>
#include <sstream>

void PrettyPrinter::print(ASTProgram *p, std::ostream &os, char c, int n) {
  PrettyPrinter visitor(os, c, n);
  p->accept(&visitor);
}

/**
 * join last sz items from the visitedResults with delimiter delim. Then, remove
 * these items from the stack
 *
 * the delimiter before the last skip items are not appended (e.g. to not add
 * trailing commas)
 *
 * returns the joined string
 */
std::string joinWithDelim(std::vector<std::string> &visitResults,
                          std::string delim, int sz, int skip) {
  std::string out;
  int i;
  for (i = visitResults.size() - sz; i < visitResults.size() - skip; i++) {
    out += visitResults[i];
    out += delim;
  }
  // skip the delimiter for the last several tokens
  for (; i < visitResults.size(); i++)
    out += visitResults[i];
  visitResults.erase(visitResults.begin() + visitResults.size() - sz,
                     visitResults.end());
  return out;
}

void PrettyPrinter::endVisit(ASTProgram *element) {
  os << joinWithDelim(visitResults, "\n", element->getFunctions().size(), 1);
  os.flush();
}

/*
 * General approach taken by visit methods.
 * - visit() is used to increase indentation (decrease should happen in
 * endVisit).
 * - endVisit() should expect a string for all of its AST nodes in reverse order
 * in visitResults. Communicate the single string for the visited node by
 * pushing to the back of visitedResults.
 */

/*
 * Before visiting function, record string for signature and setup indentation
 * for body. This visit method pushes a string result, that the endVisit method
 * should extend.
 */
bool PrettyPrinter::visit(ASTFunction *element) {
  indentLevel++;
  return true;
}

/*
 * After visiting function, collect the string representations for the:
 *   statements, declarations, formals, and then function name
 * they are on the visit stack in that order.
 */
void PrettyPrinter::endVisit(ASTFunction *element) {
  auto bodyString =
      joinWithDelim(visitResults, "\n", element->getStmts().size(), 0);
  auto declString =
      joinWithDelim(visitResults, "\n", element->getDeclarations().size(), 0);
  auto formalsString =
      joinWithDelim(visitResults, ", ", element->getFormals().size(), 1);

  // function name is last element on stack
  // we modify it in place
  visitResults.back() +=
      "(" + formalsString + ") \n{\n" + declString + bodyString + "}\n";
  indentLevel--;
}

void PrettyPrinter::endVisit(ASTNumberExpr *element) {
  visitResults.push_back(std::to_string(element->getValue()));
}

void PrettyPrinter::endVisit(ASTVariableExpr *element) {
  visitResults.push_back(element->getName());
}

void PrettyPrinter::endVisit(ASTBinaryExpr *element) {
  std::string rightString = visitResults.back();
  visitResults.pop_back();
  std::string leftString = visitResults.back();
  visitResults.pop_back();

  visitResults.push_back("(" + leftString + " " + element->getOp() + " " +
                         rightString + ")");
}

void PrettyPrinter::endVisit(ASTInputExpr *element) {
  visitResults.push_back("input");
}

void PrettyPrinter::endVisit(ASTFunAppExpr *element) {
  auto actualsString =
      joinWithDelim(visitResults, ", ", element->getActuals().size(), 1);
  visitResults.back() += "(" + actualsString + ")";
}

void PrettyPrinter::endVisit(ASTAllocExpr *element) {
  std::string init = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back("alloc " + init);
}

void PrettyPrinter::endVisit(ASTRefExpr *element) {
  std::string var = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back("&" + var);
}

void PrettyPrinter::endVisit(ASTDeRefExpr *element) {
  std::string base = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back("*" + base);
}

void PrettyPrinter::endVisit(ASTNullExpr *element) {
  visitResults.push_back("null");
}

void PrettyPrinter::endVisit(ASTFieldExpr *element) {
  std::string init = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(element->getField() + ":" + init);
}

void PrettyPrinter::endVisit(ASTRecordExpr *element) {
  visitResults.push_back(
      "{" + joinWithDelim(visitResults, ", ", element->getFields().size(), 1) +
      "}");
}

void PrettyPrinter::endVisit(ASTAccessExpr *element) {
  std::string accessString = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(accessString + '.' + element->getField());
}

void PrettyPrinter::endVisit(ASTDeclNode *element) {
  visitResults.push_back(element->getName());
}

void PrettyPrinter::endVisit(ASTDeclStmt *element) {
  visitResults.push_back(
      indent() + "var " +
      joinWithDelim(visitResults, ", ", element->getVars().size(), 1) + ";");
}

void PrettyPrinter::endVisit(ASTAssignStmt *element) {
  std::string rhsString = visitResults.back();
  visitResults.pop_back();
  std::string lhsString = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(indent() + lhsString + " = " + rhsString + ";");
}

bool PrettyPrinter::visit(ASTBlockStmt *element) {
  indentLevel++;
  return true;
}

void PrettyPrinter::endVisit(ASTBlockStmt *element) {
  indentLevel--;
  visitResults.push_back(
      indent() + "{\n" +
      joinWithDelim(visitResults, "\n", element->getStmts().size(), 0) +
      indent() + "}");
}

/*
 * For a while the body should be indented, but not the condition.
 * Since conditions are expressions and their visit methods never indent
 * incrementing here works.
 */
bool PrettyPrinter::visit(ASTWhileStmt *element) {
  indentLevel++;
  return true;
}

void PrettyPrinter::endVisit(ASTWhileStmt *element) {
  std::string bodyString = visitResults.back();
  visitResults.pop_back();
  std::string condString = visitResults.back();
  visitResults.pop_back();

  indentLevel--;

  std::string whileString =
      indent() + "while (" + condString + ") \n" + bodyString;
  visitResults.push_back(whileString);
}

bool PrettyPrinter::visit(ASTIfStmt *element) {
  indentLevel++;
  return true;
}

void PrettyPrinter::endVisit(ASTIfStmt *element) {
  std::string elseString;
  if (element->getElse() != nullptr) {
    elseString = visitResults.back();
    visitResults.pop_back();
  }

  std::string thenString = visitResults.back();
  visitResults.pop_back();

  std::string condString = visitResults.back();
  visitResults.pop_back();

  indentLevel--;

  std::string ifString = indent() + "if (" + condString + ") \n" + thenString;

  if (element->getElse() != nullptr) {
    ifString += "\n" + indent() + "else\n" + elseString;
  }

  visitResults.push_back(ifString);
}

void PrettyPrinter::endVisit(ASTOutputStmt *element) {
  std::string argString = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(indent() + "output " + argString + ";");
}

void PrettyPrinter::endVisit(ASTErrorStmt *element) {
  std::string argString = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(indent() + "error " + argString + ";");
}

void PrettyPrinter::endVisit(ASTReturnStmt *element) {
  std::string argString = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(indent() + "return " + argString + ";");
}

std::string PrettyPrinter::indent() const {
  return std::string(indentLevel * indentSize, indentChar);
}

/* New pretty printer methods for Deliverable 2 */

void PrettyPrinter::endVisit(ASTArrayConstructorExpr *element) {
  int size = element->getElements().size();
  std::string E1, E2 = "";

  std::string arrayString = "";
  if (element->isImplicit()) {
    E2 = visitResults.back();
    visitResults.pop_back();
    E1 = visitResults.back();
    visitResults.pop_back();
    arrayString = "[" + E1 + " of " + E2 + "]";
  } else {
    arrayString = "[" + joinWithDelim(visitResults, ", ", size, 1) + "]";
  }
  visitResults.push_back(arrayString);
}

void PrettyPrinter::endVisit(ASTArrayLengthExpr *element) {
  std::string arrayIdentifier = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back("#" + arrayIdentifier);
}

void PrettyPrinter::endVisit(ASTArraySubscriptExpr *element) {
  std::string index = visitResults.back();
  visitResults.pop_back();
  std::string arrayIdentifier = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(arrayIdentifier + "[" + index + "]");
}

void PrettyPrinter::endVisit(ASTBooleanExpr *element) {
  visitResults.push_back(element->getValue() ? "true" : "false");
}

void PrettyPrinter::endVisit(ASTPostfixStmt *element) {
  std::string identifier = visitResults.back();
  visitResults.pop_back();
  visitResults.push_back(indent() + identifier + element->getOp() + ";");
}

void PrettyPrinter::endVisit(ASTTernaryExpr *element) {
  std::string E3 = visitResults.back();
  visitResults.pop_back();
  std::string E2 = visitResults.back();
  visitResults.pop_back();
  std::string E1 = visitResults.back();
  visitResults.pop_back();

  visitResults.push_back(E1 + " ? " + E2 + " : " + E3);
}

void PrettyPrinter::endVisit(ASTUnaryExpr *element) {
  std::string E = visitResults.back();
  visitResults.pop_back();
  if (element->getOp() == "-") {
    visitResults.push_back(element->getOp() + E);
  } else {
    visitResults.push_back(element->getOp() + " " + E);
  }
}

bool PrettyPrinter::visit(ASTForStmt *element) {
  indentLevel++;
  return true;
}

void PrettyPrinter::endVisit(ASTForStmt *element) {
  std::string bodyString = visitResults.back();
  visitResults.pop_back();

  std::string E4 = "";
  std::string E3 = "";
  std::string E2 = "";
  std::string E1 = "";

  if (element->getE4() != nullptr) {
    E4 = visitResults.back();
    visitResults.pop_back();
  }
  if (element->getE3() != nullptr) {
    E3 = visitResults.back();
    visitResults.pop_back();
  }

  E2 = visitResults.back();
  visitResults.pop_back();
  E1 = visitResults.back();
  visitResults.pop_back();

  indentLevel--;

  std::string forString = indent() + "for (" + E1 + " : " + E2 +
                          (E3 != "" ? " .. " + E3 : "") +
                          (E4 != "" ? " by " + E4 : "") + ")\n" + bodyString;

  visitResults.push_back(forString);
}
