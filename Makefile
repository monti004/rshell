CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:|bin 
	$(CC) $(FLAGS) -o   bin/rshell src/rshell.cpp


rshell: |bin
	$(CC)  -o bin/rshell src/rshell.cpp

bin: 
	mkdir bin

clean: 
	rm -rf bin


