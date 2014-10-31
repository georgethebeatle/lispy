CC=gcc
CFLAGS=-I.
LIBS=-lcbehave

lispy: lispy.o
	$(CC) -o lispy lispy.o $(CFLAGS) $(LIBS)

test: test.o
	$(CC) -o test test.o $(CFLAGS) $(LIBS)

testrun: test
	make test && ./test

.PHONY: clean

clean:
	rm -f  *.o test lispy
