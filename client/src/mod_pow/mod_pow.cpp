#include "mod_pow.hpp"

vector <IntType> from_10_to_2(IntType x)
{
    vector <IntType> binary;

    binary.resize(100);

    IntType tmp; 
    int i;

    for (i = binary.size() - 1; x >= 2; --i)
    {
        tmp = x / 2;
        binary[i] = x % 2;
        x = tmp;
    }

    binary[i] = x;

    return binary;
}

vector <IntType> zero_delete(vector <IntType> binary)
{
    auto it = binary.begin();
    int vec_size = binary.size();

    for (int i = 0; !*it; ++i) 
    {
        if (i == vec_size - 1)
        {
            break;
        }

        binary.erase(it);
    }
    
    return binary;
}

vector <IntType> reverse_vector(vector <IntType> binary_a)
{
    vector <IntType> reversed_binary_a;

    for (auto it = binary_a.end() - 1; it >= binary_a.begin(); --it)
    {
        reversed_binary_a.push_back(*it);
    }

    return reversed_binary_a;
}

IntType to_pow(IntType a, IntType m, vector <IntType> reversed_binary_a)
{
    IntType y = 1;
    IntType s = a;

    for (size_t i = 0; i < reversed_binary_a.size(); ++i)
    {
        if (reversed_binary_a[i])
        {
            y = (y * s) % m;
        }

        s = (s * s) % m;
    }

    return y;
}

IntType mod_pow(IntType a, IntType x, IntType m)
{
    vector <IntType> binary_a = from_10_to_2(x);
    vector <IntType> reversed_binary_a;

    binary_a = zero_delete(binary_a);

    reversed_binary_a = reverse_vector(binary_a);

    return to_pow(a, m, reversed_binary_a);
}