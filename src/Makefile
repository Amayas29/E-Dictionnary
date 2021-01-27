CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = E_dictionary

Objects = E_Dictionary.o Dictionary.o word.o hashfunctions.o UIfunctions.o

all: $(PROGRAMS)

.PHONY:	all clean

.SUFFIX: 

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

E_dictionary: $(Objects)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(PROGRAMS)
