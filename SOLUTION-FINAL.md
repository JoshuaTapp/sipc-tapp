# Deliverable 5: Compiler Optimizations

## Testing

I want to first introduce my testing method and the programs that perform the testing.

### TIPProgMetrics

This program is my main method of measuring the effectiveness of optimizations. The program takes in optimized and unoptimized SIP programs and runs them. It runs each program `k` times (default:40) and captures the following averaged metrics: approximate number of clock cycles to execute, machine code file size, and number of memory access calls. It then outputs a ratio between [-1, 1] for each metric which is defined by the following,

$$ \frac{-(p1 - p2)}{\max (p1, p2)} $$

It will also produce a weighted score based on what I found to be important that tries to signify the balance between the three metrics. With 50% of the weight towards time, 30% towards number of memory accesses, and 20% for approximate instruction count. The reasoning of this was to try to project the three metrics into a balanced approach that would lean heavier towards execution time.

### `bin/runtests.sh -oX`

I added the feature to the test script to automate the running of `TIPProgMetrics` with a level of optimization. This test will run all of the programs in `test/system/optests` and output the ratio scores to the terminal. This way you can see how a certain optimization set will effect many different types of programs. This is useful for finding where certain unexpected changes would happen automatically. For instance, when running with `-o0` (default TIP optimizations) would produce the following with programs that focused on loops.

| Name       | Weighted Score | File Score | Time Score | Memory Score |
|------------|----------------|------------|------------|--------------|
| loopunroll |  -0.059962 | 0 | -0.119924 | 0 |
| superloopsum |0.051346 | 0 | 0.102691 | 0 |


but when ran with the `-o1` flag, we get the following outputs,

| Name       | Weighted Score | File Score | Time Score | Memory Score |
|------------|----------------|------------|------------|--------------|
| loopunroll | -0.024212 | 0 | -0.048423 | 0 |
| superloopsum | 0.130751 | 0 | 0.261501 | 0 |

I use this test for all determination of what optimizations are effective and with what types of programs they are effective for. If a optimization level (which are a 'themed' set of optimization passes or an optimization style) shows a large jump in performance, then we can associate it with that specific optimization strategy. For instance the change from `-O=0` to `-O=1` for `superloopsum` is substantial because with `TIPProgMetrics` the arguments to it are `optimized superloopsum` and `unoptimized superloopsum`. Therefore we can compare different optimization levels because the ratios are always constructed using the `--do` flag during compilation.

### CompIR.sh

I create this cute little script that has the dependency of colordiff `brew install colordiff`. This little script takes a TIP/SIP program and compiles the human readable llvm bytecode. It then runs colordiff on the the outputs and shows you the differences between the two with some nice highlighting. It also stores the results in a text file called `{program name}_O{opLevel}_diff.txt` and you can run `cat --color` to see the formatted results.

You can also compare a program with two different optimization levels by just using adding a second optimization level to the command line.

```bash
# opLevel = 0 - 10

# Optimized vs. Unoptimized
./CompIR.sh <opLevel> </path/to/program>

# Optimized A vs. Optimized B
./CompIRO.sh <opLevel> <opLevel> </path/to/program>
```

Here is an example when running `./CompIR.sh 1 optests/superloopsum.tip` on my machine.

![colordiff output](./Screenshot%202022-12-12%20at%2011.18.19%20PM.png)

Here is an example when running `./CompIR.sh 1 0 optests/superloopsum.tip` on my machine.

![colordiff output](./Screenshot%202022-12-12%20at%2011.45.39%20PM.png)


### abalation.sh

This script runs the abalation tests, it actually produces the `ablation.txt` file with the results of every permutation of the available optimizations where number of disabled passes is 1.


## Understanding Function Passes


After a lot of research, here is my understanding of what passes are effective and justifications. I was liberal in my application of passes and could most likely accomplish similar performance with less passes. I have already reduced the number by ~7 passes as is from my original solution.

NOTE: **[Score of -Ox against -Ox w/o that specific pass]**

