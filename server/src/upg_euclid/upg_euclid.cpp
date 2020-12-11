#include "upg_euclid.hpp"

IntType gcd(IntType a, IntType b, IntType *x, IntType *y) 
{
 	if (a == 0)
 	{
 		*x = 0;
 		*y = 1;

    	return b;
 	}

  	IntType x1, y1;

	IntType nod = gcd(b % a, a, &x1, &y1);
	
	*x = y1 - (b / a) * x1;
	*y = x1;

	return nod;
}

IntType upgrade_euclid(IntType a, IntType b, IntType *x, IntType *y)
{
	if (a >= b)
	{
		return gcd(a, b, x, y);
	}
	else
	{
		return gcd(b, a, x, y);
	}
}