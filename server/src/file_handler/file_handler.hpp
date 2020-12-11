#pragma once
#include "mod_pow.hpp"

#define KEY_V_POS 2

int find_user(string founded_user);

void save_user(string new_user, IntType n, IntType v);

IntType find_n(string user);

IntType find_v(string user);