- Mem2Reg: [-O0: +0.1602] This pass attempts to modify memory access by loading it into a register and replaces memory access down stream. Test showed very important with cycle count.

- Reassociate Expressions: [-O0:  +0.0882] This pass does reordering with constants and variables to improve downstream optimizations, such as GVN.

- Global Value Numbering: [-O0: +0.0375] This pass removes **MUST** be redundant instructions. Does simple DLE as well, which works well with DSE & DCE.

- Instruction Combining: [-O1: +0.133] Minor benefit, I believe this is because it allows future optimizations to happen. As it performs the same with `-O0` but with `-O1` (which mods the CFG) has a significant advantage.

- CFG Simplification: [-O3: +0.2851] Due to many other programs modifying the CFG, I found this one small but signification change. The program `CFGSimple.sip` test has branches in a while loop in order to test the simplicity of the call graph. The fact that even with all loop passes being enabled still showed a 3.5% improvement is significant to me.

- Dead Store/Code Elimination: [-O1: +0.1331] I originally had Dead Code Store as well, but I realized that CFG passes were remove loads and with that, it looked like (based on the bytecode) that DCE was more than able to remove the stores. I verified it with the program `deadstore.sip` and ran diff on the `.ll` output. ![](./Screenshot%202022-12-14%20at%207.53.36%20AM.png)

- SCCP: I did a lot of testing with this one and could find any benefit for using the pass with my `SCCP.sip` test, which is one that should have benefit. Therefore it was removed for function passes. I did add IPSCCP to help find any propagation across functions (which seems more appropriate).

- TailCall: [-O3 +0.2348] We love it. I dont like to have to worry about stack overflows.

- Flatten CFG: Did research and eventually removed, as it seems this is used to prevent reverse engineering of binaries. As it just converts your nice understandable branched code into a switch-like mess. It did not effect final bytecode.

- Induction Variable Simplification: [-O1 +0.1428] This is useful for programs that use a multiple loops that cannot be reduced through other means.

- Loop Flattening: [-O2 +0.0475] This one is only useful if using "[i*M+j]" style indexing. Critical for things like 2D array calculations and useful in ones that rely on cache blocking.

- Loop Rotate: [-O1 +0.1833] This one shifts the loop test to the bottom of the loop block in order to reduce the use of branches. Can use this with Loop CFG passes to further optimize loops. Almost every test led to worse performance with this enabled. Which led me to experiment with its placement. I settled on putting it at the beginning of the loop function passes to take advantage of the better loop structure.

- Loop Deletion: [-O1 +0.1043] Does DCE on loops when they are not infinite. Which is good, because we do not have multiple returns or breaks. Helpful, since without unused returns, dead loops may not be caught by other DCE passes.

- Loop Idiom Recognition: [-O1 +0.0679, -O2 +0.1254] This is pass is hard to test as other passes can do similar tests. This pass will convert a loop into straight instructions using some heuristic method. For instance a loop like this would benefit from this pass (as it will not trigger if the new code is larger than the original loop).
    ```
    for (i : 0 .. 5) {
        sum = sum + arr[i];
    }
    ```

- Unify Loop Exits & Loop Simplification: [-O2 +0.2716] I am treating these as a pair based on how they "should" work. Where `UnifyLoopExit` reduces the branches in the loop to simplify the loop CFG. Then running the `LoopSimplify` afterwords to collapse all "back edge" of the loop to a single node. This should open up further CFG simplification optimizations. Which I take advantage of later.

- Loop Invariant Code Motion: [-O2 +0.0325]
    - This is such an interesting pass. It hoists and sinks (so I removed sinking passes) and also does alias analysis to:
        - move invariant loads/calls out of the loop and into the header / exit.
        - in some occasion where stores can be moved to after the loop body, it will do so. This will make the loop body execution run faster.

- Loop Unrolling: [-O2 +0.1944] the comments in the .cpp file insists that I run indvars first and it improved the effectiveness of the loop. Its unrolling, its powerful and cuts down on the branch which usually lowers execution time.


