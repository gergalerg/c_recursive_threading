GCC=gcc
CFLAGS=-g -std=c11 -Wall 
TARGET=main
SOURCES:=main.c 
DEPS:=headers.h
THREADS:=-pthread
# Math libraries
# MATH:=-lm
OBJECTS:=$(SOURCES:.c=.o)

%.o: %.c
	@echo "Making objects! Input = " $< "OUtput = " $@
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(OBJECTS)
	$(CC) $(THREADS) $(CFLAGS) $(OBJECTS) -o $(TARGET) 

.PHONY: test
test:
	$(CC) $(THREADS) $(CFLAGS) test.c -o test  

.PHONY: clean
clean:
	rm $(TARGET) $(OBJECTS)
