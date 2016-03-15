CC=g++
CFLAGS=-O3
LFLAGS=-O3
OBJ= main.o
TARGET=max-president-alive
max-president-alive: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cc
	$(CC) -c main.cc

clean:
	rm *.o max-president-alive