- Loop Interchange: [-O2 +0.3543] I was scrolling through the .cpp files in `Transforms/Scalar` and found this pass. It solved the cache alignment problem with SIMD instructions (vectorizer) and can reduce cache misses. Huge gains on vectorized code.

- Aggressive Dead Code Elimination: I treat this and DCE as the same in testing. This is run at the end to pick up anything previous DCE passes were unable to pick out after most optimizations are done.

- SLP Vectorization, Loop Vectorization, and Load/Store Vectorization:
    - [-O3 +0.3654]
    - These passes do similar things, but SLP focusing on straight-line code, Loop focuses on vectorizing the loop body, and Load/Store attempts to do vectorized stores and/or loads. By using the `LoopInterchange` earlier, we see benefits to `LoopVectorize`. The other two are useful for any explicit batched actions, after they have been shown by previous optimization passes reducing the complexity of the function.

- Demote Register to Memory: [-O3 +0.3638] Used to help with CFG "hacking". I couldn't find any additional information on why it would make this possible. I run `CFGSimp` afterwords to try to capture this saving and then run `mem2reg` again.

- Jump Threading: [-O3 +0.0219] This pass was one I have never heard of before. My understanding of it, is that it takes blocks that multiple succ/prec blocks and tries to prove that some will not be taken. It then restructures the code so that the prec block jumps straight to the succ block. I am still unsure of the placement of this jump, as it is conservative as to not create irrudicible loops, which is why I placed it after all of the loop optimizations to minimize that chance. My understand of the pass is something like this,
    ```Cpp
    if (c1) {
    // Some code here
    } else if (c2) {
    // Some code here
    } else if (c3) {
    // Some code here
    } else {
    // Some code here
    }

    // Assume that c1 is proven to be false at compile time, then it is converted to...

    if (c2) {
    // Some code here
    } else if (c3) {
    // Some code here
    } else {
    // Some code here
    }
    ```

## BIG BANG TEST

huh... These are compared against `--do`


| Name       | Weighted Score | File Score | Time Score | Memory Score |
|------------|----------------|------------|------------|--------------|
| BIGBANG-03| +0.1403 |    0     |  +0.2807   |      0        |
| BIGBANG-O2| -0.0107 |    0     | -0.0215    | 0 |
| BIGBANG-O1|              +0.0780 | 0 | +0.1561 | 0|
|BIGBANG-O0|              -0.0858 | 0 | -0.1716 | 0 |



```C

arraySum(arr) {
    var s, i;
    i = 0;
    s = 0;

  for ( i : 0 .. #arr by 32) {
    s = s + arr[i];
  }
  return s;
}

bigSum(arr) {
    var s, i, j;
    i = 0;
    j = 0;
    s = 0;
    for(i : 0 .. #arr by 32) {
        for(j : 0 .. #arr[0] by 16) {
            s = s + arraySum(arr[i][j]);
        }
    }

    return s;
}

main() {
    var arr, i, j, k, s;

    s = 0;
    arr = [128 of [128 of [128 of 0]]];

    for (i : 0 .. #arr by 4) {
        for (j : 0 .. #arr[0] by 8) {
            for (j : 0 .. #arr[0][0]) {
                if ( (j + i) % 2 == 0 ) {
                    arr[i][j%2][k] = i * j + arraySum(arr[i%64][j%32]);
                }
                else {
                    if ( (j + i) % 2 == 1 ) {
                        arr[i%2][j][k] = i * j + arraySum(arr[i%32][j%16]);
                    }
                    else {
                        arr[i%13][j][k%2] = (i * j) % k;
                    }
                }
                if( (i % 128) == 0) {
                    output arr[i%8][j%4][k%2];
                }
                else {
                    arr[i][j][k] = k % 8;
                    s = s + arr[i][j%4][k];
                }
            }
        }
        if (k % 24 == 2) {
                arr[i%16][j%4][k%8] = 2;
            }
            else {
                if (i+1 == j) {
                    output arraySum(arr[i][j]);
                }
                else {
                    arr[i%64][j%32][k%2] = 1;
                }
            }
    }
  return bigSum(arr);
}
```