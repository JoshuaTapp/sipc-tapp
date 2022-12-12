#include "Optimizer.h"

#include "llvm/Analysis/LazyValueInfo.h"
#include "llvm/Analysis/LoopAccessAnalysis.h"
#include "llvm/Analysis/MemDerefPrinter.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include "llvm/CodeGen/MachineScheduler.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/IPO/GlobalDCE.h"
#include "llvm/Transforms/IPO/GlobalOpt.h"
#include "llvm/Transforms/IPO/Inliner.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Vectorize.h"
#include "llvm/Transforms/Vectorize/LoadStoreVectorizer.h"
#include "llvm/Transforms/Vectorize/SLPVectorizer.h"
#include <iostream>

#include "loguru.hpp"

using namespace llvm;
/*
  TODO: add more function optimization passes

  TODO: add module optimization passes

  TODO: research how passes interact with each other so that additional passes
  can be     added if necessary. Such as DCE Pass after InstCombine Pass makes
  sense.

  TODO: Write programs to test the effectiveness of the optimization passes.

  TODO: Define my performance metrics and write script to test the effectiveness
  of the optimization passes according to those metrics.

  TODO: Abalation Study: remove each pass and see how it affects the performance
  of the program.

  TODO: modify tipc.cpp (command line options) to handle modification of the
  optimization passes.

  TODO: BigBang.sip: write a sip program that uses all the features of the
  language. This program will be used to test the effectiveness of the
  optimization passes.

  * Passes to Add:
  * - Constant Propagation
  *

*/

void Optimizer::optimize(Module *theModule, int optLevel) {
  LOG_S(1) << "Optimizing program " << theModule->getName().str();

  auto TheFPM = std::make_unique<legacy::FunctionPassManager>(theModule);
  auto TheMPM = std::make_unique<legacy::PassManager>();

  switch (optLevel) {
  case 0:
    LOG_S(1) << "Optimization Level: -O0";

    TheFPM->add(createPromoteMemoryToRegisterPass());
    TheFPM->add(createInstructionCombiningPass());
    TheFPM->add(createReassociatePass());
    TheFPM->add(createGVNPass());
    TheFPM->add(createCFGSimplificationPass());
    break;
  case 1:
    LOG_S(1) << "Optimization Level: -O1";

    // Loop Simplify
    TheFPM->add(createLoopSimplifyPass());
    // Loop Strength Reduce
    TheFPM->add(createLoopStrengthReducePass());
    // Loop Unroll
    TheFPM->add(createLoopUnrollPass());
    // Loop Vectorize
    TheFPM->add(createLoopVectorizePass());
    break;

  case 2:
    LOG_S(1) << "Optimization Level: -O2";

    break;

  default:
    LOG_S(1) << "Optimization Level: Unknown";
    break;
  }

  // initialize and run simplification pass on each function
  TheFPM->doInitialization();
  for (auto &fun : theModule->getFunctionList()) {
    LOG_S(1) << "Optimizing function " << fun.getName().str();

    TheFPM->run(fun);
  }

  // Run the interprocedural optimization passes on the module.
  TheMPM->run(*theModule);
}
