/* 
 * CS:APP Data Lab 
 * 
 * Luke Jung 904-982-644
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

You will provide your solution to the Data Lab by
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
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
    /*
     * NOTs the integer plus 1 OR'ed with the original number
     * to make sure there's a 1 in every spot, unless it's 0,
     * which would become 0 again from the +1.
     * Then it shifts to the MSB and adds 1 to switch to opposite
     * result
     */
    return (((~x+1) | x)>>31)+1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
    /*
     * For this one, we want to count each bit by dividing each word into
     * smaller pieces, or by half.  So we first have to create 5 different
     * mask values to be able to divide each bit into something we can use.
     * So first, we create masks that are alternating one's, then alternates
     * every two, and so on.  Once we create the masks, we use an expression of
     * x-((x >> 1) & mask) to push the bits to the smallest word expression we
     * can count.  Once we iterate through this expression with masks that match
     * the shifts, we'll end up with a small digit that'll count how many counts.
     */
    int one, two, three, four, five;
    
    one = 0x55; //01010101
    one = (one << 8) + 0x55;
    one = (one << 16) + one; //0x55555555
    
    two = 0x33; //00110011
    two = (two << 8) + 0x33;
    two = (two << 16) + two; //0x33333333
    
    three = 0x0f; //00001111
    three = (three << 8) + 0x0f;
    three = (three << 16) + three; //0x0f0f0f0f
    
    four = 0xff; //111111111
    four = (four << 16) + four; //00ff00ff
    
    five = 0xff; //11111111
    five = (five << 8) + 0xff; //0000ffff
    
    x = x + ~((x >> 1) & one) + 1;
    x = (x & two) + ((x >> 2) & two);
    x = (x & three) + ((x >> 4) & three);
    x = (x & four) + ((x >> 8) & four);
    
    return (x & five) + ((x >> 16) & five);
}

/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y)
{
    /*
     * NOTs both inputs and ANDs which gives the opposite
     * OR value which is then NOT'ed again.
     */
    return ~(~x&~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n)
{
    /*
     * First, assigns the inputted variable into an unsigned int to
     * clear the uneeded numbers by shifting it left 32-n and back to
     * right to mask only the digits cared for.  Then, we use 3 variables,
     * t1, t2, and size, where t1 consists of the int found when subtracting
     * the word size to make sure we're not shifting too far over, and t2
     * to get the sign bit when it's casted an unsigned bit.  If the MSB is
     * 1, then we haven't gone over the word count, and we continue to use
     * the function.  We only need to use the function 5 times because it
     * only needs to be doubled 5 times to get the max word size if the
     * inputted size was only 1.
     */
    int result, t1, size;
    unsigned t2, ux;
    
    ux = x;
    ux = (ux << (32-n)) >> (32-n);
    
    result = ux;
    size = n;
    
    t1 = size - 32;
    t2 = t1;
    t2 = t2 >> 31;
    
    result = (result << (size * t2)) + result * t2;
    size = size * 2;
    t1 = size - 32;
    t2 = t1;
    t2 = t2 >> 31;
    
    result = (result << (size * t2)) + result * t2;
    size = size * 2;
    t1 = size - 32;
    t2 = t1;
    t2 = t2 >> 31;
    
    result = (result << (size * t2)) + result * t2;
    size = size * 2;
    t1 = size - 32;
    t2 = t1;
    t2 = t2 >> 31;
    
    result = (result << (size * t2)) + result * t2;
    size = size * 2;
    t1 = size - 32;
    t2 = t1;
    t2 = t2 >> 31;
    
    result = (result << (size * t2)) + result * t2;

    return result;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
    /*
     * First create a shift variable that is the word size - the inputted
     * shift by converting to 2's complement.  Then by shifting the number
     * left, then right, we get a number that's all 0's or 1's until the
     * shifted over number.  When XOR'ing this with it's original number,
     * we'll see if there's a digit after the n number, and if there exists,
     * the ! will flip it to say 0 or 1.
     */
    int shift = (32 + (~n+1));
    x = ((x<<shift)>>shift)^x;
    return !x;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n)
{
    /*
     * First, we shift the input over by the bytes * 8 because
     * it starts at 0 and a byte is 8 wide.  Then we and it with 2 byte's,
     * or 0xFF to only get the last 8.
     */
  x = (x >> (n<<3));
    return x&0xFF;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
    /*
     * First step is having an XOR that is both of the MSB of inputs.
     * If it's 1, then one is negative and one is positive.  Then, we
     * compute the difference using 2's complement between y and x, and
     * obtain that MSB too.  When returning, if the xor and xsign are neg,
     * then x is definitely smaller, and if the MSB are the same and
     * difference is positive, then x must also be negative.
     */
    
    int xor = (x >> 31)^(y >> 31);
    int xsign = x>>31;
    
    int d = y + (~x+1);
    d = d>>31;
    
    return !!((xor & xsign) | (~xor & ~d));
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
    /*
     * First, we create a variable that shifts over to find the
     * sign bit.  Then, by flipping the answer of the sign, we get 0
     * if the number is negative, or if the answer is 0.
     */
    int sign = x>>31;
    return !(sign | !x);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n)
{
    /*
     * First we create a mask that is 32-n bits and then flipped.
     * Then we shift it over right n bits, and use the mask to turn
     * all the moved numbers to 0's.
     */
    int mask = ~((1 << 31) >> n << 1);
    int p = (x >> n) & mask;
    return p;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
    /*
     * Tmin is simply the smallest number, or a 1 in the MSB.
     */
    return 1<<31;
}
