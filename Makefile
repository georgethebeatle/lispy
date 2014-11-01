CC=gcc
CFLAGS=-I.
LIBS=-lcbehave -ledit -lm

lispy: lispy.h lispy.o main.o mpc.h mpc.o
	$(CC) -o lispy main.o lispy.o mpc.o $(CFLAGS) $(LIBS)

test: test.o lispy.o mpc.h mpc.o
	$(CC) -o test test.o lispy.o mpc.o $(CFLAGS) $(LIBS)

testrun: test
	make test && ./test

.PHONY: clean

clean:
	rm -f  *.o test lispy
