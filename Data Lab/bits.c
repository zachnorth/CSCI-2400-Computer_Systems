/* 
 * CS:APP Data Lab 
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
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) 
{
  return (~(~x & ~y));
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) 
{
    int mask = 0x55;
    int a = (mask | mask << 8);
    int b = (a | a << 16);
    return b;
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) 
{
    //int mask = 1 << 31; //Shifts 1 all the way to the signed bit position then performs an arithmetic shift
    return ((1 << 31) >> 31);//to get all bits set to 1, which in turn is -1.
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
    int mask = 0x55; //creates a mask of 0101 0101
    mask = mask | (mask << 8); //extends the mask to 16 bits
    mask = mask | (mask << 16); //extends the mask to 32 bits
    return !((x & mask) ^ mask); //(x & mask) will combine the two into a second number
                                 //((x & mask) ^ mask) exclusive or will check to see if the number created
                                 //by (x & mask) has all even bits set to 1. If they are, then the result will                                  //be all 0's which in turn will return a value of 1 because of the !
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) 
{
    int mask = (0xaa << 8) + 0xaa; //creates a 16 bit mask
    mask = ((mask << 16) + mask); //creates a 32 bit mask
    return !!(mask & x);//(mask & x) will give me a 1 in any odd-numbered bit position where x has a 1.
                        //!! the first one will give me a 0 if there are any odd-numbered bits, the second 
                        //will change that to a 1.
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) 
{
    int a = n << 3; //Multiplies n by 8 to get the number of bytes i am shifting
    int b = m << 3;//Same as above
    int swap = ~((0xFF << a) | ( 0xFF << b));//creates a mask of 0000 0000 1111 1111 0000 0000 1111 1111
    int byteOne = (x >> a) & 0xFF;//This will section off the first byte that I want to swap
    int byteTwo = (x >> b) & 0xFF;//This will section off the second byte that I want to swap
    return (x & swap) | ((byteTwo << a) | (byteOne << b));//((byteTwo << a) | (byteOne << b)) will do the         actual swap of the two bits and set them into the correct position. (x & swap) will fill in the remaining     unchanged bits/rest of the origional number.
}
/* 
 * addOK - Determine if you can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) 
{
    int sumXY = x + y; //Sums x and y
    int signSum = sumXY >> 31;//gets the sign of the sum
    int signX = x >> 31;//gets the sign of x
    int signY = y >> 31;//gets the sign of y
    return !(~(signX ^ signY) & (signX ^ signSum));//If x and y have the same sign as each other and the same                                                      sign as the sum, then the addition is ok. If x and y have                                                      the same sign as eachother, but a different sign than                                                          their sum, then the sum has overflown.
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) //go to office hours to understand this one
{
    x = !(!x); //creates a boolean value of x. IE: 0 or a 1;
	int a = (~(x & 1) + 1);//a == either 0000 or 1111
	return ((a & y) + ((~a) & z));//depending on what a was, you will either add 0 or 1 to a and z
	//and then return either the value of y or z.
    
    //Basically, if x is anything except 0, the function returns y, otherwise, it returns z
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
    int mask = (1 << 31);//creates a mask with a 1 in the most significant spot (i.e. -1)
    int lowerLimit = ~(mask | 0x39);//creates the upper limit of bits
    int upperLimit = ~(0x30);//creats the upper limit of the bits
    
    lowerLimit = (mask & (lowerLimit + x) >> 31);//If the 8th byte cause a 1 to roll over to the 7th byte,                                                      //then the bit that carries over cause the rest of the 8-byte                                               //word to be 0's. ie..putting a 0 in the most significant spot
    upperLimit = (mask & (upperLimit + x + 1) >> 31);//Theoretically creates the lower bound that does the same     //thing as the lowerlimit
    //creates the lower limit so if anything less than 0x30 gets added to upperLimit, all the bits from 6th to     //1st stay 1's, resulting in all 1's, ie..0xffffffff, after the shift
    
    
    return !(upperLimit | lowerLimit);//returns true if the upperLimit and lowerLimit are both all 0's
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) 
{
    int mask = 0xff;//Creates a mask of 1111 1111 in the 0th byte
    int shift = n << 3;//creates the actual shift in bits(ie..multiplies n by 8)
    c = c << shift;//puts the byte that we are swapping in into the correct position
    mask = (~(mask << shift));//creates a mask of all 1's except for the bit we are replacing.
    //ie.. 1111 1111 1111 1111 0000 0000 1111 1111. 
    return ((x & mask) | c);//(x & mask) will get the 32-bit integer of the origional number with 0's holding     the position of the bit we are replacing
    //((x & mask) | c) will finally put the bits of c into the correct position
}
/* reverseBits - reverse the bits in a 32-bit integer,
              i.e. b0 swaps with b31, b1 with b30, etc
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) 
{
//firstSwap = 01010101010101... swaps single bits with the bit next to it
  int one = 85;// = 0101 0101
  int two = one << 8;// = 0101 0101 0000 0000
  one = one + two;// = 0101 0101 0101 0101
  int three = one << 16;// = 0101 0101 0101 0101 0000 0000 0000 0000
  int firstSwap = one + three;// = 0101 0101 0101 0101 0101 0101 0101 0101 ... creates the mask that will swap bits that are directly next to each other
    
//dsecondSwap = 001100110011...swaps pairs of bits right next to each other
  int four = 51;// = 0011 0011
  int five = four << 8;// = 0011 0011 0000 0000
  four = four + five;// = 0011 0011 0011 0011
  int six = four << 16;// = 0011 0011 0011 0011 0000 0000 0000 0000
  int secondSwap = four + six;// = 0011 0011 0011 0011 0011 0011 0011 0011 ... creates the mask that will swap pairs of bits within each byte with eachother

//thirdSwap = 0000111100001111....swaps bytes with each other
  int seven = 15;// = 0000 1111
  int eight = seven << 8;// = 0000 1111 0000 0000
  seven = seven + eight;// = 0000 1111 0000 1111
  int nine = seven << 16;// = 0000 1111 0000 1111 0000 0000 0000 0000
  int thirdSwap = seven + nine;// = 0000 1111 0000 1111 0000 1111 0000 1111 ... creates the mask that will swap bytes with eachother

//fourthSwap = 0000 0000 1111 1111 0000 0000 1111 1111 swaps 8-bit bytes with each other
  int fourthSwap = 255 + (255 << 16); //creates the mask that will swap pairs of bytes with eachother

  

//swaps bits next to one another
//x shifted over one, AND 10000000000000 AND 1010101010101010101
//OR  x and 10101010101010 shifted over one
  x = (((x >> 1) & (~(1 << 31))) & firstSwap) | ((x & firstSwap) << 1);//This will swap singular bits next to each other
                                                           //ie.. 1010 -> 0101

//swaps pairs next to one another
  x = (((x >> 2) & (~(3 << 30))) & secondSwap) | ((x & secondSwap) << 2);//This will swap pairs of bits
                                                               //ie.. 0010 -> 1000

//swaps nibbles
  x = (((x >> 4) & (~(15 << 28))) & thirdSwap) | ((x & thirdSwap) << 4);//This will swap bytes next to each other
                                                                //ie.. 0010 1010 -> 1010 0010

//swaps bytes
  x = (((x >> 8) & (~(255 <<  24))) & fourthSwap) | ((x & fourthSwap) << 8);//This will swap 8-bit bytes with eachother
                                                             //ie.. 1010 1010 0011 0011 -> 0011 0011 1010 1010

//cuts the final number in half and switches sides
  x = ((x >> 16) & (~((255 + (255 << 8)) << 16))) | ( x << 16);//Fully flips the two halfs of the 32-bit quantity
                                                       //ie.. 1010 1010 1010 1010 0011 0011 0011 0011
                                                       //-> 0011 0011 0011 0011 1010 1010 1010 1010
 return x;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) 
{
    
    return 2;
}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) 
{
    
    return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) 
{
    
    return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) 
{
    
    return 2;
}
