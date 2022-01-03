CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu89
SECHEADERS = accessories.h pieces.h
MAINHEADERS = write_functions.h support_functions.h primary_functions.h
HEADERS = $(SECHEADERS) $(MAINHEADERS)
OBJECTS = source.o
EXEC = main_exec

.PHONY = default build clean

default: build

build: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run_task1: build
	./$(EXEC) 1

run_task2: build
	./$(EXEC) 2

run_task3: build
	./$(EXEC) 3

run_task4: build
	./$(EXEC) 4

run_bonus: build
	./$(EXEC) 5

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)