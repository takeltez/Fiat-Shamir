#pragma once
#include "mod_pow.hpp"

IntType mulmod(IntType a, IntType b, IntType mod);

IntType modulo(IntType base, IntType exponent, IntType mod);

bool miller_rabin(IntType p, IntType iteration);