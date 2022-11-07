#include "ParserHelper.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ExceptionContainsWhat.h"

#include <catch2/catch_test_macros.hpp>

/*
    STARTING NEW UNIT TESTS FOR SIP EXTENSION

    TODO: DOCUMENT
*/

TEST_CASE("TIP Parser: Parsing Boolean Type", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
      main() {
        var t,f,r;
        t = true;
        f = false;
        r = (t == f);
        return r;
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Lexer: leq comparison token", "[TIP Lexer]")
{
  std::stringstream stream;
  stream << R"(
      operators1() { var x; if (x <= 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Lexer: lt comparison token", "[TIP Lexer]")
{
  std::stringstream stream;
  stream << R"(
      operators1() { var x; if (x < 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Lexer: geq comparison token", "[TIP Lexer]")
{
  std::stringstream stream;
  stream << R"(
      operators1() { var x; if (x >= 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Relational Operator Types", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
      main() {
        var x, y, z;
        x = 0;
        y = 1;
        z = x > y;
        z = x < y;
        z = x >= y;
        z = x <= y;
        return z;
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Inc and Dec", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 0;
          y = 1;
          x++;
          y--;
          return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Inc and Dec within if-then clause", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 0;
          y = 1;
          if(true) {
            x++;
          }
          else {
            y--;
          }
          return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Inc and Dec with while", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 0;
          y = 5; 
          while(x < y) {
            x++;
          }
          return (x == y);
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Modulo", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 1;
          y = 1;
          x = y % 1;
          return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Negation", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 1;
          y = -2;
          x = -y;
          return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing Modulo and Negation", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = 1;
          y = 1;
          y = -x;
          return y;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing logical not", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y;
          x = true;
          y = not x;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing logical or", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = true;
          y = false;
          z = x or y;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing logical and", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = true;
          y = true;
          z = x and y;
          return z;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing logical [not, or, and]", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = true;
          y = false;
          z = x and not y;
          z = x or z;
          return z;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Parsing logical [not, or, and] with if clause", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = true;
          y = false;
          z = x and not y;
          z = x or z;
          if(z) {
            z = false;
          }
          return z;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

// Ternary Op Tests

TEST_CASE("TIP Parser: Ternary Op Simple", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x;
          x = (true) ? 0 : 1;
          return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Ternary Op Simple Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x;
          x = () ? 0 : 1;
          return x;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Ternary Op Complex", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var w, x, y, z;
          w = true;
          x = 8;
          y = (true) ? (w ? true : false) : x;
          z = w ? not false : true;
          return y;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Ternary Op Complex Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var w, x, y, z;
          w = true;
          x = 8;
          y = (true) ? (w ? return 0 : false) : x;
          z = w ? not false : true;
          return y;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Explicit Construction", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr;
          arr = [];
          arr = [1];
          arr = [1, 2, 3];
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Implicit Construction", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, arr1, arr2;
          x = 1;
          arr1 = [1, 2, 3];
          arr2 = [x of arr1];
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Implicit Construction Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, arr1, arr2;
          arr1 = [1, 2, 3];
          arr2 = [ of arr1];
          return 0;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array - arrayinit.sip", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          y = 3;
          x = [y+3, 13, 42];
          if (x[0] != 6) error x[0];
          x = [7 of 9];
          if (x[4] != 9) error x[4];
          z = [5 of [5 of 5]];
          if (z[3][3] != 5) error z[3][3];
          z = [[1,2,3], [4,5,6], [7,8,9]];
          if (z[1][1] != 5) error z[1][1];
          return 0; 
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Length Op", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          arr = [];
          x = (#arr == 0);
          y = #arr;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Length Op Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          arr = [];
          x = (#arr == 0);
          y = #;         // should this fail or not?
          return 0;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Element Op", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          arr = [1, 2, 3];
          x = arr[0];
          y = arr[1];
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Array Element Op Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          arr = [1, 2, 3];
          x = arr[0];
          y = arr[var f];
          return 0;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

// Iterator Style For Loop

TEST_CASE("TIP Parser: Iterator For Loop Simple", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          y = 0;
          arr = [1, 2, 3];
          for( x : arr ) {
            y = y + x;
          }
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Iterator For Loop Simple Failure", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y;
          y = 0;
          arr = [1, 2, 3];
          for(  : arr ) {
            y = y + x;
          }
          return 0;
        }
      )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Iterator For Loop Complex", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y, z;
          z = 0;
          arr = [1, 2, 3];
          for( x : arr ) {
            for(y : arr) {
              z = z + y;
            }
            z = z + x;
          }
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Iterator For Loop Complex with if-then", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var arr, x, y, z;
          z = 0;
          arr = [1, 2, 3];
          for( x : arr ) {
            if(x > 1) {
              for(y : arr) {
                z = z + y;
              }
            }
          }
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Simple range for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
            var x, arr, i;
            x = 0;
            arr = [1, 2, 3, 4];
            for( i : arr[0] .. arr[2] by 2) {
                x = x + i;
            }
            return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: Triple range for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
            var x, arr, i;
            x = 0;
            arr = [ 
                    [ 
                      [1, 2, 3, 4], [true, false, true] 
                    ], 
                    [ 
                      [5, 6, 7, 8], [&x, &i] 
                    ],
                    [ 
                      [5, 6, 7, 8], [&x, &i] 
                    ],
                    [ 
                      [1, 2, 3, 4], [true, false, true]
                    ]
                  ];
            for( a : 0 .. 1 ) {
              for(b : 0 .. 2 by 2) {
                for(c : 0 .. 4 by 2) {
                    x = x + i;
                }
              }
            }
            return x;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: maps.sip: Array and range for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
          map(a, f) {
            var m, i;
            m = [#a of f(a[0])];
            for (i : 0 .. #a) {            
              m[i] = f(a[i]);
            }
            return m;
          }
          ispositive(x) { return x > 0; }
          main() {
            var a, b;
            a = [ 13, 7, -4, 14, 0 ];

            // The following statement should produce: [true, true, false, true, false]
            b = map(a, ispositive);

            if (not b[0]) error b[0];
            if (not b[1]) error b[1];
            if (b[2]) error b[2];
            if (not b[3]) error b[3];
            if (b[4]) error b[4];
            return 0;
          }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: insertionsort.sip: Array, while, range for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
          // in-place insertion sort for array of integers
          sort(a) {
            var i, j, k, break;
            for (i : 1 .. #a) {
              k = a[i];                    // array indexing
              j = i - 1;

              /* SIP's logical operators do not use short-circuit evaluation
              * so this more complex logic is required.
              */
              break = false;
              while (j >= 0 and not break) {
                if (a[j] > k) { 
                  a[j+1] = a[j];
                  j--;       
                } else {
                  break = true;
                }
              }

              a[j+1] = k;
            } 
            return a;
          }

          copy(a) {
            var b, i;
            b = [ #a of 0 ];	// computed array initialization
            for (i : 0 .. #a) {   
              b[i] = a[i];
            }
            return b;
          }

          main() {
            var a, b, x;
            var e;
            a = [ 13, 7, -4, 14, 0 ];
            b = copy(a);
            a[2] = 2;
            a[4] = 3;
            if (sort(b)[0] != -4) error sort(b)[0];
            if (sort(b)[1] != 0) error sort(b)[1];
            if (sort(b)[2] != 7) error sort(b)[2];
            if (sort(b)[3] != 13) error sort(b)[3];
            if (sort(b)[4] != 14) error sort(b)[4];
            if (sort(a)[0] != 2) error sort(a)[0];
            if (sort(a)[1] != 3) error sort(a)[1];
            if (sort(a)[2] != 7) error sort(a)[2];
            if (sort(a)[3] != 13) error sort(a)[3];
            if (sort(a)[4] != 14) error sort(a)[4];
            return 0;
          }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: fold.sip: Arrays, itr for loop, functions as arguments", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        /*
          * This function requires an extension to type inference referred
          * to as "let polymorphism".  This is not implemented in the sipc 
          * compiler, so to compile this program use the "-dt" option to
          * disable type checking.  
          */

          /* 
          * This is a higher-order function of type:
          *    ([] \alpha1, \alpha2, (\alpha2, \alpha1) -> \alpha2) -> \alpha2
          */
          fold(a, i, f) {
            var s, e;
            s = i;
            for (e : a) {                 // iterator-style for loop  
              s = f(s,e);                  
            }
            return s;
          }

          // (int, int) -> int
          sum(x,y) { return x + y; }

          // (bool,int) -> bool
          orodd(x,y) { return x or (y % 2 != 0); }            

          main() {
            var a;
            a = [ 13, 7, -4, 14, 0 ];

            // The following statement would produce: "30"
            if (fold(a, 0, sum) != 30) error fold(a, 0, sum); 

            // The following statement would produce: "true"
            if (not fold(a, false, orodd)) error -1;

            return 0;
          }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: incdec.sip: Inc/Dec testing", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x;
          x = 7;
          x++;
          if (x != 8) error x;
          x--;
          if (x != 7) error x;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: median.sip: everything but itr for-loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        // in-place insertion sort for array of integers
        sort(a) {
          var i, j, k, break;
          for (i : 1 .. #a) {
            k = a[i];                    // array indexing
            j = i - 1;

            /* SIP's logical operators do not use short-circuit evaluation
            * so this more complex logic is required.
            */
            break = false;
            while (j >= 0 and not break) {
              if (a[j] > k) { 
                a[j+1] = a[j];
                j--;       
              } else {
                break = true;
              }
            }

            a[j+1] = k;
          } 
          return a;
        }

        array_median(a) {
          var s;
          s = sort(a);    
          return s[#s/2]; 
        }

        main() {
          var a, m;
          a = [ 13, 7, -4, 14, 0 ];
          m = array_median(a);
          if (m != 7) error m;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: logicaloperators.sip: bool, lops, error", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = true;
          y = false;
          z = true;
          if (not x) error -1;
          if (not (y or z)) error -1;
          if (not (x and z)) error -1;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: itesimple.sip: Ternary, Rel ops", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x;
          x = true ? 2 : 3;
          if (x != 2) error x;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: iteexpr.sip: Ternary complex, Rel ops", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = 1;
          y = 2;
          z = 3; 
          x = y>z ? y+2 : x-1;
          if (x != 0) error x;
          z = y!=x ? y==13 ? 42 : 5 : y+x;
          if (z != 5) error x;
          z = y!=x ? 42 : z==3 ? 5 : y+x;
          if (z != 42) error x;
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: oddfold.sip: almost same as fold.sip", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        /* 
        * This is a higher-order function of type:
        *    ([\alpha1], \alpha2, (\alpha2, \alpha1) -> \alpha2) -> \alpha2
        */
        fold(a, i, f) {
          var s, e;
          s = i;
          for (e : a) {                 // iterator-style for loop  
            s = f(s,e);                  
          }
          return s;
        }

        orodd(x,y) { output x; output y; return x or (y % 2 != 0); }            

        main() {
          var a;
          a = [ 13, 7, -4, 14, 0 ];

          if (not fold(a, false, orodd)) error fold(a, false, orodd); 

          return 0;
        }

      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: relops.sip: Relational Ops", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var x, y, z;
          x = 1;
          y = 8;
          z = 13;
          if (y < 8) error 8 - y;
          if (not (y <= 8)) error 8 - y;
          if (13 > z) error 13 - z;
          if (not (13 >= z)) error 13 - z;
          if (y+5 != z) error y+5-z;
          if (not (y+5 == z)) error y+5-z;
          return 0;
        }

      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: sequencesum.sip: rng-for-loop (by num && no by)", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var i, s;

          s = 0;
          for (i : 0 .. 10) {   // Lack of by E4
            s = s + i;
          } 
          if (s != 45) error s;

          for (i : 0 .. 10 by 2) {
            s = s + i;
          }
          if (s != 65) error s;

          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: simplearray.sip: array constructor and indexing", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var a;
          a = [1,2];
          return a[1];
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: squarearray.sip: 2d array construction and indexing", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        main() {
          var z;

          z = [[101,102], [103,104]];
          if (z[0][0] != 101) error z[0][0];
          if (z[0][1] != 102) error z[0][1];
          if (z[1][0] != 103) error z[1][0];
          if (z[1][1] != 104) error z[1][1];

          z = [[1,2,3], [4,5,6], [7,8,9]];
          if (z[0][0] != 1) error z[0][0];
          if (z[0][1] != 2) error z[0][1];
          if (z[0][2] != 3) error z[0][2];
          if (z[1][0] != 4) error z[1][0];
          if (z[1][1] != 5) error z[1][1];
          if (z[1][2] != 6) error z[1][2];
          if (z[2][0] != 7) error z[2][0];
          if (z[2][1] != 8) error z[2][1];
          if (z[2][2] != 9) error z[2][2];
          return 0;
        }
      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: sumfold.sip: arrays, functions as param, assign from function return", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        /* 
        * This is a higher-order function of type:
        *    ([\alpha1], \alpha2, (\alpha2, \alpha1) -> \alpha2) -> \alpha2
        */
        fold(a, i, f) {
          var s, e;
          s = i;
          for (e : a) {                 // iterator-style for loop  
            s = f(s,e);                  
          }
          return s;
        }

        sum(x,y) { return x + y; }

        main() {
          var a;
          a = [ 13, 7, -4, 14, 0 ];

          // The following statement would produce: "30"
          if (fold(a, 0, sum) != 30) error fold(a, 0, sum); 

          return 0;
        }

      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: tensor3d.sip: 3D arrays and indexing", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(
        hcube3d(d,v) {
          var t;
          t = [d of [d of [d of v]]];
          return t;
        }

        sum3d(hcube) {
          var s, i, j, k;
          s = 0;
          for (i : 0 .. #hcube) 
            for (j : 0 .. #hcube[i]) 
              for (k : 0 .. #hcube[i][j]) 
                s = s + hcube[i][j][k];
          return s;  
        }

        main() {
          var t1, t2;
          t1 = hcube3d(3, 1); 
          t2 = hcube3d(4, 2); 
          if (sum3d(t1) != 27) error sum3d(t1); 
          if (sum3d(t2) != 128) error sum3d(t2); 
          return 0;
        }

      )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: gtadd.sip : add higher precedence than gt", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() { return 1 > 2 + 3; })";
  std::string expected = "(expr (expr 1) > (expr (expr 2) + (expr 3)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrEleadd.sip : array element higher precedence than add", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [5 of 1];
                  return a[1] + 1; })";
  std::string expected = "(expr (expr (expr a) [ (expr 1) ]) + (expr 1))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: termuland.sip : ternary op higher precedence than mul and 'and'", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return true ? 1 * 8 : 2 and 9; })";
  std::string expected = "(expr (expr true) ? (expr (expr 1) * (expr 8)) : (expr (expr 2) and (expr 9)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrExpr.sip : array expressions", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [5 of 1];
                  return a[1] + 1; })";
  std::string expected = "(expr (expr (expr a) [ (expr 1) ]) + (expr 1))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: iteratorForLoop.sip : iterator for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a, s;
                  a = [5 of 1];
                  s = 0;
                  for (e : a) {
                    s = s + e;
                  }
                  return s;
                })";
  std::string expected =  "(declaration var (nameDeclaration a) , (nameDeclaration s) ;) (statement (assignStmt (expr a) = (expr (array [ (expr 5) of (expr 1) ])) ;)) (statement (assignStmt (expr s) = (expr 0) ;)) (statement (forStmt for ( (expr e) : (expr a) ) (statement (blockStmt { (statement (assignStmt (expr s) = (expr (expr s) + (expr e)) ;)) })))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

// (program (function (nameDeclaration main) ( ) { 
//   (declaration var (nameDeclaration a) , (nameDeclaration s) ;)
//   (statement (assignStmt (expr a) = (expr (expr array) [ (expr 5)) <missing ';'>)) statement (statement of) (statement 1 ] ;) (statement (assignStmt (expr s) = (expr 0) ;)) (statement (forStmt for ( (expr e) : (expr a) ) (statement (blockStmt { (statement (assignStmt (expr s) = (expr (expr s) + (expr e)) ;)) })))) (returnStmt return (expr s) ;) }))

TEST_CASE("TIP Parser: rangeForLoop.sip : range for loop", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var s;
                  s = 0;
                  for (i : 0 .. 10) {
                    s = s + i;
                  }
                  return s;
                })";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: rangeForLoopBy.sip : range for loop with by clause", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var s;
                  s = 0;
                  for (i : 0 .. 10 by 2) {
                    s = s + i;
                  }
                  return s;
                })";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("TIP Parser: notAndOr.sip : not, and, or precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return not true and false or true;
                })";
  std::string expected = "return (expr (expr (expr not (expr true)) and (expr false)) or (expr true))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: relEq.sip : relational and equality precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 < 2 == 3 > 4;
                })";
  std::string expected = "return (expr (expr (expr 1) < (expr 2)) == (expr (expr 3) > (expr 4)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: addMul.sip : add and mul precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 + 2 * 3;
                })";
  std::string expected = "return (expr (expr 1) + (expr (expr 2) * (expr 3)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: mulAdd.sip : mul and add precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 * 2 + 3;
                })";
  std::string expected = "return (expr (expr (expr 1) * (expr 2)) + (expr 3))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: addMulAdd.sip : add and mul precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 + 2 * 3 + 4;
                })";
  std::string expected = "return (expr (expr (expr 1) + (expr (expr 2) * (expr 3))) + (expr 4))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: mulAddMul.sip : mul and add precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 * 2 + 3 * 4;
                })";
  std::string expected = "return (expr (expr (expr 1) * (expr 2)) + (expr (expr 3) * (expr 4)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: addMulAddMul.sip : add and mul precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 + 2 * 3 + 4 * 5;
                })";
  std::string expected = "return (expr (expr (expr 1) + (expr (expr 2) * (expr 3))) + (expr (expr 4) * (expr 5)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: mulAddMulAdd.sip : mul and add precedence", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return 1 * 2 + 3 * 4 + 5;
                })";
  std::string expected = "return (expr (expr (expr (expr 1) * (expr 2)) + (expr (expr 3) * (expr 4))) + (expr 5))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: ternary.sip : ternary expressions with array constructors as return values", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var r;
                  r = true ? [1, 2, 3] : [5 of 10];
                  return r;
                })";
  std::string expected = "(expr (expr true) ? (expr (array [ (expr 1) , (expr 2) , (expr 3) ])) : (expr (array [ (expr 5) of (expr 10) ])";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprEmpty.sip : array length expression with empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [];
                  return #a;
                })";
  std::string expected = "return (expr # (expr a)";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprNonEmpty.sip : array length expression with non-empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [1, 2, 3];
                  return #a;
                })";
  std::string expected = "return (expr # (expr a))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprNonEmpty2.sip : array length expression with non-empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [1, 2, 3];
                  return #a + 1;
                })";
  std::string expected = "return (expr (expr # (expr a)) + (expr 1))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprNonEmpty3.sip : array length expression with non-empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [1, 2, 3];
                  return 1 + #a;
                })";
  std::string expected = "return (expr (expr 1) + (expr # (expr a))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprNonEmpty4.sip : array length expression with non-empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [1, 2, 3];
                  return 1 + #a + 2;
                })";
  std::string expected = "return (expr (expr (expr 1) + (expr # (expr a))) + (expr 2))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayLengthExprNonEmpty5.sip : array length expression with non-empty array", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  var a;
                  a = [1, 2, 3];
                  return 1 + #a + 2 * 3;
                })";
  std::string expected = "return (expr (expr (expr 1) + (expr # (expr a))) + (expr (expr 2) * (expr 3)))";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("TIP Parser: arrayConstructorExpr.sip : array constructor with [expr : expr] syntax", "[TIP Parser]")
{
  std::stringstream stream;
  stream << R"(main() {
                  return [1 of 10];
                })";
  std::string expected = "(array [ (expr 1) of (expr 10) ])";
  std::string tree = ParserHelper::parsetree(stream);
  REQUIRE(tree.find(expected) != std::string::npos);
}