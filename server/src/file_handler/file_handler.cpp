#include "file_handler.hpp"

int find_user(string founded_user)
{
	string curr_user;

	ifstream fin("res/users.txt");

    while(!fin.eof())
    {
        fin >> curr_user;

        if (curr_user == founded_user)
        {
        	return 1;
        }
    }

    return 0;
}

void save_user(string new_user, IntType n, IntType v)
{
	ofstream fout("res/users.txt", ios::app);

	fout << new_user << " " << n << " " << v << endl;
}

IntType find_n(string user)
{
	string curr_user;
	IntType n;

	ifstream fin("res/users.txt");

    while(!fin.eof())
    {
        fin >> curr_user;

        if (curr_user == user)
        {
        	fin >> n;

        	return n;
        }
    }

    return -1;
}

IntType find_v(string user)
{
    string curr_user;
    IntType v;

    ifstream fin("res/users.txt");

    while(!fin.eof())
    {
        fin >> curr_user;

        if (curr_user == user)
        {
            for (size_t i = 0; i < KEY_V_POS; ++i)
            {
                fin >> v;
            }
            
            return v;
        }
    }

    return -1;
}
