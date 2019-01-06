#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

int saturating_add(int x, int y)
{
    int result = x + y;
    int sign = result >> (sizeof(int)*8-1);
    int overflow = __builtin_add_overflow_p(x, y, (__typeof__ ((x) + (y))) 0);
    
    int posoverflow = (sign & overflow);
    int negoverflow = ((!(sign)) & overflow);
    
    int twoposoverflow = ~posoverflow + 1;
    int twonegoverflow = ~negoverflow + 1;
    
    int result1 = (twoposoverflow & INT_MAX) | (~twoposoverflow & result);
    int result2 = (twonegoverflow & INT_MIN) | (~twonegoverflow & result);
    
    result = (twoposoverflow&result1) | (~twoposoverflow&result2);
    return result;
    
}
