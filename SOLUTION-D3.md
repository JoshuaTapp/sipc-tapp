# Deliverable 3: Semantic Analysis Extension

## Weeding Pass

The only new feature from SIP that required an update to TIP's weeding pass was array referencing. My AST node for this feature, `ASTArraySubscriptExpr` holds two node pointers (array, index). To update my `CheckAssignable.cpp` was to add a new method for array referencing. Because all arrays are simply pointers to a memory block (in some way), they will be assigned to some `ASTVariableExpr`. Because of this, I could reuse the `isAssignable` anonymous function without update. I followed the same model as the `CheckAssignable::endVisit(ASTRefExpr *element)` method; as they are effectively doing the same thing. The only difference being the type of `ASTExpr` field. Funny enough, the only issue I had was with testing. It took me a few minutes to remember that even an uninitialized variable is still valid in the weeding pass. Once I realized this oversight, I updated the test for failure from,
```cpp
// Original
TEST_CASE("Check Assignable: address of array", "[Symbol]") {
  std::stringstream stream;
  stream << R"(arraysublhs() { return x[0]; })";
  auto ast = ASTHelper::build_ast(stream);
  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
                         ContainsWhat("x not an l-value"));
}

// Fix
TEST_CASE("Check Assignable: address of array", "[Symbol]") {
  std::stringstream stream;
  stream << R"(arraysublhs() { return 1[0]; })";
  auto ast = ASTHelper::build_ast(stream);
  REQUIRE_THROWS_MATCHES(CheckAssignable::check(ast.get()), SemanticError,
                         ContainsWhat("1 not an l-value"));
}
```
With that fix, I was somewhat ensured that my solution was correct.


## Types

### Boolean Type

As the boolean type is a primitive type, I used `TipInt` as a template. Very straightforward and I implemented it correctly the first try.

### Array Type

Arrays were more complicated. As with the weeding pass, I followed `ASTRef` as a design reference because of their similarities. One could say that arrays are just a specialized subtype of pointers and so this made sense in my mind.

I decided to have `TipArray`'s constructor to only have a single argument: `TipArray(std::shared_ptr<TipType> arrayElements);`. This was done becaused I planned to enforce type homogeneity in the type constraint rules. To me, this was the better design as it simplified the type by removing superfluous data.

## Type Constraints

This was the hardest part of extending the type system in TIP. While some constraints were straightforward, such as booleans and unary/binary ops, the others were more complicated.

### Array Constructors

Because I designed my AST nodes to handle both syntaxes, I had only a single `TypeConstraintVisitor` method for arrays. My original implementation was incorrect due to me having trouble grasping only handling local concerns. I knew my solution was incorrect, but I was struggling to create the proper type rules. I met with Nick and talked through my thought process and eventually came up with the correct solution.

### Array Ops

While array referencing was straightforward, array length was difficult because I again failed to understand the focus on local concerns. The problem was enforcing that the array used with the length operator be a type of `array of alpha`. I originally started by passing a `nullptr` to the `TipAlpha` constructor. During testing, this caused a seg fault. I started looking over piazza and found a comment to pass the AST array to the `TipAlpha` constructor. In hindsight, this make perfect sense, as the solver will now use a array of alpha to enforce the type.

### Other Type Rules

The other were straight forward when I had a handle of how to use alpha properly.

## Advantages From Previous Design Decisions

My decision to shrink node size in the AST is going to pay off in the forcible future. Because I combined all new SIP features into existing or new AST nodes, My type constraints were more clean. I believe this will also help greatly in the codegen portion.

## Testing

I hated doing tests for this but I have 100% code coverage and everything behaves as expected. I found a lot of issues as I progressed. The most notable being discovering that the print method of `TipType` uses the pointer passed as the `ASTNode` to `TipAlpha`. That required me breaking out lldb and running the executable test file. I mentioned the testing issues with `CheckAssignableTest`. I did find I forgot to write the pretty printer tests from D2 and went back and wrote those. I found that my `[E1 of E2]` pretty print method had the wrong output. I hate writing tests, but it is something I will always due after this class.