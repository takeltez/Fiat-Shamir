#include "fiat_shamir_client.hpp"
#include "rand.hpp"

int sock;

void settings()
{
    struct sockaddr_in addr;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
  
    if(sock < 0)
    {
        perror("socket");

        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(DEFAULT_PORT); 
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");

        exit(2);
    }
}

void fiat_shamir_client()
{
	size_t t = 40;

	int e;

	IntType n;
	IntType s, v;
	IntType r, x, y;	

	char user[256];

	char option = -1;
	int is_autorized = 1;
	int is_registered = 1;

	settings();

	cout << "Hello! Welcome to our web-service!" << endl << endl;
	cout << "Choose option: authorization(1)/registration(0): ";

	cin >> option;

	if (!isdigit(option) || option < '0' || option > '1')
	{
		cout << "Choose option correctly" << endl;

		exit(1);
	}

	cout << endl <<"Enter your nickname: ";

	cin >> user;

	send(sock, &option, sizeof(option), 0);
	send(sock, user, sizeof(user), 0);

	switch (option)
	{
		case '0':

			recv(sock, &is_registered, sizeof(is_registered), 0);

			if (!is_registered)
			{
				cout << endl << "Such nickname is already used" << endl;

				exit(1);
			}

			recv(sock, &n, sizeof(n), 0);

			s = rand_s(n);

			v = mod_pow(s, 2, n);

			cout << endl << user << ", you has been successfully registered" << endl << endl;
			cout << "There is your secret key:" << endl << endl;

			cout << "s = " << s << endl;

			send(sock, &v, sizeof(v), 0);

			break;

		case '1':

			recv(sock, &is_autorized, sizeof(&is_autorized), 0);

			if (!is_autorized)
			{
				cout << endl <<"User with such nickname does not exist" << endl;

				exit(1);
			}

			cout << endl << user << ", welcome back! Please enter your secret key: ";

			cin >> s;

			recv(sock, &n, sizeof(n), 0);

			for (size_t i = 0; i < t; ++i)
			{
				r = rand() % (n - 1) + 1;  

				x = mod_pow(r, 2, n);

				send(sock, &x, sizeof(n), 0);

				recv(sock, &e, sizeof(e), 0);

				if (!e)
				{
					y = r;
				}
				else
				{
					y = ((r % n) * mod_pow(s, e, n)) % n;
				}

				send(sock, &y, sizeof(y), 0);
			}

			recv(sock, &is_autorized, sizeof(&is_autorized), 0);

			if (is_autorized)
			{
				cout << endl <<"Successfull authorization" << endl;
			}
			else
			{
				cout << endl << "Permission denied" << endl;
			}

			break;
	}

	close(sock);
}