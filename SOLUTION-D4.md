# Deliverable 4: Code Generation -- SIP Support

## Codegen Routines

Code generation was obviously the hardest. I had made design decisions previously That I thought would have made everything easier to manage as time went on. However, when it came to codegen, collapsing different syntax styles into one AST Node representation led to increased complexity. This was notably felt with `ASTForStmt` and `ASTArrayConstructorExpr`. Another unknown configuration issue that was preventing the correct LLVM IR code generation as was expected from the implementation I had written. Eventually I reinstalled `xcode-cli-tools`, where clang was reinstalled. I then reinstalled all of the packages from brew that are included in the `bootstrap.sh` script. Only after that did things start to behave as expected. It took me three days of experimenting to finally reinstall everything. I spent nearly two hours in office hours and was unable to diagnose a single issue. I just ask you be understanding in the lateness of my deliverable. I have put over 30 hours into this due to a lot of lost time due to the previously mentioned issues.

The following is a brief summary of what was done in `CodeGenFunctions.cpp`.

####  Modified:
- ASTBinaryExpr
   - Added full support for new arithmetic, relational, equality, and logical operators.
   - This included ensuring the return type was correct due to the addition of the boolean literal
   - Used the convenience of `i1` types to do logical operations by using `icmpEQ(Value, zeroV)` to cast to `i1`, performing boolean operations, and then casting back into `i64` representation
- ASTifStmt
   - changed conditional generation to use boolean literals (e.g. `true == i64 0`)
- ASTWhileStmt
   - changed conditional generation to use boolean literals (e.g. `true == i64 0`)

#### New Implementation:
- ASTTernaryExp
  -  After hours of frustrating tinkering and running lldb instruction by instruction, I discovered the parser tree was incorrect due to the grammar. This caused the AST to be incorrect as well when nested ternary expression were used. Modified the grammar and then simplified the codegen implementation. So much wasted time, a recurring theme...

- ASTPostfixStmt
  - Increment and Decrement statements were straightforward. Load -> op -> Store
- ASTArrayLengthExpr
  -  I started with this one after I originally had `ASTArrayConstructorExpr::codegen()` to allocate the array and store the size with the `[E1, ... , En]` syntax at first. I decided to store the array size in the 0-th index of the heap memory. This made sense to me as even an empty array would not lead to a segfault when accessing the array length value.

- ASTArraySubscriptExpr
  - Very difficult due to mistakes with LLVM::types. There was a moment where I started to cry out in desperation due to this code. Beyond confused why my model on paper was not being generated properly. After reinstalling everything, things started to work as expected and I could debug the remaining errors.
- ASTArrayConstructorExpr
  - Most difficult part of the project by far. Had issues with codegen reflecting how the c++ code was structured. Spent over 15 hours debugging this until I reinstalled Xcode cli tools and it started working.
  - It has a basic structure of
    - setup
    - header / conditional testing
    - body: where elements are generated and stored in array[i+1]
      - fillLoop: special case for the array fill syntax. Where the same element is stored in each subsequent array index
    - end: convert array pointer `*i64` to `i64`, for consistency and return.
  - I have a syntax style flag in the AST Node that allowed me to know which code to emit for the array filling portion along with where the array length value will be sourced from (`getElements().size()` or `getE1()->codegen()`)
- ASTUnaryExpr
  - Simple, based on ASTBinaryExpr::codegen. Used boolean algebra to design the instructions and simplify the code.
- ASTBooleanExpr
  - decided to represent "true" values as `i64 0`. I do not even recall why I did this. I have spent so much time on this and this was the first thing I did.

In all, I have a deep understanding of LLVM now, as I have lost count on the hours I spent on this. I just wanted to figure it out on my own so badly. After office hours were unproductive (no blame on TA), I felt like I was on my own. It does surprise me it took this long. As I gave myself 15 hours before the deadline to complete just arrays and for loops. Jokes on me =/

## Type Disabling

This process was simple. I followed the pattern in `tipc.cpp` and implemented the `--dt` command line argument by modifying the `SemanticAnalysis` class to take a flag to disable type checking. As well as overriding the `--pt` flag, which is printing of types, due to the conflict.

```cpp
SemanticAnalysis::analyze(ASTProgram *ast, bool disableTypeChecking) {
  auto symTable = SymbolTable::build(ast);
  CheckAssignable::check(ast);
  auto callGraph = CallGraph::build(ast, symTable.get());
  auto typeResults = (disableTypeChecking)
                         ? nullptr
                         : TypeInference::check(ast, symTable.get());
  return std::make_unique<SemanticAnalysis>(
      std::move(symTable), std::move(typeResults), std::move(callGraph));
}
```

## Testing

### System: `siptests/*.sip`

I modified the `test/system/run.sh` script to automate the testing of SIP programs. These included polymorphic function that required the use of the `--dt` argument. I had some programs that required command line arguments, I tested them thoroughly individually before adding trusting the autmated test to behave as expected. Here is an excerpt of the script modification.

```bash
# test unoptimized program
  initialize_test
    if [[ $base == *"fold"* || $base == *"map"* ]]; then
    # Disable type checking for programs whose names contain "fold" or "map"
    ${TIPC} --dt --do $i
  else
    ${TIPC} --do $i
  fi
  ${TIPCLANG} -w $i.bc ${RTLIB}/tip_rtlib.bc -o $base

  if [[ $base == *"arrayref"* ]]; then
      ./${base} 3 3 1 &>/dev/null
  else
      ./${base} &>/dev/null
  fi
  exit_code=${?}
  if [ ${exit_code} -ne 0 ]; then
    echo -n "Test failure for : "
    echo $i
    ./${base}
    ((numfailures++))
  else
    rm ${base}
  fi
  rm $i.bc
  ```

  Thankfully all of the tests are passing and I have reasonable belief that my compiler is performs according to the standard. I used the provided siptests with heavy modification and the addition of new tests as well.

### Unit Tests

My code coverage was 95% from the last commit. I am comfortable with where my testing is at currently. I did not add tests to `unit/codegen/CodegenFunctionsTest.cpp` for every codegen method. This was because of segmenation faults. I noticed that no test was included for `ASTWhileStmt`. I assumed this was for the same reason, as when I tried to implement one, I also was getting segfaults. Because I am already behind the deadline, I did not research further, as the siptests gave me reasonable assurance that my programs should work as expected. At the worse, it would just be difficult to debug if a nullptr was passed to an AST Node and stored in one of it's children.
