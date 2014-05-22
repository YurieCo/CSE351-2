/*
 * Chun-Wei Chen
 * CSE 351
 * 04/10/12
 */

/* 
 * CSE 351 HW1 (Data Lab)
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
// Rating: 1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* x & y is equivalent to the negation of (~x | ~y) (DeMorgan's Law) */
  return ~(~x | ~y);
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   * x^y is equivalent to (x & ~y) | (~x & y),
   * which is also equivalent to ~(~(x & ~y) & ~(~x & y))
   */
  return ~(~(x & ~y) & ~(~x & y));
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  /*
   * Sets x equal to 1 then shifts it over 3 and adds 1, 
   * then shifts that over 6 and adds the 3 shifted one,
   * then shifts that over 12 and adds the 6 shifted one,
   * then shifts that over 24 and adds the 12 shifted one
   */
  int x = 1;
  x = (x << 3) + 1;
  x = x + (x << 6);
  x = x + (x << 12);
  x = x + (x << 24);	
  return x;
}
// Rating: 2
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*
   * Shift x to the left by (32 - n) bits and then shift back.
   * If the value of x remains unchanged, then x can be represented
   * as an n-bit.
   */
  int shift = 32 + (~n + 1);
  int num = x;
  num = num << shift;
  num = num >> shift;
  return !(num ^ x);
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  /*
   * (x >> 31) takes care of sign, 0 for positive nubmers and 0 and
   * -1 (all bits 1) for negative numbers. !!x sperates 0 with other
   * values. !!x gives 0 if x is 0 and 1 otherwise. positive: 0|1 gives 1,
   * zero: 0|0 gives 0, negative: -1|1 gives 1.
   */
  return (x >> 31) | (!!x);
 }
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    /*
     * Shift the word to right by 8*n bits and then
     * use & with 0xFF to keep the byte we want. 
     */
    int shift = n << 3;
    return (x >> shift) & 0xFF;
}
// Rating: 3
/* 
 * logicalShift - shift x to *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >> the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*
   * Creates a filter to get rid of any leading 1's created by
   * the arithmetic shift to make it become logical shift. The
   * value of filter is 0 followed by all 1's, and then it's
   * shifted to the right by n - 1 bits. Shift x to the right by
   * n bits and use & with filter to get the result of logical shift.
   */
  int filter;
  filter = 0x7f;
  filter = (filter << 8) + 0xFF;	
  filter = (filter << 8) + 0xFF;	
  filter = (filter << 8) + 0xFF;
  filter = ((filter >> n) << 1) + 1;
  return (x >> n) & filter; 
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  /*
   * Overflow occurs when the sign of x and y are the same, but
   * the sign of x + y is different. Use ! in front of 
   * (~(sign_x ^ sign_y) & (sign_x ^ sign_sum)) so it gives 1
   * when x + y won't ovreflow.
   */
  int sum = x + y;
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int sign_sum = sum >> 31;
  return !(~(sign_x ^ sign_y) & (sign_x ^ sign_sum));
}
// Rating: 4
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 (~(sign_x ^ sign_y) & (sign_x ^ sign_sum))
 */
int bang(int x) {
  /*
   * Since 0 is the only number where x-1 < 0 and ~x is less than 0,
   * & x-1 and ~x the sign bit will tell whether x is zero or nonzero.
   * Shifting the sign bit down to the first bit (LSB) and & with 1
   * will give 1 if x is zero and zero otherwise.
   */
  int x_minus_one;
  int sign_holder;
  x_minus_one = x + (~1 + 1);
  sign_holder = (x_minus_one & ~x) >> 31;
  return 1 & sign_holder;
 }
// Extra Credit: Rating: 3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
   * First determine whether x is 0 using !!x, then use a variable b to hold
   * ~(!!x) + 1, which is all bits 0 when x is 0 and all bits 1 otherwise.
   * Then use | to (b & y) and (~b & y). Since b is either all bits 0 or 1,
   * one of the expression will give 0 and the other one give the original
   * value. | with 0 doesn't change the value.
   */
  int a = !!x;
  int b = ~a + 1;
  return (b & y) | (~b & z);
}
// Extra Credit: Rating: 4
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*
   * Variable a checks if x is power of 2, x and x - 1 won't have a 1
   * in the same place if it's power of 2. Variable b checks if x is
   * negative or zero. Use & to combine !a and b to complete the function.
   */
  int a = x & (x + (~1 + 1));
  int b = ((!(x >> 31)) & (~(!x)));
  return (!a) & b;
}
