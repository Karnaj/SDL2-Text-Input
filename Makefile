CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors
LDFLAGS = -lmingw32 -lSDL2main -lSDL2
includedir = ./include
libdir = ./lib

main : main.o 
	$(CC) -I $(includedir) -L $(libdir) main.o -o programme $(LDFLAGS)
 
main.o : src/main.c 
	$(CC) -I $(includedir) -c src/main.c -o main.o $(CFLAGS)
	
clean :
	del -rf *.o

mrproper : clean
	del programme.exe
   
