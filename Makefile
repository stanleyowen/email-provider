CC = gcc
CFLAGS = -Wall -I./Auth
DEPS = Auth/auth.h
OBJ = main.o Auth/auth.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lcurl

clean:
	rm -f *.o main Auth/*.o