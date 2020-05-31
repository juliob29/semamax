CC = gcc
CPPFLAGS = -g -Wall -O0 -std=c++14
CFLAGS = -g -Wall -O0 -std=gnu99

practice: changeMake.cpp
	$(CC) $(CPPFLAGS) -o  semamax semamax.cpp -lstdc++ 
