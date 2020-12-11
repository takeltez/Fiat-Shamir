#pragma once
#include<iostream>
#include<ctime>
#include <cmath>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define LIMIT 1000000000

using namespace std;

namespace mp = boost::multiprecision;

using IntType = mp::cpp_int;

vector <IntType> from_10_to_2(IntType a);

vector <IntType> zero_delete(vector <IntType> binary);

vector <IntType> reverse_vector(vector <IntType> binary_a);

IntType to_pow(IntType a, IntType m, vector <IntType> reversed_binary_a);

IntType mod_pow(IntType a, IntType x, IntType m);

