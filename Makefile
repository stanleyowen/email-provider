# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./Auth

# Source files and dependencies
DEPS = Auth/auth.h Auth/session.h Layout/base.h Layout/composeEmail.c Operation/readEmail.h Operation/deleteEmail.h Operation/sendEmail.h
OBJ = main.o Auth/auth.o Auth/session.o Layout/base.o Layout/composeEmail.o Operation/readEmail.o Operation/deleteEmail.o Operation/sendEmail.o

# Pattern rule for compiling object files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Target for the main executable
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lcurl

# Clean target to remove compiled files
clean:
	rm -f *.o main Auth/*.o Layout/*.o Operation/*.o