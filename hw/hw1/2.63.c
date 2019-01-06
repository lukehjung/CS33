#include <stdio.h>

unsigned long srl(unsigned long x, int k)
{
    unsigned long xsra = (long)x >> k;
    long mask = (-1 << ((8*sizeof(int))-k));
    return xsra & ~mask;
}

long sra(long x, int k)
{
    long xsrl = (unsigned long)x >> k;
    long mask = (-1 << ((8*sizeof(int))-k));
    return x<0 ? xsrl | mask: xsrl;
}
