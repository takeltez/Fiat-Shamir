#include "fiat_shamir_server.hpp"
#include "rand.hpp"
#include "file_handler.hpp"

int sock, listener;

void settings()
{
    struct sockaddr_in addr;
    
    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("socket");

        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(DEFAULT_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");

        exit(2);
    }

    listen(listener, 1);
}

void fiat_shamir_server()
{
	size_t t = 40;

	int e;

	IntType n, p, q;
	IntType v;
	IntType x, y;	

	char user[256];
	int bytes_read;

	char option = -1;
	int is_autorized = 1;
	int is_registered = 1;

	settings();

	while(1)
    {
        sock = accept(listener, NULL, NULL);

        if(sock < 0)
        {
            perror("accept");
           
            exit(3);
        }

        switch(fork())
        {
        	case -1:

           		perror("fork");

            	break;

             case 0:
             
            	close(listener);

		        while(1)
		        {
		        	srand(time(NULL));
		        	
		        	bytes_read =  recv(sock, &option, sizeof(option), 0);

		     		if(bytes_read <= 0) 
		        	{
				        break;
				    }
		        	
		        	bytes_read = recv(sock, user, sizeof(user), 0);

		        	if(bytes_read <= 0) 
		        	{
				        break;
				    }

		        	switch (option)
					{
						case '0':
			        		cout << endl << "Connected by user " << user << ", targer: registration" << endl;

			        		if (find_user(user))
			        		{
			        			cout << "Such nickname is already used" << endl;

			        			is_registered = 0;

			        			send(sock, &is_registered, sizeof(is_registered), 0);

								is_registered = 1;
								
			        			continue;
			        		}

			        		else
			        		{
			        			send(sock, &is_registered, sizeof(is_registered), 0);
			        		}

			        		rand_p_q(&p, &q);

							n = abs(p * q);

				            send(sock, &n, sizeof(n), 0);

				            recv(sock, &v, sizeof(v), 0);

							save_user(user, n, v);

							cout << "New user "<< user << " has been successfully registered" << endl;

							break;

				        case '1':
				        	
			        		cout << endl << "Connected by user " << user << ", targer: authorization" << endl;

			        		if (!find_user(user))
			        		{
			        			cout << "User with such nickname does not exist" << endl;

			        			is_autorized = 0;

			        			send(sock, &is_autorized, sizeof(is_autorized), 0);

					        	is_autorized = 1;
			        			
			        			continue;
			        		}

			        		else
			        		{
			        			send(sock, &is_autorized, sizeof(is_autorized), 0);
			        		}

			        		n = find_n(user);

			        		 send(sock, &n, sizeof(n), 0);

				            for (size_t i = 0; i < t; ++i)
							{
					            recv(sock, &x, sizeof(x), 0);

					            e = rand() % 2;

					            send(sock, &e, sizeof(e), 0);

					            recv(sock, &y, sizeof(y), 0);

					            if(!y)
								{
									cout << "Falling conection on iteration: " << i << endl;

									is_autorized = 0;
								}

								else
								{
									v = find_v(user);

									if (mod_pow(y, 2, n) != (((x % n) * mod_pow(v, e, n)) % n))
									{
										cout << "Falling conection on iteration: " << i << endl;

										is_autorized = 0;
									}
								}			
				        	}

				        	if (is_autorized == 1)
							{
								cout << "Successfull authorization by user " << user << endl;
							}
							else
							{
								cout << "Permission denied by user " << user << endl;
							}

			        		send(sock, &is_autorized, sizeof(is_autorized), 0);
			    	
			    			break; 	 			
		        	}

		        	is_registered = 1;
		        	is_autorized = 1;
		        }

		        close(sock);
		        	        
	            exit(0);

	        default:
        		close(sock);
    	}
    }

     close(listener);
}