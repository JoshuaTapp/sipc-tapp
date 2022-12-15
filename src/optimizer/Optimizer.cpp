#include "Optimizer.h"

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopUnrollAnalyzer.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/IPO/Inliner.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Scalar/SCCP.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Vectorize.h"

#include <iostream>
#include <vector>

#include "loguru.hpp"

using namespace llvm;

struct LLVMFunctionPass {
  Pass *pass;
  std::string name;
};

/*
  TODO: add more function optimization passes

  TODO: add module optimization passes

  TODO: research how passes interact with each other so that additional
  passes can be     added if necessary. Such as DCE Pass after InstCombine
  Pass makes sense.


  TODO: Abalation Study: remove each pass and see how it affects the
  performance of the program.

  TODO: BigBang.sip: write a sip program that uses all the features of the
  language. This program will be used to test the effectiveness of the
  optimization passes.

  * Passes to Add:
  * - Constant Propagation
  *
  * Important Notes:
  *   - Order of the passes matters
  *   - Some passes dont play well with each other
  *   - alot of passes assume mem2reg has been run (ex. Constant Propagation)
*/

void Optimizer::optimize(Module *theModule, int optLevel = 0) {
  LOG_S(1) << "Optimizing program " << theModule->getName().str();

  std::vector<LLVMFunctionPass> functionPasses = {
      // the default passes that were provided with TIP
      // * Basic Optimization Passes [0] -> [5] (6 passes)
      LLVMFunctionPass{createPromoteMemoryToRegisterPass(), "Mem2Reg"},
      LLVMFunctionPass{createReassociatePass(), "Reassociate Expressions"},
      LLVMFunctionPass{createInstructionCombiningPass(),
                       "Instruction Combining"},
      LLVMFunctionPass{createGVNPass(), "Global Value Numbering"},
      LLVMFunctionPass{createCFGSimplificationPass(), "CFG Simplification"},
      LLVMFunctionPass{createDeadCodeEliminationPass(),
                       "Dead Code Elimination"},

      // * Simple Loop Passes [6] -> [15] (10 passes)
      LLVMFunctionPass{createLoopRotatePass(), "Loop Rotate"},
      // simplify the loop's induction variables
      LLVMFunctionPass{createIndVarSimplifyPass(),
                       "Induction Variable Simplification"},
      // only useful if using "[i*M+j]" style indexing
      LLVMFunctionPass{createLoopFlattenPass(), "Loop Flattening"},
      // put the test at the end of the loop
      LLVMFunctionPass{createLoopSimplifyCFGPass(), "Loop Simplify CFG"},
      LLVMFunctionPass{createLoopDeletionPass(), "Loop Deletion"},
      // reduce conditional branches before unify loop exits
      LLVMFunctionPass{createLoopIdiomPass(), "Loop Idiom Recognition"},
      LLVMFunctionPass{createUnifyLoopExitsPass(), "Unify Loop Exits"},
      // ensures only have a single back edge. Then do CFG Simplification
      LLVMFunctionPass{createLoopSimplifyPass(), "Loop Simplification"},
      // does both hoisting and sinking.
      LLVMFunctionPass{createLICMPass(), "Loop Invariant Code Motion"},
      // from LoopUnrollPass.cpp: must run -indvars first to ensure
      // effectiveness
      LLVMFunctionPass{createLoopUnrollPass(), "Loop Unrolling"},

      // * Advanced Loop Passes [16] -> [22] (7 passes)
      LLVMFunctionPass{createInstructionCombiningPass(),
                       "Instruction Combining"},
      // help with order for cache access (which is important for SIMD)
      LLVMFunctionPass{createLoopInterchangePass(), "Loop Interchange"},
      LLVMFunctionPass{createLoadStoreVectorizerPass(),
                       "Load/Store Vectorization"},
      // run first, to group scalar instructions into single instruction
      LLVMFunctionPass{createSLPVectorizerPass(), "SLP Vectorization"},
      // vectorize the loop now!
      LLVMFunctionPass{createLoopVectorizePass(), "Loop Vectorization"},
      // clean up after vectorization
      LLVMFunctionPass{createTailCallEliminationPass(),
                       "Tail Call Elimination"},
      LLVMFunctionPass{createDeadCodeEliminationPass(),
                       "Dead Code Elimination"},

      // * Branch Prediction Passes [23] -> [26] (4)
      LLVMFunctionPass{createJumpThreadingPass(), "Jump Threading"},
      // demote to try and do better CFG Simplification
      LLVMFunctionPass{createDemoteRegisterToMemoryPass(),
                       "Demote Register to Memory"},
      LLVMFunctionPass{createCFGSimplificationPass(), "CFG Simplification"},
      LLVMFunctionPass{createPromoteMemoryToRegisterPass(), "Mem2Reg"},
  };

  auto TheFPM = std::make_unique<legacy::FunctionPassManager>(theModule);
  auto TheMPM = std::make_unique<legacy::PassManager>();

  // Add some optimizations
  for (int i = 0; i < functionPasses.size(); i++) {
    /*
     * 27 total passes in functionPasses vector
     *   All OptLevels
     *     mem2reg: [0], [26]
     *     reassociate: [1]
     *     instcombine: [2], [16]
     *     gvn: [3]
     *     cfgsimplify: [4], [25]
     *     dce: [5], [18], [22]
     *   OptLevels: 1, 2, 3 (and the corresponding disabling optLevels)
     *     indvars: [6]
     *     loopsimplifycfg: [7]
     *     loopflatten: [8]
     *     looprotate: [9]
     *     loopdelete: [10]
     *     loopidiom: [11]
     *     loopunify: [12]
     *     loopsimplify: [13]
     *     licm: [14]
     *     loopunroll: [15]
     *  OptLevels: 2, 3 (and the corresponding disabling optLevels)
     *     loopinterchange: [17]
     *     SLPVectorize: [19]
     *     loopvectorize: [20]
     *     tailcallelim: [21]
     *  OptLevels: 3 (and the corresponding disabling optLevels)
     *     jumpthreading: [23]
     *     demoteregister: [24]
     *
     * Begin Pass Disabling
     * No disabled Passes:
     *   optLevel 0: -O0, 1: -O1, 2: -O2, 3: -O3
     * Disabled Passes:
     *   To disable pass,
     *     1. take desired base -Ox optLevel (0, 1, 2, 3)
     *     2. add the following number to the base optLevel
     *          4: -O0
     *          9: -O1
     *         24: -O2
     *         45: -O3
     *     2. add the index of the pass to disable from above list
     *  Example: to disable loopunroll pass at -O2
     *     2 + 24 + 15 = -O41
     */

    // * Disable Passes
    // * -O0
    if ((optLevel == 0 || (optLevel >= 4 && optLevel <= 9)) && i > 5)
      break;
    // * -O1
    if ((optLevel == 1 || (optLevel >= 10 && optLevel <= 25)) && i > 15)
      break;
    // * -O2
    if ((optLevel == 2 || (optLevel >= 26 && optLevel <= 48)) && i > 23)
      break;

    // * disable Mem2Reg pass
    if (optLevel == 4 || optLevel == 10 || optLevel == 26 || optLevel == 48 ||
        optLevel == 74) {
      if (i == 0 || i == 26) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable Reassociate pass
    if (optLevel == 5 || optLevel == 11 || optLevel == 27 || optLevel == 49) {
      if (i == 1) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable InstCombine pass [2] and [16]
    if (optLevel == 6 || optLevel == 12 || optLevel == 28 || optLevel == 50 ||
        optLevel == 42 || optLevel == 64) {
      if (i == 2 || i == 16) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable GVN pass
    if (optLevel == 7 || optLevel == 13 || optLevel == 29 || optLevel == 51) {
      if (i == 3) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable CFGSimplify pass [4] and [23]
    if (optLevel == 8 || optLevel == 14 || optLevel == 30 || optLevel == 52 ||
        optLevel == 43 || optLevel == 73) {
      if (i == 4 || i == 23) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable DCE pass [5] and [18] and [22]
    if (/* 5 */ optLevel == 9 || optLevel == 15 || optLevel == 31 ||
        optLevel == 53 ||
        /* 18 */ optLevel == 44 || optLevel == 66 ||
        /* 22 */ optLevel == 48 || optLevel == 70) {
      if (i == 5 || i == 18 || i == 22) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable IndVars pass
    if (optLevel == 16 || optLevel == 32 || optLevel == 54) {
      if (i == 6) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopSimplifyCFG pass
    if (optLevel == 17 || optLevel == 33 || optLevel == 55) {
      if (i == 7) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopFlatten pass
    if (optLevel == 18 || optLevel == 34 || optLevel == 56) {
      if (i == 8) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopRotate pass
    if (optLevel == 19 || optLevel == 35 || optLevel == 57) {
      if (i == 9) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopDelete pass
    if (optLevel == 20 || optLevel == 36 || optLevel == 58) {
      if (i == 10) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopIdiom pass
    if (optLevel == 21 || optLevel == 37 || optLevel == 59) {
      if (i == 11) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable Loopunify pass
    if (optLevel == 22 || optLevel == 38 || optLevel == 60) {
      if (i == 12) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopSimplify pass
    if (optLevel == 23 || optLevel == 39 || optLevel == 61) {
      if (i == 13) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LICM pass
    if (optLevel == 24 || optLevel == 40 || optLevel == 62) {
      if (i == 14) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopUnroll pass
    if (optLevel == 25 || optLevel == 41 || optLevel == 63) {
      if (i == 15) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable LoopInterchange pass
    if (optLevel == 43 || optLevel == 65) {
      if (i == 17) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable SLPVectorizer pass
    if (optLevel == 45 || optLevel == 67) {
      if (i == 19) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable Vectorize pass
    if (optLevel == 46 || optLevel == 68) {
      if (i == 20) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable TailCallElimination pass
    if (optLevel == 47 || optLevel == 69) {
      if (i == 21) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable JumpThreading pass
    if (optLevel == 71) {
      if (i == 23) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    // * disable demoteRegisterToMemory pass
    if (optLevel == 72) {
      if (i == 24) {
        LOG_S(1) << "Disabling " << functionPasses[i].name << " Pass";
        continue;
      }
    }

    LOG_S(1) << "Adding optimization pass " << functionPasses[i].name;
    TheFPM->add(functionPasses[i].pass);
  }

  TheFPM->doInitialization();

  for (auto &fun : theModule->getFunctionList()) {
    LOG_S(1) << "Optimizing function " << fun.getName().str();

    for (int i = 0; i < 20; i++) {
      TheFPM->run(fun);
    }
  }

  TheFPM->doFinalization();

  // * Interdependence Passes
  if (theModule->getFunctionList().size() > 1) {
    TheMPM->add(createConstantMergePass());
    TheMPM->add(createIPSCCPPass());
    TheMPM->add(createMergeFunctionsPass());
    TheMPM->add(createDeadArgEliminationPass());
    TheMPM->add(createFunctionInliningPass(50));
    TheMPM->add(createGlobalOptimizerPass());
    TheMPM->add(createGlobalDCEPass());
    for (int i = 0; i < 25; i++) {
      TheMPM->run(*theModule);
    }
  }
  // * LETS TRY AGAIN
  TheFPM->doInitialization();

  for (auto &fun : theModule->getFunctionList()) {
    LOG_S(1) << "Optimizing function " << fun.getName().str();

    for (int i = 0; i < 20; i++) {
      TheFPM->run(fun);
    }
  }

  TheFPM->doFinalization();
};
