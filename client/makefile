CC := g++
CFLAGS := -Wall -std=c++17

all: bin/fiat_shamir_client

bin/fiat_shamir_client: build/main.o build/rand.o build/miller_rabin.o build/mod_pow.o build/upg_euclid.o build/fiat_shamir_client.o
		$(CC) $(CFLAGS) build/main.o build/rand.o build/miller_rabin.o build/mod_pow.o build/fiat_shamir_client.o -o bin/fiat_shamir_client -lm

build/main.o: src/main.cpp src/fiat_shamir_client/fiat_shamir_client.hpp src/mod_pow/mod_pow.hpp
		$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o -Isrc/fiat_shamir_client -Isrc/mod_pow 

build/rand.o: src/rand/rand.cpp src/rand/rand.hpp src/miller_rabin/miller_rabin.hpp src/mod_pow/mod_pow.hpp 
		$(CC) $(CFLAGS) -c src/rand/rand.cpp -o build/rand.o -Isrc/mod_pow  -Isrc/miller_rabin

build/miller_rabin.o: src/miller_rabin/miller_rabin.cpp src/miller_rabin/miller_rabin.hpp src/mod_pow/mod_pow.hpp
		$(CC) $(CFLAGS) -c src/miller_rabin/miller_rabin.cpp -o build/miller_rabin.o -Isrc/miller_rabin -Isrc/mod_pow

build/mod_pow.o: src/mod_pow/mod_pow.cpp src/mod_pow/mod_pow.hpp
		$(CC) $(CFLAGS) -c src/mod_pow/mod_pow.cpp -o build/mod_pow.o -Isrc/mod_pow

build/upg_euclid.o: src/upg_euclid/upg_euclid.cpp src/upg_euclid/upg_euclid.hpp src/mod_pow/mod_pow.hpp
		$(CC) $(CFLAGS) -c src/upg_euclid/upg_euclid.cpp -o build/upg_euclid.o -Isrc/upg_euclid -Isrc/mod_pow

build/fiat_shamir_client.o: src/fiat_shamir_client/fiat_shamir_client.cpp src/fiat_shamir_client/fiat_shamir_client.hpp src/rand/rand.hpp src/mod_pow/mod_pow.hpp
		$(CC) $(CFLAGS) -c src/fiat_shamir_client/fiat_shamir_client.cpp -o build/fiat_shamir_client.o  -Isrc/mod_pow -Isrc/rand

dir:
		@mkdir build
		@mkdir bin
		
clean:
		@rm build/*.o
		@rm bin/*