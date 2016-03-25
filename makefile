CC=g++

CFLAGS=-c -Wall 

compile: objects
	$(CC) -o basket basket.o
	rm *.o
	

objects:
	$(CC) $(CFLAGS) basket.cpp  
clean:
	rm *.o
