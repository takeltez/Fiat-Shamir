#include "miller_rabin.hpp"

IntType mulmod(IntType a, IntType b, IntType mod)
{
    IntType x = 0, y = a % mod;

    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }

        y = (y * 2) % mod;

        b /= 2;

    }

    return x % mod;
}

IntType modulo(IntType base, IntType exponent, IntType mod)
{
    IntType x = 1;

    IntType y = base;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            x = (x * y) % mod;
        }

        y = (y * y) % mod;

        exponent = exponent / 2;

    }

    return x % mod;
}

bool miller_rabin(IntType p, IntType iteration)
{
    if (p < 2)
    {
        return false;
    }

    if (p != 2 && p % 2==0)
    {
        return false;
    }

    IntType s = p - 1;

    while (s % 2 == 0)
    {
        s /= 2;
    }

    for (IntType i = 0; i < iteration; i++)
    {
        IntType a = rand() % (p - 1) + 1, temp = s;

        IntType mod = modulo(a, temp, p);

        while (temp != p - 1 && mod != 1 && mod != p - 1)

        {
            mod = mulmod(mod, mod, p);

            temp *= 2;
        }

        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }

    return true;
}