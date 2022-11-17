#include "SemanticAnalysis.h"
#include "CheckAssignable.h"

std::unique_ptr<SemanticAnalysis>
SemanticAnalysis::analyze(ASTProgram *ast, bool typeInference) {
  auto symTable = SymbolTable::build(ast);
  CheckAssignable::check(ast);
  auto callGraph = CallGraph::build(ast, symTable.get());
  auto typeResults =
      typeInference ? TypeInference::check(ast, symTable.get()) : nullptr;
  return std::make_unique<SemanticAnalysis>(
      std::move(symTable), std::move(typeResults), std::move(callGraph));
}

SymbolTable *SemanticAnalysis::getSymbolTable() { return symTable.get(); };

TypeInference *SemanticAnalysis::getTypeResults() { return typeResults.get(); };

CallGraph *SemanticAnalysis::getCallGraph() { return callGraph.get(); };
