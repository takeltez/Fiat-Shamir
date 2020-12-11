#include "rand.hpp"
#include "miller_rabin.hpp"

IntType nod(IntType a, IntType b)
{
    while (a != 0 && b != 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else b = b % a;
    }
    return a + b;
}

IntType rand_nums(IntType limit)
{
    return rand() % limit;
}

void rand_p_q(IntType *p, IntType *q)
{
    do  
    {
        *p = rand_nums(LIMIT);
        *q = rand_nums(LIMIT);
    }
    while((!miller_rabin(*p, 5)) || (!miller_rabin(*q, 5)));
}

IntType rand_s(IntType n)
{
    IntType s;

    do  
    {
        s = rand() % (n - 1) + 1;   
    }
     while(nod(s, n) != 1);

    return s;
}
