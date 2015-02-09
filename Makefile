CC = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:|bin 
	$(CC) $(FLAGS) -o   bin/rshell src/rshell.cpp
	$(CC) $(FLAGS) -o bin/ls src/ls.cpp


rshell: |bin
	$(CC)  -o bin/rshell src/rshell.cpp
	$(CC) -o bin/ls src/ls.cpp

bin: 
	mkdir bin

clean: 
	rm -rf bin


