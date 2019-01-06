#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y)
{
    int result = x + y;
    int a = x >> (sizeof(int) * 8 - 1);
    int b = y >> (sizeof(int) * 8 - 1);
    int c = result >> (sizeof(int) * 8 - 1);
    
    int posoverflow = !a & !b&c;
    int negoverflow = a & b & !c;
    
    int twoposoverflow = ~posoverflow + 1;
    int twonegoverflow = ~negoverflow + 1;
    
    int result1 = (twoposoverflow & INT_MAX) | (~twoposoverflow & result);
    int result2 = (twonegoverflow & INT_MIN) | (~twonegoverflow & result);
    
    result = (twoposoverflow&result1) | (~twoposoverflow&result2);
    return result;
    
}
