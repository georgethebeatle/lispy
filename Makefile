CC=gcc
CFLAGS=-I.
LIBS=-lcbehave

lispy: lispy.h lispy.o main.o
	$(CC) -o lispy main.o lispy.o $(CFLAGS) $(LIBS)

test: test.o lispy.o
	$(CC) -o test test.o lispy.o $(CFLAGS) $(LIBS)

testrun: test
	make test && ./test

.PHONY: clean

clean:
	rm -f  *.o test lispy
